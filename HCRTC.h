/* FILE:    HCRTC.h
   DATE:    23/12/13
   VERSION: 0.2
   AUTHOR:  Andrew Davies
   
   23/12/13 : V0.2
   Added GetTimeString() and GetDateString() member functions that return the date
   and time in string format to allow easy output to a serial terminal or LCD display
   
   03/05/13 : V0.1
   Initial version.

Library header Real Time Clock library.

You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


#ifndef HCRTC_h
#define HCRTC_h

#include "Arduino.h"
#include "wire.h"

class HCRTC
{
  public:
  HCRTC(void);

  /* DS1307 RTC read and write functions */
  void RTCRead(int I2CDS1307Add);
  void RTCWrite(int I2CDS1307Add, byte Year, byte Month, byte Day, byte hour, byte Minuite, byte Second, byte DOW);

  byte GetYear(void);
  byte GetMonth(void);
  byte GetDay(void);
  byte GetHour(void);
  byte GetMinute(void);
  byte GetSecond(void);
  byte GetWeekday(void);
  
  String GetTimeString(void);
  String GetDateString(void);
  
  /* 24C32 EEPROM Read functions */
  void EEStartWrite(int I2C24C32Add, unsigned int ByteLocation);
  void EEWriteByte(byte Data);
  void EEEndWrite(void);
  
  void EEStartRead(int I2C24C32Add, unsigned int ByteLocation);
  byte EEReadByte(int I2C24C32Add);
    
  private:
  byte _RTCSecs;
  byte _RTCMins;
  byte _RTCHours;
  byte _RTCWeekday;
  byte _RTCDate;
  byte _RTCMonth;
  byte _RTCYear;

  byte BCD2DEC(byte BCDValue);
  byte DEC2BCD(byte DECValue);
};
#endif