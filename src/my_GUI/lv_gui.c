#include "./my_GUI/lv_gui.h"
#include "./my_GUI/lv_clock.h"
#include "./my_GUI/lv_weather.h"
#include "./image/images.h"


static lv_style_t default_style;

lv_obj_t* Init_obj;


void lv_GuiInit(void)
{
    lv_style_init(&default_style);
	lv_style_set_radius(&default_style, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&default_style, LV_STATE_DEFAULT, LV_OPA_COVER);
	lv_style_set_border_width(&default_style, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_add_style(lv_scr_act(), LV_BTN_PART_MAIN, &default_style);

	//创建开机界面
	Init_obj = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_click(Init_obj, false);
	lv_obj_set_size(Init_obj, 240, 240);
	lv_obj_align(Init_obj, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(Init_obj, LV_OBJ_PART_MAIN, &default_style);

	//开机界面图像设置
	lv_obj_t* img = lv_img_create(Init_obj, NULL);
	// lv_img_set_src(img, &ali);
	lv_img_set_src(img, &ali);
	lv_obj_align(Init_obj, NULL, LV_ALIGN_CENTER, 0, 0);

    //开机界面字幕设置
	static lv_style_t alarm_style;

	lv_style_init(&alarm_style);
	lv_style_set_text_color(&alarm_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_text_font(&alarm_style, LV_STATE_DEFAULT, &lv_font_montserrat_22);
	lv_style_set_text_opa(&alarm_style, LV_STATE_DEFAULT, LV_OPA_COVER);
	lv_style_set_bg_opa(&alarm_style, LV_STATE_DEFAULT, LV_OPA_0);

	lv_obj_t* label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_add_style(label, LV_LABEL_PART_MAIN, &alarm_style);
	lv_obj_set_width(label, 80);
	lv_label_set_text(label, "Loading............");
	lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 100);

	lv_task_handler();
}

void lv_alarm(uint8_t mode)
{
	static lv_style_t alarm_label_style;

	lv_style_init(&alarm_label_style);
	lv_style_set_text_color(&alarm_label_style, LV_STATE_DEFAULT, LV_COLOR_RED);
	lv_style_set_text_font(&alarm_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_22);
	lv_style_set_text_opa(&alarm_label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
	lv_style_set_bg_color(&alarm_label_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_style_set_bg_opa(&alarm_label_style, LV_STATE_DEFAULT, LV_OPA_COVER);


	if(mode == 1){
		lv_obj_t* alarm_label = lv_label_create(lv_scr_act(), NULL);
		lv_obj_add_style(alarm_label, LV_LABEL_PART_MAIN, &alarm_label_style);
		lv_label_set_long_mode(alarm_label, LV_LABEL_LONG_SROLL_CIRC);
		lv_obj_set_width(alarm_label, 150);
		lv_label_set_text(alarm_label, "Cannot connect to the WiFi network");
		lv_obj_align(alarm_label, NULL, LV_ALIGN_CENTER, 0, 100);
	}
}

LV_GUI_S my_GUI;
/* 
 * GUI执行
 * 包含时钟与天气界面
 * flag：	0表示当前为时钟界面 Clock_obj
 * 			1表示当前为天气界面 Weather_obj
 */
static int flag = 0;
void lv_gui(void)
{
	lv_clock(0);
	lv_weather(0);
}

void lv_InterfaceManagement(int motion)
{
	switch(motion)
	{
		case 1://左运动
			if(flag){
				lv_scr_load_anim(Clock_obj, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 50, false);
				flag = ~flag;
			}
			else{
				lv_scr_load_anim(Weather_obj, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 50, false);
				flag = ~flag;
			}
			break;
		case 2://右运动
			if(flag){
				lv_scr_load_anim(Clock_obj, LV_SCR_LOAD_ANIM_OVER_RIGHT, 500, 50, false);
				flag = ~flag;
			}
			else{
				lv_scr_load_anim(Weather_obj, LV_SCR_LOAD_ANIM_OVER_RIGHT, 500, 50, false);
				flag = ~flag;
			}
			break;
		default:
			break;
	}
}