#include "../include/my_GUI/lv_weather.h"
#include "../include/my_GUI/lv_gui.h"
#include "./image/images.h"
#include "../src/my_GUI/font/fonts.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif


lv_obj_t* Weather_obj;
LV_WEATHER_S my_Weather;

void lv_weather(int mode)
{
    if(mode == 0)
    {
        static lv_style_t weather_style;

        static lv_style_t location_label_style;
        static lv_style_t temp_label_style;


        /* 天气整体背景 */
        lv_style_init(&weather_style);
        lv_style_set_radius(&weather_style, LV_STATE_DEFAULT, 0);
        lv_style_set_bg_opa(&weather_style, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_border_width(&weather_style, LV_STATE_DEFAULT, 0);
        lv_style_set_bg_color(&weather_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

        /* location font */
        lv_style_init(&location_label_style);
        lv_style_set_text_color(&location_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_font(&location_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
        lv_style_set_text_opa(&location_label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_bg_opa(&location_label_style, LV_STATE_DEFAULT, LV_OPA_0);

        /* temperature font */
        lv_style_init(&temp_label_style);
        lv_style_set_text_color(&temp_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_font(&temp_label_style, LV_STATE_DEFAULT, &temp_font);
        lv_style_set_text_opa(&temp_label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_bg_opa(&temp_label_style, LV_STATE_DEFAULT, LV_OPA_0);

        Weather_obj = lv_obj_create(NULL, NULL);
        lv_obj_add_style(Weather_obj, LV_OBJ_PART_MAIN, &weather_style);

        /* Weather Image */
        my_GUI.weather = lv_img_create(Weather_obj, NULL);

        /*location display*/
        lv_obj_t* location_obj = lv_obj_create(Weather_obj, NULL);
        lv_obj_set_width(location_obj, 150);
        lv_obj_align(location_obj, NULL, LV_ALIGN_CENTER, -40, 100);
        lv_obj_add_style(location_obj, LV_OBJ_PART_MAIN, &weather_style);

        /*temperature display*/
        lv_obj_t* temp_obj = lv_obj_create(Weather_obj, NULL);
        lv_obj_set_width(temp_obj, 80);
        lv_obj_align(temp_obj, NULL, LV_ALIGN_CENTER, 85, 95);
        lv_obj_add_style(temp_obj, LV_OBJ_PART_MAIN, &weather_style);

        my_GUI.location = lv_label_create(location_obj, NULL);
        lv_obj_add_style(my_GUI.location, LV_LABEL_PART_MAIN, &location_label_style);

        my_GUI.temp = lv_label_create(temp_obj, NULL);
        lv_obj_add_style(my_GUI.temp, LV_LABEL_PART_MAIN, &temp_label_style);
    }
    else if(mode == 1)
    {
        lv_label_set_text_fmt(my_GUI.location, "%s", my_Weather.location);
        lv_img_set_src(my_GUI.weather, weather[weatherCodeConversion(my_Weather.code)].Path);
        lv_obj_align(my_GUI.weather, NULL, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text_fmt(my_GUI.temp, "%d℃", my_Weather.temp);
    }
    else
    {
        printf("weather up data error!!!");
    }
}

void lv_weather_now(LV_WEATHER_S* weatherValue)
{
    my_Weather.code = weatherValue->code;
    strcpy(my_Weather.location , weatherValue->location);
    my_Weather.temp = weatherValue->temp;

    lv_weather(1);
}

int weatherCodeConversion(int ex_code)
{
    return ex_code;
}

#ifdef __cplusplus
} /* extern "C" */
#endif