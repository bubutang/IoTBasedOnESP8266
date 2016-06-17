#ifndef __LED_H__
#define __LED_H__

#include <SmingCore/SmingCore.h>

#define ON false
#define OFF true

void ledInit();
void ledON();
void ledToggle();
void ledOFF();
void ledSet(bool sta);
bool ledStatus();
void ws2812Updata(char r, char g, char b);
void ws2812Updata(int color);
#endif
