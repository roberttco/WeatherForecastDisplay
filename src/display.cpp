#include "app.h"

#include <Arduino.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "display.h"

#include "fonts/Roboto_Condensed_72.h"
#include "fonts/DejaVu_Sans_Mono_10.h"
#include "fonts/Meteocons_Regular_72.h"
#include "fonts/DejaVu_Sans_Condensed_30.h"
#include "fonts/DejaVu_Sans_Condensed_16.h"
#include "fonts/DejaVu_Sans_Mono_Bold_14.h"
#include "fonts/DejaVu_LGC_Sans_Condensed_24.h"
#include "fonts/DejaVu_LGC_Sans_Mono_48.h"

// 2.9'' EPD Module
GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(/*CS=5*/ 15, /*DC=*/4, /*RES=*/5, /*BUSY=*/10)); // DEPG0290BS 128x296, SSD1680
// GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=5*/ 15, /*DC=*/ 4, /*RES=*/ 5, /*BUSY=*/ 16)); // GDEM029C90 128x296, SSD1680

void initDisplay()
{
    APPDEBUG_PRINTLN("Init display");
    display.init(9600, true, 2, false);

    APPDEBUG_PRINTLN("Set rotation");
    display.setRotation(1);

    APPDEBUG_PRINTLN("Set partial window");
    display.setPartialWindow(0, 0, display.width(), display.height());
}

struct Zone
{
    int16_t x, y, w, h, cx, cy;
} zones[numzones] = {
    {0, 0, 98, 70, 49, 35},
    {98, 0, 98, 70, 147, 35},
    {196, 0, 98, 70, 245, 35},

    {0, 70, 98, 35, 49, 87},
    {98, 70, 98, 35, 147, 87},
    {196, 70, 98, 35, 245, 87},

    {0, 105, 98, 22, 49, 116},
    {98, 105, 98, 22, 147, 116},
    {196, 105, 98, 22, 245, 116},
};

#define CURRENT_TEMP_ZONE 0
#define HIGH_TEMP_ZONE 1
#define ICON_ZONE 2
#define CURRENT_LABEL_ZONE 3
#define HIGH_TEMP_LABEL_ZONE 4
#define ICON_LABEL_ZONE 5
#define SAMPLE_TIME_ZONE 6
#define WARNING_ZONE 7
#define BATTERY_LEVEL_ZONE 8

void GetAlignedStringCoordinatesInZone(String str, int zone, byte alignment = ALIGN_Y_TOP | ALIGN_X_LEFT, int16_t *sx = nullptr, int16_t *sy = nullptr)
{
    int16_t zone_x = zones[zone].x;
    int16_t zone_y = zones[zone].y;
    int16_t zone_w = zones[zone].w;
    int16_t zone_h = zones[zone].h;
    int16_t zone_cx = zones[zone].cx;
    int16_t zone_cy = zones[zone].cy;

    int16_t tbx, tby;
    uint16_t tbw, tbh;

    const char *c_str = str.c_str();

    display.getTextBounds(c_str, 0, 0, &tbx, &tby, &tbw, &tbh);

    // top-left default
    int16_t x = zone_x;
    int16_t y = zone_y + tbh;

    // do X first
    if ((alignment & ALIGN_X_CENTER) != 0)
    {
        x = zone_cx - tbw / 2;
    }
    else if ((alignment & ALIGN_X_RIGHT) != 0)
    {
        x = zone_x + zone_w - tbw;
    }
    else
    {
        // nothing to do - use default ALIGN_X_LEFT
    }

    // now y
    if ((alignment & ALIGN_Y_CENTER) != 0)
    {
        y = zone_cy + tbh / 2;
    }
    else if ((alignment & ALIGN_Y_BOTTOM) != 0)
    {
        y = zone_y + zone_h;
    }
    else
    {
        // nothing do - use default ALIGN_Y_TOP
    }

    if (sx != nullptr)
        *sx = x;

    if (sy != nullptr)
        *sy = y;

    Serial.printf("geometry: tbx=%i tby=%i tbw=%i tbh=%i @ loc_x=%i loc_x=%i align=%02x %s\n", tbx, tby, tbw, tbh, x, y, alignment, c_str);
}

void fillZone(int zone, uint16_t color)
{
    display.fillRect(zones[zone].x,
                     zones[zone].y,
                     zones[zone].w,
                     zones[zone].h,
                     color);
}

void updateCurrentTemperature(float temperature)
{
    String ggg = String((int)(round(temperature)));
    int16_t sx = 0, sy = 0;
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&Roboto_Condensed_72);
    GetAlignedStringCoordinatesInZone(ggg, CURRENT_TEMP_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);

    fillZone(CURRENT_TEMP_ZONE, GxEPD_WHITE);

    do
    {
        display.setCursor(sx, sy);
        display.print(ggg);
    } while (display.nextPage());
}

