#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include <lvgl.h>
#include "./my_GUI/lv_gui.h"
#include "../include/my_BSP/lv_port_fs.h"

#define LCD_BL_PIN 5				//背光引脚
#define LCD_BL_PWM_CHANNEL 0		//背光所使用的PWM通道


class Display
{
public:
	//初始化
	void init(void);
	//常规显示
	void routine(void);
	//背光设置
	void setBackLight(int dark, int bright);
};
#endif

