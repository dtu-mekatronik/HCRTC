/* FILE     HCRTC_Example.cpp
   DATE:    23/12/13
   VERSION: 0.2
   AUTHOR:  Andrew Davies

This is an example of how to use the Hobby Components RTC library to read and
write to and from the DS1307 real time clock 24C32 EEPROM. The library is intended
to be used with our RTC clock module (HCMODU0011), but should work fine with any
module that uses a DS1307 device.

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

/*
FILE HCRTC_Write_time
DATE: 10/2/14
VERSION:0.1
AUTHOR: Ali Ozkil

Additional routines to set time via Arduino Serial Terminal
time should be sent in the form of: year, month, date, hour, minute, second, day of week

E.g: write  <<  14,2,10,9,28,0,1 >> on serial terminal and press enter to set the date and time to : 2014 February 10th, 09:28:00, Monday


*/


/* Include the wire library */
#include "Wire.h"
/* Include the Hobby Components RTC library */
#include <HCRTC.h>

/* Define the I2C address for the RTC */
#define I2CDS1307Add 0x68

/* Create an instance of HCRTC library */
HCRTC HCRTC;


void setup()
{
  Serial.begin(9600);

  /* Use the RTCWrite library function to read the time and date that is already set on the device. */
  HCRTC.RTCRead(I2CDS1307Add);
  /* Read the current time from the RTC module */

  /* Output the information to the UART */
  Serial.print(HCRTC.GetDay());
  Serial.print("/");
  Serial.print(HCRTC.GetMonth());
  Serial.print("/");
  Serial.print(HCRTC.GetYear());
  Serial.print(" ");

  Serial.print(HCRTC.GetHour());
  Serial.print(":");
  Serial.print(HCRTC.GetMinute());
  Serial.print(":");
  Serial.print(HCRTC.GetSecond());
  Serial.print(" DOW:");
  Serial.println(HCRTC.GetWeekday());

  /* Now output the same thing but using string functions instead: */
  Serial.print(HCRTC.GetDateString());
  Serial.print(" ");
  Serial.println(HCRTC.GetTimeString());
}

void loop()
{
  /* Continuously wait for input from Serial Terminal */

  while (Serial.available() > 0) {
    /* Use the RTCWrite library function to set the time and date.
    Parameters are: I2C address, year, month, date, hour, minute, second,
    day of week */
    int year = Serial.parseInt();
    int month = Serial.parseInt();
    int date = Serial.parseInt();
    int hour = Serial.parseInt();
    int minute = Serial.parseInt();
    int second = Serial.parseInt();
    int dayOfWeek = Serial.parseInt();
    HCRTC.RTCWrite(I2CDS1307Add, year, month, date, hour, minute, second, dayOfWeek);
    delay(100); // wait a little for the buffers

    /* Display the new time*/
    Serial.print(" The new time& date is set:  ");
    Serial.print(HCRTC.GetDateString());
    Serial.print(" ");
    Serial.println(HCRTC.GetTimeString());
  }
  delay(1000); //wait for one second
}
