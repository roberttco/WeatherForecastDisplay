#ifndef display_h
#define display_h

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include "OpenWeatherMapOneCall.h"

void InitDisplay(bool warmBoot);
void PutDisplayToSleep();
void displayCurrentWeatherData(OpenWeatherMapOneCallCurrentData *data);
void setupZones(uint16_t display_width, uint16_t display_height);
void DisplayInformation(OpenWeatherMapOneCallData *data, float temp_now, double battery_level);

void UpdateCurrentTemperature(float temperature);

// Location constants
// These depend on the fonts used and rotation.  These default values may be reset in setup()

const uint16_t numzones = 9;

const byte ALIGN_X_CENTER = 0b00000001;
const byte ALIGN_Y_CENTER = 0b00000010;
const byte ALIGN_X_LEFT = 0b00000100;
const byte ALIGN_X_RIGHT = 0b00001000;
const byte ALIGN_Y_TOP = 0b00010000;
const byte ALIGN_Y_BOTTOM = 0b00100000;


#endif