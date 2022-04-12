#include "PxMatrix.h"
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Ticker.h>
Ticker display_ticker;
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2
const char *ssid = "название вашей сети";
const char *password = "пароль вашей сети";
const long utcOffsetInSecond = 10800;//мешение времини относительно utc в секундах
char daysOfTheWeek[7][13] = {"VOSKRESEN'YE","PONEDEL'NIK","VTORNIK","SREDA","CHETVERG","PEATNITSA","SUBBOTA"}; //дни недели писать или на английском или транслитом
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org"/*ntp сервер*/,utcOffsetInSecond);
uint8_t display_draw_time=10; //10-50 is usually fine
PxMATRIX display(64/*ширина матрицы */,32/*высота матрицы*/,P_LAT, P_OE,P_A,P_B,P_C,P_D);
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);
uint16_t myCOLORS[8]={myRED,myGREEN,myBLUE,myWHITE,myYELLOW,myCYAN,myMAGENTA,myBLACK};
void display_updater()
{  display.display(display_draw_time);}
void display_update_enable(bool is_enable)
{  if (is_enable)
    display_ticker.attach(0.004, display_updater);
  else
    display_ticker.detach();}
void setup() {
 Serial.begin(115200);
 WiFi.begin(ssid,password);
 while(WiFi.status() !=WL_CONNECTED)
 {delay(500);
 Serial.print(".");}
 timeClient.begin();
  display.begin(16);//тип сканирования 
  display.setDriverChip(FM6126A);  
  display_update_enable(true);
  delay(10);}
void loop() {
   timeClient.update();
  display.clearDisplay();
  display.setTextColor(myRED);
  display.setCursor(2,2);
  display.print(timeClient.getHours());
  display.setTextColor(myGREEN);
  display.print(":");
  display.setTextColor(myBLUE);
  display.print(timeClient.getMinutes());
  display.setTextColor(myYELLOW);
  display.print(":");
  display.setTextColor(myCYAN);
  display.print(timeClient.getSeconds());
  display.setTextColor(myMAGENTA);
  display.setCursor(2,12);
  display.print(daysOfTheWeek[timeClient.getDay()]);
delay(1000);
}
