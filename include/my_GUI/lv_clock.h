#ifndef LV_CLOCK_H
#define LV_CLOCK_H

#include "lvgl.h"
#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TIME_DATE_W                     200 
#define TIME_DATE_H                     80 
#define TIME_DATE_ALIGN_CENTER_X        0
#define TIME_DATE_ALIGN_CENTER_Y        80

#define CLOCK_WIDTH                     50 
#define CLOCK_HEIGHT                    50    
#define CLOCK_POS_X                     10
#define CLOCK_POS_Y                     10


typedef struct _LV_TIME_S
{
    int year;
    int mon;
    int mday;
    int wday;
    int hour;
    int min;
    int sec;
}LV_TIME_S;


extern lv_obj_t* Clock_obj;
extern LV_TIME_S my_Time;
void lv_clock(int mode);
void lv_clock_now(struct tm* timeinfo);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  