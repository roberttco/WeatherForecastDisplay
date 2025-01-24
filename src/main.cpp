#include "app.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "wifi.h"
#include "rtcdata.h"
#include "display.h"

#include "OpenWeatherMapOneCall.h"

#include "secret.h"

// #########################
// # RTC memory stuff
// #########################
RTCMemory<RtcData> rtcMemory;
RtcData *rtcData = NULL;

const String OPEN_WEATHER_MAP_LANGUAGE = "en";
boolean IS_METRIC = false;

// initiate the client
OpenWeatherMapOneCall *oneCallClient;

OpenWeatherMapOneCallData openWeatherMapOneCallData;

float get_ha_temp()
{
    float rval = 999;
    HTTPClient http_client;
    WiFiClient wifi_client;

    const char *url = HOME_ASSISTANT_URL;
    Serial.printf("Getting HA temp from %s\n", url);

    if (wifi_client.connected() == false)
    {
        wifi_client.connect("ha.home", 8123);
        delay(100);
    }

    http_client.begin(wifi_client, url);
    http_client.addHeader("Authorization", HOME_ASSISTANT_AUTH);
    http_client.setTimeout(5000);

    int connecitonRetries = 3;
    while (connecitonRetries > 0 && http_client.connected() == false)
    {
        APPDEBUG_PRINTLN("Waiting for connection to HA");
        delay(1000);
        connecitonRetries--;
    }

    if (connecitonRetries == 0)
    {
        APPDEBUG_PRINTLN("Connection retries exhausted.  Returning 999.");
        return rval;
    }

    int statusCode = http_client.GET();

    Serial.printf("GET request returned %d\nResponse:\n", statusCode);

    String response = http_client.getString();
    Serial.println(response);

    if (statusCode > 0 && statusCode < 300)
    {
        // now parse the response looking for "content":
        int labelStart = response.indexOf("state\":");
        // find the first { after "content":
        int contentStart = labelStart + 7;
        // find the following } and get what's between the braces:
        int contentEnd = response.indexOf("\"", contentStart + 1);
        String content = response.substring(contentStart + 1, contentEnd);

        Serial.printf("state = %s\n", content.c_str());

        rval = round(content.toFloat());
    }
    http_client.end();
    return rval;
}

void setup()
{
    Serial.begin(9600);

    WiFi.mode(WIFI_OFF);
    delay(10);
    WiFi.forceSleepBegin();
    delay(10);

    if (rtcMemory.begin())
    {
        APPDEBUG_PRINTLN("RTC memory library initialization done!");
    }
    else
    {
        APPDEBUG_PRINTLN("No previous RTC memory data found. The memory is reset to zeros!");
    }

    // Get the data
    rtcData = rtcMemory.getData();

#ifdef APPDEBUG
    Serial.printf("Valid: %X\nChannel: %d\nap_mac: %s\n",
                  rtcData->valid,
                  rtcData->channel,
                  macAddressToString(rtcData->ap_mac).c_str());
#endif

    oneCallClient = new OpenWeatherMapOneCall();
    oneCallClient->setMetric(IS_METRIC);
    oneCallClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);

    initDisplay();
}

int connectRetries = 3;

void loop()
{
    double battery_level = 0;
#ifdef VCAL
    int a = analogRead(A0);
    int a_wo = a - 7;         // imperically derived by connecting A0 to GND
    double K = 3.273 / 615.0; // calibrtion factor also derived imperically by observing a_wo while measuring input voltage

    float voltage_val = a_wo * K;

    Serial.printf("a0 = %i, a0 - offset = %i, v = %1.2fV\n", a, a_wo, voltage_val);
    delay(1000);
#else
    float temp_now = 9998;

    if (ConnectToWiFi(rtcData))
    {
        // Write current connection info back to RTC
        rtcData->channel = WiFi.channel();
        rtcData->valid |= APVALID;
        memcpy(rtcData->ap_mac, WiFi.BSSID(), 6); // Copy 6 bytes of BSSID (AP's MAC address)
    }
    else
    {
        connectRetries--;
        if (connectRetries > 0)
        {
            APPDEBUG_PRINTLN("Retrying WiFi connection in 10 seconds");
            delay(10000);
        }
    }

    if (connectRetries == 0)
    {
        APPDEBUG_PRINTLN("Connect retries exhausted.  Clearing RTC data and resetting.");
        // clear RTC data in case there is something amiss with the info - get a fresh start.
        memset(rtcData, 0, sizeof(RtcData));
        delay(1000);
        ESP.reset();
    }
    else
    {
        // get RSSI value including retries.
        APPDEBUG_PRINT("Getting RSSI ... ");

        connectRetries = 5;
        long rssi = WiFi.RSSI();
        while ((rssi > 0) && (connectRetries > 0))
        {
            connectRetries--;
            delay(100);
        }

        if (connectRetries <= 0)
        {
            rssi = 0;
        }

        APPDEBUG_PRINTLN(rssi);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        // Get current temp from HA if possible
        temp_now = get_ha_temp();

        if (oneCallClient)
        {
            oneCallClient->setMetric(IS_METRIC);
            oneCallClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
            oneCallClient->update(&openWeatherMapOneCallData, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATTION_LAT, OPEN_WEATHER_MAP_LOCATTION_LON);
        }

        // battery level
        rtcData->adc = analogRead(A0); // get the battery voltage for next loop iteration while WiFi is on

        // Disconnect WiFi here so its not on during the ePaper update time which can be long.
        WiFi.disconnect(true);
        delay(10);
        WiFi.forceSleepBegin();
        delay(10);
    }

    //  save curent RTC memory data
    rtcMemory.save();
    delay(10);

    APPDEBUG_PRINT("OpenWeatherMap temperature: ");
    APPDEBUG_PRINTLN(openWeatherMapOneCallData.current.temp);

    APPDEBUG_PRINT("Home assistant temperature: ");
    APPDEBUG_PRINTLN(temp_now);

    // displayCurrentWeatherData(&openWeatherMapOneCallData.current);

    // calculate the battery level using calibration data
    int a_wo = rtcData->adc - 7; // imperially derived by connecting A0 to GND
    double K = 3.273 / 615.0;    // calib
    battery_level = a_wo * K;

    displayInformation(&openWeatherMapOneCallData, temp_now, battery_level);

    delay(5000);

    updateCurrentTemperature(55);

    delay(300 * 60000); // 5 minutes
#endif
}