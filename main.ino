#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>  
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);

virtuabotixRTC rtcTime(6, 7, 8);

const char* weekdays[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
const char* months[12] = {"Jan","Feb","Mar","April","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

byte degree[8] = {
  B00100,
  B01010,
  B10001,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000
};

void setup() {  
  //Set time
  //rtcTime.setDS1302Time(5, 13, 13, 2, 22, 6, 2022);
  
  lcd.init();
  lcd.clear();
  lcd.backlight();

  //Comment for 5 seconds
  lcd.setCursor(0,0);
  lcd.print("Clock, date and");
  lcd.setCursor(0,1);
  lcd.print("thermometre.");
  delay(5000);

  lcd.createChar(1,degree);

  dht.begin();
}

void loop() {
  rtcTime.updateTime();

  lcd.setCursor(0,0);

  //Time
  if(rtcTime.hours<10) lcd.print("0");
  lcd.print(rtcTime.hours); 
  lcd.print(":");
  if(rtcTime.minutes<10) lcd.print("0");
  lcd.print(rtcTime.minutes); 
  lcd.print(":");
  if(rtcTime.seconds<10) lcd.print("0");
  lcd.print(rtcTime.seconds);

  //Date
  lcd.print(" ");
  lcd.print(rtcTime.dayofmonth);
  lcd.print(" ");
  lcd.print(months[rtcTime.month-1]);
  lcd.print(".");

  //Weekday
  lcd.setCursor(0,1);
  lcd.print(weekdays[rtcTime.dayofweek-1]);
  lcd.print(". ");

  //Thermometre
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  lcd.print(temperature);
  lcd.write(byte(1));
  lcd.print("C ");
  lcd.print(humidity);
  lcd.print("%");

  delay(1000);
}
