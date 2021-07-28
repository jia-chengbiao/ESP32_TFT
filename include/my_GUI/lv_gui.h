#ifndef LV_GUI_H
#define LV_GUI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

extern lv_obj_t* Init_obj;

typedef struct _LV_GUI_S
{
    lv_obj_t* time_label1;
    lv_obj_t* time_label2;
    lv_obj_t* date_label;
    lv_obj_t* week_label;

    lv_obj_t* location;
    lv_obj_t* weather;
    lv_obj_t* temp;
}LV_GUI_S;

extern LV_GUI_S my_GUI;
/* 
 * 对gui进行初始化，
 * 此函数放置在setup函数中
 */
//GUI初始化
void lv_GuiInit(void);
//警报
void lv_alarm(uint8_t mode);
//GUI执行
void lv_gui(void);
//界面管理
void lv_InterfaceManagement(int motion);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  