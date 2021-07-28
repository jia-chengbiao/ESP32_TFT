#include "../include/my_GUI/lv_clock.h"
#include "../include/my_GUI/lv_gui.h"
#include "../src/my_GUI/font/fonts.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif


lv_obj_t* Clock_obj;
LV_TIME_S my_Time;

void lv_clock(int mode)
{
    if(mode == 0)
    {
        static lv_style_t clock_style;
        static lv_style_t time_label_style1;
        static lv_style_t time_label_style2;
        static lv_style_t date_label_style;

        /* 时钟整体背景 */
        lv_style_init(&clock_style);
        lv_style_set_radius(&clock_style, LV_STATE_DEFAULT, 0);
        lv_style_set_bg_opa(&clock_style, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_border_width(&clock_style, LV_STATE_DEFAULT, 0);
        lv_style_set_bg_color(&clock_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

        /* Time font */
        lv_style_init(&time_label_style1);
        lv_style_set_text_color(&time_label_style1, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_font(&time_label_style1, LV_STATE_DEFAULT, &clock_font);
        lv_style_set_text_opa(&time_label_style1, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_bg_opa(&time_label_style1, LV_STATE_DEFAULT, LV_OPA_0);

        lv_style_init(&time_label_style2);
        lv_style_set_text_color(&time_label_style2, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_font(&time_label_style2, LV_STATE_DEFAULT, &lv_font_montserrat_16);
        lv_style_set_text_opa(&time_label_style2, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_bg_opa(&time_label_style2, LV_STATE_DEFAULT, LV_OPA_0);

        /* Date font */
        lv_style_init(&date_label_style);
        lv_style_set_text_color(&date_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_font(&date_label_style, LV_STATE_DEFAULT, &date_font);
        lv_style_set_text_opa(&date_label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_bg_opa(&date_label_style, LV_STATE_DEFAULT, LV_OPA_0);

        Clock_obj = lv_obj_create(NULL, NULL);
        lv_obj_add_style(Clock_obj, LV_OBJ_PART_MAIN, &clock_style);

        /*Time display*/
        lv_obj_t* time_obj = lv_obj_create(Clock_obj, NULL);
        lv_obj_set_size(time_obj, 240, 55);
        lv_obj_align(time_obj, NULL, LV_ALIGN_CENTER, 0, -20);
        lv_obj_add_style(time_obj, LV_OBJ_PART_MAIN, &clock_style);

        /*Date display*/
        lv_obj_t* date_obj = lv_obj_create(Clock_obj, NULL);
        lv_obj_set_size(date_obj, 160, 50);
        lv_obj_align(date_obj, NULL, LV_ALIGN_CENTER, 0, 50);
        lv_obj_add_style(date_obj, LV_OBJ_PART_MAIN, &clock_style);

        my_GUI.date_label = lv_label_create(date_obj, NULL);
        lv_obj_add_style(my_GUI.date_label, LV_LABEL_PART_MAIN, &date_label_style);

        my_GUI.time_label1 = lv_label_create(time_obj, NULL);
        lv_obj_add_style(my_GUI.time_label1, LV_LABEL_PART_MAIN, &time_label_style1);
        
        my_GUI.time_label2 = lv_label_create(time_obj, NULL);
        lv_obj_add_style(my_GUI.time_label2, LV_LABEL_PART_MAIN, &time_label_style2);
    }
    
    else if(mode == 1)
    {
        static const char* week[7] = { "日","一","二","三","四","五","六" };

        lv_label_set_text_fmt(my_GUI.time_label1, "%.2d:%.2d", my_Time.hour, my_Time.min);
        lv_obj_align(my_GUI.time_label1, NULL, LV_ALIGN_CENTER, -5, 0);
        lv_label_set_text_fmt(my_GUI.time_label2, "%.2d", my_Time.sec);
        lv_obj_align(my_GUI.time_label2, NULL, LV_ALIGN_IN_RIGHT_MID, -5, 18);

        lv_label_set_text_fmt(my_GUI.date_label, "%.2d/%.2d 周%s", my_Time.mon, my_Time.mday, week[my_Time.wday]);
        lv_obj_align(my_GUI.date_label, NULL, LV_ALIGN_CENTER, 0, 0);
    }
    else{
        printf("clock up data error!!!");
    }
}

void lv_clock_now(struct tm* timeinfo)
{
    my_Time.hour = timeinfo->tm_hour;
    my_Time.min = timeinfo->tm_min;
    my_Time.sec = timeinfo->tm_sec;
    my_Time.mon = timeinfo->tm_mon + 1;
    my_Time.mday = timeinfo->tm_mday;
    my_Time.wday = timeinfo->tm_wday;

    lv_clock(1);
}



#ifdef __cplusplus
} /* extern "C" */
#endif