/*
* DS3231 I2C RTC
* 
* triton-dev
* 2016.11.27.
*
*/

#ifndef _DS3231_H_
#define _DS3231_H_

#include <Arduino.h>

class DS3231 {
  private:
    byte RTC_addr;
    byte dec2bcd(byte);
    byte bcd2dec(byte);
 
  public:
    byte second;
    byte minute;
    byte hour;
    byte dow;
    byte day;
    byte month;
    byte year;

    DS3231();
    DS3231(byte);
    ~DS3231();
    void setRTC(byte, byte, byte, byte, byte, byte, byte);
    void getRTC();
   
};




#endif

