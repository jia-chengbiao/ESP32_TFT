#include "../include/my_APP/network.h"
#include <ArduinoJson.h> 

HTTPClient httpclient;

void Network::init(String SSID,String PassWord)
{
    int times = 0;
  	Serial.println("scan start");
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
      Serial.println("no networks found");
    }
    else
    {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i)
      {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
        delay(10);
      }
    }
    Serial.println("");
    Serial.print("Connecting: ");
    Serial.print(SSID.c_str());
    Serial.print(" @");
    Serial.println(PassWord.c_str());

    WiFi.begin(SSID.c_str(), PassWord.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(100);
      if(times == 100){
        times += 1;
        Serial.println("");
        Serial.println("Cannot connect to the WiFi network");
      }
      else if(times >100){
        lv_alarm(1);
        lv_task_handler();
      }
      else{
        times++;
        if(times%10 == 0){
          Serial.print(".");
        }
      }
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


void Network::setUpTime(void)
{
  configTime(this->gmtOffset_sec, this->daylightOffset_sec, this->ntpServer);
}

 
void Network::getTime(struct tm *timeinfo)
{
  if(!getLocalTime(timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  lv_clock_now(timeinfo);
  // Serial.println(timeinfo, "%A, %Y-%m-%d %H:%M:%S");
}


void Network::setUpWeather(String city)
{
    this->city = city;

    req = "https://api.seniverse.com";
    req += "/v3/weather/now.json?key=";
    req += this->apiKey;
    req += "&location=";
    req += this->city;
    req += "&language=zh-Hans&unit=c";
    if (httpclient.begin(req)){
        Serial.println("HTTPclient setUp done!");
    }
}

static LV_WEATHER_S weather_now;
void Network::getWeather()
{
    String tempString;
    String weatherCount;
    String temperatureCount;

    httpclient.begin(req);
    int http_code = httpclient.GET();

    if (http_code > 0)
    {
      if (http_code == HTTP_CODE_OK)
      {
        tempString = httpclient.getString();
        // Serial.println(tempString);
        int codePos = (tempString.indexOf("code"));
        int tempPos = (tempString.indexOf("temperature"));
        weatherCount = tempString.substring(codePos+7,tempPos-3);
        temperatureCount = tempString.substring(tempPos+14,tempString.length()-47);

        strcpy(weather_now.location, city.c_str());
        weather_now.code = atol(weatherCount.c_str());
        weather_now.temp = atol(temperatureCount.c_str());
      }
      
      else
      {
        Serial.printf("fail to get cityWeather,code:%d\n", http_code);
      }
    }
    
    lv_weather_now(&weather_now);
    // Serial.print("城市:");Serial.println(weather_now.location);
    // Serial.print("天气代码:");Serial.println(weather_now.code);
    // Serial.print("温度状况:");Serial.println(weather_now.temp);

}

