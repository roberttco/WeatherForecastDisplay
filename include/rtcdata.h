// The ESP8266 RTC memory is arranged into blocks of 4 bytes. The access methods read and write 4 bytes at a time,
// so the RTC data structure should be padded to a 4-byte multiple.

#ifndef __rtcdata_h
#define __rtcdata_h

#include <RTCMemory.h>

typedef struct _RTCDATA {
  uint8_t valid;          // 1 bytes
  uint8_t channel;        // 1 byte,   2 in total
  uint8_t ap_mac[6];      // 6 bytes,  8 in total
  uint16_t adc;           // 2 bytes
} RtcData;

#define DSVALID 0x01
#define APVALID 0x02

#endif
