#include <ESP8266WiFi.h>

#include "app.h"
#include "wifi.h"
#include "rtcdata.h"

#include "secret.h"

// IPAddress ip    (192,168,2,182);
// IPAddress dns   (192,168,2,4);
// IPAddress gw    (192,168,2,1);
// IPAddress subnet(255,255,255,0);

/*
 * WiFi Settings
 */
#if defined(ESP8266)
const char *ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();
#else
const char *ESP_HOST_NAME = "esp-" + ESP.getEfuseMac();
#endif

const char *password = WIFI_PASSWORD;
const char *ssid = WIFI_SSID;

#ifdef APPDEBUG

const char *StatusToString(int status)
{
    switch (status)
    {
    case WL_CONNECTED:
        return "Connected";
    case WL_NO_SHIELD:
        return "No network hardware";
    case WL_IDLE_STATUS:
        return "Waiting for connection";
    case WL_NO_SSID_AVAIL:
        return "No ssid available";
    case WL_SCAN_COMPLETED:
        return "WiFi scan completed";
    case WL_CONNECT_FAILED:
        return "Connection failed";
    case WL_CONNECTION_LOST:
        return "Connection lost";
    case WL_DISCONNECTED:
        return "Disconnected";
    default:
        return "Unknown WiFi status";
    }
}

#endif

String macAddressToString(uint8_t *mac)
{
    char result[14];

    snprintf(result, sizeof(result), "%02X%02X%02X%02X%02X%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return String(result);
}

boolean ConnectToWiFi(RtcData *rtcData)
{
    boolean rval = false;
    int retries = 0;

    // the value will be zero if the data isn't valid
    boolean apvalid = ((rtcData != NULL) && ((rtcData->valid & APVALID) == APVALID));

    if (apvalid == true)
    {
        Serial.printf("valid = %0x\n", rtcData->valid);
        // The RTC data was good, make a quick connection
        APPDEBUG_PRINTLN("Connecting to AP using stored AP channel and MAC");
        APPDEBUG_PRINT("Channel: ");
        APPDEBUG_PRINTLN(rtcData->channel);

        APPDEBUG_PRINT("MAC: ");
        APPDEBUG_PRINTLN(macAddressToString(rtcData->ap_mac));

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD, rtcData->channel, rtcData->ap_mac, true);
    }
    else
    {
        // The RTC data was not valid, so make a regular connection
        APPDEBUG_PRINTLN("Connecting to AP by discovering AP channel and MAC");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
    delay(50);

    int wifiStatus = WiFi.status();
    int loops = 0;
    while (wifiStatus != WL_CONNECTED)
    {
        retries++;
        if (retries == 300)
        {
            APPDEBUG_PRINTLN("No connection after 300 steps, power cycling the WiFi radio. I have seen this work when the connection is unstable");
            WiFi.disconnect();
            delay(10);
            WiFi.forceSleepBegin();
            delay(10);
            WiFi.forceSleepWake();
            delay(10);
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        }
        else if (retries == 600)
        {
            APPDEBUG_PRINTLN("Retrying WiFi connection");

            WiFi.disconnect(true);
            delay(10);
            WiFi.mode(WIFI_OFF);
            delay(10);
            WiFi.forceSleepBegin();
            delay(10);

            if (loops == 3)
            {
                APPDEBUG_PRINTLN("   That was 3 loops, still no connection so let's go to deep sleep for 2 minutes");
                Serial.flush();
                ESP.deepSleep(120000000, WAKE_RF_DISABLED);
            }
            else
            {
                APPDEBUG_PRINTLN("   No connection after 600 steps. WiFi connection failed.");
                loops++;
            }

            break;
        }
        APPDEBUG_PRINTLN("   Waiting for connection");
        delay(500);
        wifiStatus = WiFi.status();
    }

    if (wifiStatus == WL_CONNECTED)
    {
        rval = true;

        APPDEBUG_PRINT("Connected to ");
        APPDEBUG_PRINTLN(WiFi.SSID());
        APPDEBUG_PRINT("Assigned IP address: ");
        APPDEBUG_PRINTLN(WiFi.localIP());
    }

    return rval;
}
