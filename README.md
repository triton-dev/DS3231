#DS3231 I2C real-time clock (RTC) Arduino helper

DS3231 is a low-cost extremely accurate I2C RTC with an integrated temperature
compensed crystal oscillator (TCXO) any crystal. DS3231 is available in a
16-pin 300-mil SO package.

The date management cares leap years automatically. DS3231 has a built in 
temperature sensor with +/- 3 Celsius accuracy, two programmable time-of-day
alarms. (Please check the datasheet for more information.)

##Usage

Include **DS3231** library to your Arduino sketch.
It is ready to use for basic usage as:
- set RTC to an user defined sec, min, hour, day-of-week, day, month, year
- get time and date from the RTC
- get LCD printable time and date character array

###Variables
  private:
-    `byte RTC_addr` Address of RTC. 0x68 is the default address.
  
  public:
-    `byte second`
-    `byte minute`
-    `byte hour`
-    `byte dow` (day of week 1-Sunday, 2-Monday, ... 7-Saturday)
-    `byte day`
-    `byte month`
-    `byte year`
-    `byte dec2bcd(byte)` DS3231 stores data in BCD format, these 2 functions
-    `byte bcd2dec(byte)` Convert values dec-to-bcd and bcd-to-dec values.
-    `char RTCtime[9]` This array contains the **time** for LCD print.
-    `char RTCdate[16]` This array contains the **date** for LCD print.

###Functions
  
-    `DS3231(byte)` // Use this contructor when your RTC has a different address.

    
-    `void setRTC(byte, byte, byte, byte, byte, byte, byte)`
    Set the RTC to the user defined timestamp.
    Values in order: 
    second, minute, hour, day-of-week (see dow), day, month, year
    
-   `void getRTC()`
    Ask full **time** and **date** data from RTC.
    This function must be called before you want to get time and date datas.
    This function refreshh date and time variables.
    After the call your `rtc.[second|minute|hour|dow|day|month|year]` will
    contain the actual data. If your application use only the minute, you
    simply write:
    `rtc.getRTC();
      your_variable = rtc.minute;
    `
    
-    `void getRTCtime()`
    This function create an LCD printable **time** data array.
    The result is in `RTCtime`.
    
-    `void getRTCdate()`
    This function create an LCD printable **date** data array.
    The result is in `RTCdate`.
    In _DS3231.cpp_ `switch(D)` cases contains the name-of-day abbreviations.
    There are Hungarian abbrev. of days now. You can change them to yours, 
    but follow the sample please. 
    
    
-    `byte getRTC_addr()`
    This function returns your RTC address.

###Example to print to the LCD RTC time and date.

```
/*
Arduino Pro Micro
Board: Arduino Micro
Port: /dev/ttyACMx
Programmer: USBasp
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <DS3231.h>

DS3231 rtc; // RTC address is default.
// You can use:
// DS3231 rtc(0x68)
// to set your RTC address if it hasn't the default.
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();
  //rtc.setRTC(00,53,15,2,28,11,16);
  //Set RTC if it is not. 
  //I use EEPROM addr(0) to check RTC set. Simply write EEPROM(0,255) when you
  // setted the RTC and check it in setup(). If EEPROM(0) is not 255, your RTC
  // is not setted.
  
  rtc.getRTCtime();
  rtc.getRTCdate();
  lcd.setCursor(0,0);
  lcd.print(rtc.RTCtime);
  lcd.setCursor(0,1);
  lcd.print(rtc.RTCdate);
  delay(3000);
  lcd.clear();
}

void loop() {
  rtc.getRTCtime();
  rtc.getRTCdate();
  lcd.setCursor(0,0);
  lcd.print("    ");
  lcd.print(rtc.RTCtime);
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.print(rtc.RTCdate);
}

```




