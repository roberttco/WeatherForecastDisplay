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

// zone heights should be a multiple of 8 with rotation = 1 to accommodate the display controller
// behavior.
struct Zone
{
    int16_t x, y, w, h;
} zones[numzones] = {
    {0, 0, 98, 72},     // current temp
    {98, 0, 98, 72},    // high temp
    {196, 0, 98, 72},   // icon

    {0, 64, 98, 40},    // current label
    {98, 64, 98, 40},   // high temp label
    {196, 64, 98, 40},  // icon label

    {0, 104, 98, 20},   // sample time
    {98, 104, 98, 20},  // warning
    {196, 104, 98, 20}, // battery level
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

void InitDisplay(bool warmBoot)
{
    if (warmBoot)
    {
        APPDEBUG_PRINTLN("Init display after warm boot");
        display.init(9600, false, 2, false);
    }
    else
    {
        APPDEBUG_PRINTLN("Init display");
        display.init(9600, true, 2, false);
    }

    APPDEBUG_PRINTLN("Set rotation");
    display.setRotation(1);

    APPDEBUG_PRINTLN("Set partial window");
    display.setPartialWindow(0, 0, display.width(), display.height());
}

void PutDisplayToSleep()
{
    display.hibernate();
}

void GetAlignedStringCoordinatesInZone(String str, int zone, byte alignment = ALIGN_Y_TOP | ALIGN_X_LEFT, int16_t *sx = nullptr, int16_t *sy = nullptr)
{
    int16_t zone_x = zones[zone].x;
    int16_t zone_y = zones[zone].y;
    int16_t zone_w = zones[zone].w;
    int16_t zone_h = zones[zone].h;

#ifdef APPDEBUG
    Serial.printf("Zone: %i, align=%2i, x=%3i, y=%3i, w=%3i, h=%3i, ", zone, alignment, zone_x, zone_y, zone_w, zone_h);
#endif

    int16_t tbx, tby;
    uint16_t tbw, tbh;

    int16_t x = 0, y = 0;

    const char *c_str = str.c_str();

    display.getTextBounds(c_str, 0, 0, &tbx, &tby, &tbw, &tbh);

    // do X first
    if ((alignment & ALIGN_X_CENTER) != 0)
    {
        x = zone_x + (zone_w - (tbw-tbx)) / 2;
    }
    else if ((alignment & ALIGN_X_RIGHT) != 0)
    {
        x = zone_x + zone_w - tbw;
    }
    else
    {
        x = zone_x;
    }

    // now y
    if ((alignment & ALIGN_Y_CENTER) != 0)
    {
        y = zone_y + (zone_h + tbh) / 2;
    }
    else if ((alignment & ALIGN_Y_BOTTOM) != 0)
    {
        y = zone_y + zone_h;
    }
    else
    {
        y = zone_y;
    }

    if (sx != nullptr && sy != nullptr)
    {
        *sx = x;
        *sy = y;
    }

#ifdef APPDEBUG
    Serial.printf("tbx=%3i, tby=%3i, tbw=%3i, tbh=%3i,      x=%3i, sx=%3i, y=%3i, sy=%3i, val='%s'\n", tbx, tby, tbw, tbh, x, *sx, y, *sy, c_str);
#endif
}

void FillZone(int zone, uint16_t color)
{
    display.fillRect(zones[zone].x,
                     zones[zone].y,
                     zones[zone].w,
                     zones[zone].h,
                     color);
}

void UpdateCurrentTemperature(float temperature)
{
    display.setPartialWindow(zones[CURRENT_TEMP_ZONE].x, zones[CURRENT_TEMP_ZONE].y, zones[CURRENT_TEMP_ZONE].w, zones[CURRENT_TEMP_ZONE].h);
    String ggg = String((int)(round(temperature)));
    int16_t sx = 0, sy = 0;
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&Roboto_Condensed_72);
    GetAlignedStringCoordinatesInZone(ggg, CURRENT_TEMP_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);

    FillZone(CURRENT_TEMP_ZONE, GxEPD_WHITE);

    do
    {
        display.setCursor(sx, sy);
        display.print(ggg);
    } while (display.nextPage());
}

void DisplayInformation(OpenWeatherMapOneCallData *data, float temp_now, double battery_level)
{
    char tempstring[32];

    do
    {
        APPDEBUG_PRINTLN("Displaying information");

        display.fillScreen(GxEPD_WHITE);
        display.setTextColor(GxEPD_BLACK);

        // zone debugging
        // for (int xz = 0; xz < numzones; xz++)
        //     display.drawRect(zones[xz].x, zones[xz].y, zones[xz].w, zones[xz].h, GxEPD_BLACK);

        // ###############
        // ## current temp
        // ###############
        String ggg = String((int)(round(temp_now == -99 ? data->current.temp : temp_now)));
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
        GetAlignedStringCoordinatesInZone(ggg, HIGH_TEMP_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(ggg);

        // ###############
        // ## icon
        // ###############
        // weather icon
        display.setFont(&Meteocons_Regular_72);
        GetAlignedStringCoordinatesInZone(data->daily[0].weatherIconMeteoCon, ICON_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(data->daily[0].weatherIconMeteoCon);

        // ###############
        // ## the word 'now'
        // ###############
        // 'now'
        display.setFont(&DejaVu_Sans_Condensed_30);
        snprintf(tempstring, 31, "now");
        GetAlignedStringCoordinatesInZone(tempstring, CURRENT_LABEL_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        // ###############
        // ## max temp sample time
        // ###############
        // The time of the maximum temperature
        display.setFont(&DejaVu_Sans_Condensed_30);
        time_t cdt = dt; // + data->timezone_offset;
        strftime(tempstring, 31, "%H:%M", localtime(&cdt));
        GetAlignedStringCoordinatesInZone(tempstring, HIGH_TEMP_LABEL_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        // ###############
        // ## icon description
        // ###############
        display.setFont(&DejaVu_Sans_Condensed_16);
        snprintf(tempstring, 31, "%s", data->daily[0].weatherMain.c_str());
        GetAlignedStringCoordinatesInZone(tempstring, ICON_LABEL_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        // ###############
        // ## status line stuff
        // ###############
        // current reading time
        display.setFont(&DejaVu_Sans_Mono_10);
        cdt = data->current.dt; // + data->timezone_offset;
        strftime(tempstring, 31, "%D %H:%M", localtime(&cdt));
        GetAlignedStringCoordinatesInZone(tempstring, SAMPLE_TIME_ZONE, ALIGN_X_CENTER | ALIGN_Y_BOTTOM, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);

        // warn about charging
        if (battery_level <= 3.0)
        {
            display.setFont(&DejaVu_Sans_Mono_Bold_14);
            String msg = "Charge Battery";
            // display.setTextColor(GxEPD_RED);
            display.setTextColor(GxEPD_BLACK);
            GetAlignedStringCoordinatesInZone(msg, WARNING_ZONE, ALIGN_X_CENTER | ALIGN_Y_CENTER, &sx, &sy);
            display.setCursor(sx, sy);
            display.print(msg);
        }

                display.setFont(&DejaVu_Sans_Mono_10);
        snprintf(tempstring, 31, "%1.2fV", battery_level);
        GetAlignedStringCoordinatesInZone(tempstring, BATTERY_LEVEL_ZONE, ALIGN_X_RIGHT | ALIGN_Y_BOTTOM, &sx, &sy);
        display.setCursor(sx, sy);
        display.print(tempstring);
    } while (display.nextPage());
}
