/*
* DS3231 I2C RTC Arduino class
*
* triton-dev
* 2016.11.27.
*
*/

#include <DS3231.h>
#include <Wire.h>

// Cím nélküli konstruktor, alapértelmezett I2C címmel.
DS3231::DS3231() {
  RTC_addr = 0x68;
}

// Címzett konstruktor, hardveresen megváltoztatott I2C címmel.
DS3231::DS3231(byte addr) {
  RTC_addr = addr;
}

DS3231::~DS3231() {
  // Nincs mit tenni.
}

// Decimális BCD átalakítás
byte dec2bcd(byte val) {
  return ( (val / 10 * 16) + (val % 10));
}

// BCD decimális átalakítás
byte bcd2dec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}

// RTC beállítása
void setRTC(byte second, byte minute, byte hour, byte dow, \
            byte day, byte month, byte year) {
  Wire.beginTransmission(RTC_addr);
  Wire.write(0); // Másodperc regiszter címe
  Wire.write(dec2bcd(second)); // másodperc
  Wire.write(dec2bcd(minute)); // perc
  Wire.write(dec2bcd(hour)); // óra
  Wire.write(dec2bcd(dayOfWeek)); // nap száma (1=Vasárnap, 7=Szombat)
  Wire.write(dec2bcd(dayOfMonth)); // nap (1 to 31)
  Wire.write(dec2bcd(month)); // hónap
  Wire.write(dec2bcd(year)); // év (0 to 99)
  Wire.endTransmission();
}

// RTC olvasása
void getRTC() {
  Wire.beginTransmission(RTC_addr);
  Wire.write(0); // DS3231 másodperc címe
  Wire.endTransmission();
  Wire.requestFrom(RTC_addr, 7);
  // 7 bájt olvasása DS3231-ről 00h címtől kezdve
  second = bcd2dec(Wire.read() & 0x7f);
  minute = bcd2dec(Wire.read());
  hour = bcd2dec(Wire.read() & 0x3f);
  dow = bcd2dec(Wire.read());
  day = bcd2dec(Wire.read());
  month = bcd2dec(Wire.read());
  year = bcd2dec(Wire.read());
}

