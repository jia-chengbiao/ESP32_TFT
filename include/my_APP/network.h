#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "../include/my_GUI/lv_clock.h"
#include "../include/my_GUI/lv_gui.h"
#include "../include/my_GUI/lv_weather.h"


#define UPDATE_INTERVAL_SECS  1 * 10 // Update every 20 minutes  online weather

class Network
{
public:
	void init(String SSID,String PassWord);
    void setUpTime(void);
	void getTime(struct tm *timeinfo);
    void setUpWeather(String city);
    void getWeather(void);
private:
    char* ntpServer = (char*)"ntp1.aliyun.com";
    int gmtOffset_sec = 28800;
    int daylightOffset_sec = 0;

    //天气定位与密钥
    char* apiKey = (char*)"StsTE-FTWpfPoaNlY";     //API key 私钥
    String city;                              //查询的城市
    String req;
};




#endif  