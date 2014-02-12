This Arduino library has been written to allow easy use DS1307 based real time clock modules such as our RTC module HCMODU0011. The library also contains functions to read and write to EEPROM memory which is also included in this RTC module. Communication with the module is via the standard Arduino I2C interface on pins A4 (SDA) & A5 (SCL) for an Uno

You will need to download (please log in to download the library) and unzip this library to the Arduino development environments library area

On Windows: 
My Documents\Arduino\libraries\
My Documents\Arduino\libraries\
My Documents\Arduino\libraries\

On Mac: 
Documents/Arduino/libraries/
Documents/Arduino/libraries/
Documents/Arduino/libraries/
or similarly for Linux. 


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

You cab connect the module to Arduino using this configuration:

GND-Arduino GND
Vcc-Arduino 5V
SDA-Arduino A4
SCL-Arduino A5


First time you use the RTC module, you would like to run the HCRTC_Write_Time function. Go to File> Examples > HCRTC > HCRTC_Write_Time and upload the sketch to your Arduino. Open the serial monitor and write the time to the module in the form of: 

year, month, date, hour, minute, second, day of week

E.g: write  14,2,10,9,28,0,1 on serial terminal and press enter to set the date and time to : 2014 February 10th, 09:28:00, Monday

You only need to write the time once to the module, next time you connect it to Arduino, it should remember the correct time. 

Once you write the correct time, you can write your own Arduino code to utilize the RTC module. Check the "HCRTC_Read_Example" file to see how RTC module can be used to read time and date (under File > Examples> HCRTC> HCRTC_Read_Example)
