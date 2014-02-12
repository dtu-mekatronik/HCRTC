/* FILE     HCRTC_Read_Example.cpp
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

/* HOW TO USE THE REAL TIME CLOCK:

To use the library just include the Wire.h and HCRTC.h libraries and create an instance of the HCRTC library. E.g:

HCRTC HCRTC;


You can set the date and time with the following library function:

HCRTC.RTCWrite(I2C address, Year, Month, Day, Hour, Minuite, Second, Day of week);


And read the current date and time with the following library function:

HCRTC.RTCRead(I2C address);


Once the data has been read from the RTC module it can be accessed with the following library functions which return one byte of data of type byte:

HCRTC.GetDay()
HCRTC.GetMonth()
HCRTC.GetYear()
HCRTC.GetHour()
HCRTC.GetMinute()
HCRTC.GetSecond()
HCRTC.GetWeekday()


Or using the following string functions which return the time and date as a formatted string:

HCRTC.GetTimeString()
HCRTC.GetDateString()

*/



/* Include the wire library */
#include "Wire.h"
/* Include the Hobby Components RTC library */
#include <HCRTC.h>

/* Define the I2C addresses for the RTC and EEPROM */
#define I2CDS1307Add 0x68

/* Create an instance of HCRTC library */
HCRTC HCRTC;


void setup()
{
  Serial.begin(9600);
}

void loop()
{
    

    /* Read the current time from the RTC module */
    HCRTC.RTCRead(I2CDS1307Add);
   
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
    
    //DOW is 'day of the week'. It is a number from 1 to 7. Monday is 1 and Sunday is 7
    Serial.print(" DOW:");
    Serial.println(HCRTC.GetWeekday());
    
    /* Now output the same thing but using string functions instead: */
    Serial.print(HCRTC.GetDateString());
    Serial.print(" ");
    Serial.println(HCRTC.GetTimeString());
    
    /* Wait a second before reading again */
    delay(1000);  

}
