#ifndef LV_WEATHER_H
#define LV_WEATHER_H

#include "lvgl.h"
#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _LV_WEATHER_S
{
    char location[10];
    int code;
	int temp;
}LV_WEATHER_S;


extern lv_obj_t* Weather_obj;
extern LV_WEATHER_S my_Weather;
void lv_weather(int mode);
void lv_weather_now(LV_WEATHER_S* weatherValue);
int weatherCodeConversion(int ex_code);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  