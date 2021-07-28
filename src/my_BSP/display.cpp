#include "../include/my_BSP/display.h"

TFT_eSPI TFT = TFT_eSPI(); /* TFT instance */
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

/* Serial debugging */
void my_print(lv_log_level_t level, const char* file, uint32_t line, const char* fun, const char* dsc)
{
	Serial.printf("%s@%d %s->%s\r\n", file, line, fun, dsc);
	Serial.flush();
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
	uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

	TFT.startWrite();
	TFT.setAddrWindow(area->x1, area->y1, w, h);
	TFT.pushColors(&color_p->full, w * h, true);
	TFT.endWrite();

	lv_disp_flush_ready(disp);
}


/*
 * 显示屏初始化
 * 设置屏幕镜像反转
 */
void Display::init(void)
{
	/* 屏幕背光设置（PWM调光） */
	ledcAttachPin(LCD_BL_PIN/* pin */, LCD_BL_PWM_CHANNEL);
	ledcSetup(LCD_BL_PWM_CHANNEL, 5000/* freq */, 8/*resolution*/);
	ledcWrite(LCD_BL_PWM_CHANNEL, 255);

	//lvglv初始化
	lv_init();

	lv_log_register_print_cb(my_print); /* register print function for debugging */
	TFT.begin(); /* TFT init */
	TFT.setRotation(4); /* mirror */

	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  	/*Initialize the display*/
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = 240;
	disp_drv.ver_res = 240;
	disp_drv.flush_cb = my_disp_flush;
	disp_drv.buffer = &disp_buf;
	lv_disp_drv_register(&disp_drv);

	lv_fs_if_init();

	//开机图片显示
	lv_GuiInit();
}

/*
 * 开机背光渐亮
 * 0为最亮，，，
 */
void Display::setBackLight(int bright, int dark)
{
	int start = dark;
	
	for(;start > bright;start-=2){
	 	ledcWrite(LCD_BL_PWM_CHANNEL, start);
		delay(20);
	}
	
}

void Display::routine(void)
{
	lv_task_handler();
}
