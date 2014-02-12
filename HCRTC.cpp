/* FILE:    HCRTC.h
   DATE:    23/12/13
   VERSION: 0.2
   AUTHOR:  Andrew Davies

   Change Log:
   
   23/12/13 : V0.2
   Added GetTimeString() and GetDateString() member functions that return the date
   and time in string format to allow easy output to a serial terminal or LCD display
   
   03/05/13 : V0.1
   Initial version.
   
Library for Real Time Clock module (HCMODU0011).

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

#include "HCRTC.h"

/* Constructor to initiliase the I2C library*/
HCRTC::HCRTC(void)
{
	Wire.begin();
}

/* Library function to return year byte of last RTC read */
byte HCRTC::GetYear(void)
{
	return _RTCYear;
}

/* Library function to return month byte of last RTC read */
byte HCRTC::GetMonth(void)
{
	return _RTCMonth;
}

/* Library function to return day byte of last RTC read */
byte HCRTC::GetDay(void)
{
	return _RTCDate;
}

/* Library function to return hour byte of last RTC read */
byte HCRTC::GetHour(void)
{
	return _RTCHours;
}

/* Library function to return minute byte of last RTC read */
byte HCRTC::GetMinute(void)
{
	return _RTCMins;
}

/* Library function to return second byte of last RTC read */
byte HCRTC::GetSecond(void)
{
	return _RTCSecs;
}

/* Library function to return day of week byte of last RTC read */
byte HCRTC::GetWeekday(void)
{
	return _RTCWeekday;
}

/* Library function to return current time as a string */
String HCRTC::GetTimeString(void)
{
  char TimeString[] = "00:00:00";
  
  TimeString[0] = (_RTCHours / 10)+48;
  TimeString[1] = (_RTCHours % 10)+48;  
  TimeString[3] = (_RTCMins / 10)+48;
  TimeString[4] = (_RTCMins % 10)+48; 
  TimeString[6] = (_RTCSecs / 10)+48;
  TimeString[7] = (_RTCSecs % 10)+48;

  return TimeString;
}

/* Library function to return current date as a string */
String HCRTC::GetDateString(void)
{
  char DateString[] = "00/00/00";
  
  DateString[6] = (_RTCYear / 10)+48;
  DateString[7] = (_RTCYear % 10)+48;  
  DateString[3] = (_RTCMonth / 10)+48;
  DateString[4] = (_RTCMonth % 10)+48; 
  DateString[0] = (_RTCDate / 10)+48;
  DateString[1] = (_RTCDate % 10)+48;

  return DateString;
}

/* Library function to read current time and date from the RTC module */
void HCRTC::RTCRead(int I2CDS1307Add)
{
   Wire.beginTransmission(I2CDS1307Add);
   Wire.write(0);
   Wire.endTransmission();

   Wire.requestFrom(I2CDS1307Add, 7);

   _RTCSecs = BCD2DEC(Wire.read() & 0x7f);
   _RTCMins = BCD2DEC(Wire.read());
   _RTCHours = BCD2DEC(Wire.read() & 0x7f);
   _RTCWeekday  = Wire.read();
   _RTCDate = BCD2DEC(Wire.read());
   _RTCMonth = BCD2DEC(Wire.read());
   _RTCYear = BCD2DEC(Wire.read());
}

/* Library function to write current time and date from the RTC module */
void HCRTC::RTCWrite(int I2CDS1307Add, byte Year, byte Month, byte Day, byte Hour, byte Minuite, byte Second, byte DOW)
{
   Wire.beginTransmission(I2CDS1307Add);
   Wire.write(0);
   Wire.write(DEC2BCD(Second)); 
   Wire.write(DEC2BCD(Minuite));
   Wire.write(DEC2BCD(Hour));    
   Wire.write(DEC2BCD(DOW));
   Wire.write(DEC2BCD(Day));
   Wire.write(DEC2BCD(Month));
   Wire.write(DEC2BCD(Year));
   Wire.endTransmission();
}

/* Private library function to convert BCD to decimal format */
byte HCRTC::BCD2DEC(byte BCDValue)
{
   return ((BCDValue / 16) * 10) + (BCDValue & 0xF);
}

/* Private library function to convert decimal to BCD format */
byte HCRTC::DEC2BCD(byte DECValue)
{
   return ((DECValue / 10) * 16) + (DECValue % 10);
}

/* Library function to start a write cycle to the EEPROM */
void HCRTC::EEStartWrite(int I2C24C32Add, unsigned int ByteLocation)
{
  Wire.beginTransmission(I2C24C32Add);
  Wire.write((byte)(ByteLocation >> 8));
  Wire.write((byte)(ByteLocation & 0xFF));
}

/* Library function to write one byte of data to the EEPROM */
void HCRTC::EEWriteByte(byte Data)
{
  Wire.write(Data);
}

/* Library function to end a write cycle to the EEPROM */
void HCRTC::EEEndWrite(void)
{
  Wire.endTransmission();
}

/* Library function to start a read cycle from the EEPROM */
void HCRTC::EEStartRead(int I2C24C32Add, unsigned int ByteLocation)
{
  Wire.beginTransmission(I2C24C32Add);
  Wire.write((byte)(ByteLocation >> 8));
  Wire.write((byte)(ByteLocation & 0xFF));
  Wire.endTransmission();
}

/* Library function to read a byte of data from the EEPROM */
byte HCRTC::EEReadByte(int I2C24C32Add)
{
  Wire.requestFrom(I2C24C32Add, 1);
  if (Wire.available())
  {	
	return Wire.read();
  }else
  {
  	return 0xFF;
  }
}