void displayInformation(OpenWeatherMapOneCallData *data, float temp_now, double battery_level)
{
    char tempstring[32];

    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setTextColor(GxEPD_BLACK);

        // zone debugging
        for (int xz = 0; xz < numzones; xz++)
            display.drawRect(zones[xz].x, zones[xz].y, zones[xz].w, zones[xz].h, GxEPD_BLACK);

        // ###############
        // ## current temp
        // ###############
        String ggg = String((int)(round(temp_now)));
        int16_t sx = 0, sy = 0;

        // need to set the font before getting the text bounds
        display.setFont(&Roboto_Condensed_72);
        GetAlignedStringCoordinatesInZone(ggg, CURRENT_TEMP_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(ggg);

        // ###############
        // ## max temp
        // ###############
        // Determine when the max temp will be in the next 12 hours and display the time
        long dt = 0;
        float maxtemp = -1000; // strt cold...
        for (int i = 0; i < 12; i++)
        {
            if (data->hourly[i].temp > maxtemp)
            {
                maxtemp = data->hourly[i].temp;
                dt = (long)data->hourly[i].dt;
            }
        }

        // The day's high temperature
        display.setFont(&Roboto_Condensed_72);
        ggg = String((int)(rint(maxtemp)));
        //        GetAlignedStringCoordinates(ggg, 1, 0, ALIGN_X_CENTER | ALIGN_Y_CENTER);
        GetAlignedStringCoordinatesInZone(ggg, HIGH_TEMP_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(ggg);

        // weather icon
        display.setFont(&Meteocons_Regular_72);
        //        GetAlignedStringCoordinates(data->daily[0].weatherIconMeteoCon, 2, 0, ALIGN_X_CENTER | ALIGN_Y_CENTER);
        GetAlignedStringCoordinatesInZone(ggg, ICON_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(data->daily[0].weatherIconMeteoCon);

        //
        // Y-ZONE
        //

        // 'now'
        display.setFont(&DejaVu_Sans_Condensed_30);
        snprintf(tempstring, 31, "now");
        //        GetAlignedStringCoordinates(tempstring, 0, 1, ALIGN_X_CENTER | ALIGN_Y_CENTER);
        GetAlignedStringCoordinatesInZone(ggg, CURRENT_LABEL_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        // The time of the maximum temperature
        display.setFont(&DejaVu_Sans_Condensed_30);
        time_t cdt = dt; // + data->timezone_offset;
        strftime(tempstring, 31, "%H:%M", localtime(&cdt));
        //        GetAlignedStringCoordinates(tempstring, 1, 1, ALIGN_X_CENTER | ALIGN_Y_CENTER);
        GetAlignedStringCoordinatesInZone(ggg, HIGH_TEMP_LABEL_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        // icon decryption
        display.setFont(&DejaVu_Sans_Condensed_16);
        snprintf(tempstring, 31, "%s", data->daily[0].weatherMain.c_str());
        //        GetAlignedStringCoordinates(tempstring, 2, 1, ALIGN_X_CENTER | ALIGN_Y_CENTER);
        GetAlignedStringCoordinatesInZone(ggg, ICON_LABEL_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        //
        // Y-ZONE 2
        //

        // current reading time
        display.setFont(&DejaVu_Sans_Mono_10);
        cdt = data->current.dt; // + data->timezone_offset;
        strftime(tempstring, 31, "%D %H:%M", localtime(&cdt));
        //        GetAlignedStringCoordinates(tempstring, 0, 2, ALIGN_X_LEFT | ALIGN_Y_BOTTOM);
        GetAlignedStringCoordinatesInZone(ggg, SAMPLE_TIME_ZONE, ALIGN_X_CENTER | ALIGN_Y_BOTTOM, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        display.setFont(&DejaVu_Sans_Mono_10);
        snprintf(tempstring, 31, "%1.2fV", battery_level);
        //        GetAlignedStringCoordinates(tempstring, 2, 2, ALIGN_X_RIGHT | ALIGN_Y_BOTTOM);
        GetAlignedStringCoordinatesInZone(ggg, BATTERY_LEVEL_ZONE, ALIGN_X_CENTER | ALIGN_Y_BOTTOM, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        // warn about charging
        if (battery_level <= 3.0)
        {
            display.setFont(&DejaVu_Sans_Mono_Bold_14);
            String msg = "Charge Battery";
            // display.setTextColor(GxEPD_RED);
            display.setTextColor(GxEPD_BLACK);
            //            GetAlignedStringCoordinates(msg, 1, 2, ALIGN_X_CENTER | ALIGN_Y_BOTTOM);
            GetAlignedStringCoordinatesInZone(ggg, WARNING_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
            display.setCursor(sx, sy);
            display.print(msg);
        }

    } while (display.nextPage());
}
