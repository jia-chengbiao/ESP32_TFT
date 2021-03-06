#include <Arduino.h>
#include <Wire.h>
#include <lvgl.h>
#include <../lib/lvgl/src/lv_examples/lv_examples.h>
#include "../include/my_BSP/display.h"
#include "../include/my_GUI/lv_gui.h"
#include "../include/my_APP/network.h"
#include "../include/my_BSP/sd_card.h"
#include "../include/my_BSP/lv_port_fs.h"

#define LEFT_IO     GPIO_NUM_21
#define RIGHT_IO    GPIO_NUM_22

Network network;
Display screen;
SdCard tf;
struct tm timeinfo;

long timeSinceLastWUpdate = 0;
long timeSinceLastTUpdate = 0;

// static int flag = 0;
long flagUpdate = 0;

int buttonSwitch();


void setup()
{
    Serial.begin(115200);
    
    gpio_set_direction(LEFT_IO,GPIO_MODE_INPUT);
    gpio_set_direction(RIGHT_IO,GPIO_MODE_INPUT);
    //SD卡初始化
    tf.init();

    // display init
    screen.init();
    screen.setBackLight(0,200);

    String ssid = tf.readFileLine("/wifi.txt", 1);		// line-1 for WiFi ssid
	String password = tf.readFileLine("/wifi.txt", 2);	// line-2 for WiFi password
    String city = tf.readFileLine("/wifi.txt", 3);	// line-3 for city

    //wifi、time、weather init 
    network.init(ssid,password);
    network.setUpTime();
	network.setUpWeather(city.c_str());

    //官方DEMO测试
    //lv_demo_widgets();

    lv_gui();

    network.getTime(&timeinfo);
	network.getWeather();

    lv_scr_load_anim(Weather_obj, LV_SCR_LOAD_ANIM_FADE_ON, 1000, 500, false);

    timeSinceLastTUpdate = millis();
    timeSinceLastWUpdate = millis();
    flagUpdate = millis();
}


void loop()
{
    //时间获取
    if (millis() - timeSinceLastTUpdate > (1000L)){
        network.getTime(&timeinfo);
        timeSinceLastTUpdate = millis();
    }

    //天气获取
    if (millis() - timeSinceLastWUpdate > (1000L*10*60)) {
		network.getWeather();
		timeSinceLastWUpdate = millis();
  	}

    // printf("%d\n",buttonSwitch());
    //界面控制
    lv_InterfaceManagement(buttonSwitch());

    lv_task_handler();
    delay(10);
}


int buttonSwitch()
{
    static int flag = 0;
	if(gpio_get_level(LEFT_IO) == 0 && flag == 0){
        flag = 1;
        return 1;
    }
    if(gpio_get_level(RIGHT_IO) == 0 && flag == 0){
        flag = 1;
        return 2;
    }
    if(gpio_get_level(LEFT_IO) && gpio_get_level(RIGHT_IO)){
        flag = 0;
    } 
    return 0;
}