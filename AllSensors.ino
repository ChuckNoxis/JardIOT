#include <SD.h>
#include <dht.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include "RTClib.h"
#include "state.h"

#define dht_dpin A0

dht		DHT;
File		myFile;
SFE_BMP180	pressure;
RTC_DS1307	RTC;

void	setup()
{
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for Leonardo only
  /*
  **
  ** Initialisation of the BMP180
  **
  */
  delay(1000);//Wait recommended delay before accessing BMP180
  (pressure.begin()) ? succes(1) : error(1);
  /*
  **
  ** Initialisation of the SD Card
  **  
  */
  pinMode(10, OUTPUT);
  if (!SD.begin(4))
    error(2);
  else
    succes(2);
  /*
  **
  ** Initialisation of the RTC
  **
  */
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning())
    error(3);
  else
    success(3);
  // This section grabs the current datetime and compares it to
  // the compilation time.  If necessary, the RTC is updated.
  DateTime now = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime())
    {
      setColor(0, 255, 63);
      RTC.adjust(DateTime(__DATE__, __TIME__));
      delay(1000);
      setColor(0, 0, 0);
    }
  Serial.println("Setup complete.");
}

void		givemethetime()
{
  DateTime	now = RTC.now();
  int		min;
  int		second;

  minute = now.minute();
  second = now.second();
  if ((minute == 30 || minute == 0) && second == 0)
    Serial.print("Ninja !");
}

void		loop()
{
  char		status;
  double	T_Dht;
  double	Hum;
  double	T_Bmp;
  double	Press;
  double	av;

  givemethetime();
  DHT.read11(dht_dpin);
  Serial.print("Humidity = ");
  Serial.print(Hum = DHT.humidity);
  Serial.println("%");
  Serial.print("Temperature DHT = ");
  Serial.print(T_Dht = DHT.temperature);
  Serial.println(" C");
  status = pressure.startTemperature();
  if (status != 0)
    {
      // Wait for the measurement to complete:
      delay(status);
      status = pressure.getTemperature(T_Bmp);
      if (status != 0)
        {
          Serial.print("Temperature BMP180 = ");
          Serial.print(T_Bmp, 2);
          Serial.println(" C");
          // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
          // If request is successful, the number of ms to wait is returned.
          status = pressure.startPressure(3);
	  if (status != 0)
	    {
	      delay(status);
	      status = pressure.getPressure(Press, T_Bmp);
	      if (status != 0)
		{
		  Serial.print("Pressure = ");
		  Serial.print(Press,2);
		  Serial.println(" hPa");
	        }
	      else
		Serial.println("error retrieving pressure measurement\n");
	    }
	  else
	    Serial.println("error starting pressure measurement\n");
	}
      else
	Serial.println("error retrieving temperature measurement\n");
    }
  else
    Serial.println("error starting temperature measurement\n");
  Serial.print("Average Temp :");
  Serial.print(av = ((T_Bmp + T_Dht) /2));
  Serial.println(" C");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("log.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile)
    {
      // Get the current time
      DateTime	now = RTC.now();
      // Display the current time
      myFile.print(now.day(), DEC);
      myFile.print('/');
      myFile.print(now.month(), DEC);
      myFile.print('/');
      myFile.print(now.year(), DEC);
      myFile.print(',');
      myFile.print(now.hour(), DEC);
      myFile.print(':');
      myFile.print(now.minute(), DEC);
      myFile.print(':');
      myFile.print(now.second(), DEC);
      myFile.print(",\"");
      myFile.print(T_Dht);
      myFile.print("\",\"");
      myFile.print(T_Bmp,2);
      myFile.print("\",\"");
      myFile.print(av);
      myFile.print("\",\"");
      myFile.print(Hum);
      myFile.print("\",\"");
      myFile.print(Press,2);
      myFile.println("\"");
      Serial.print("Writing to log.txt...");
      // close the file
      myFile.close();
      Serial.println("done.");
    }
  else
    Serial.println("error opening log.txt");
  //re-open the file for reading:
  myFile = SD.open("log.txt");
  if (myFile)
    {
      Serial.println("log.txt:");
      // read from the file until there's nothing else in it:
      while (myFile.available())
	Serial.write(myFile.read());
      // close the file:
      myFile.close();
    }
  else
    Serial.println("error opening log.txt");
}
