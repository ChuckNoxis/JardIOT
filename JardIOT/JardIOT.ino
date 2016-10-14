/*
** init.ino for JardIOT
** Made by Elio Desnoulez <e@desnoulez.fr>
** 
** Started on  Sat Sep  3 17:32:00 2016 Elio Desnoulez
** Last update Sun Sep  4 03:16:59 2016 Elio Desnoulez
*/

#include <dht.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include "led.h"

#define dht_dpin A0

dht		DHT;
SFE_BMP180	pressure;

void		setup()
{
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for Leonardo only
  bmp_init(&pressure);
  Serial.println("Setup complete.");
}

void		loop()
{
  char		status;
  double	T_Dht;
  double	Hum;
  double	T_Bmp;
  double	Press;
  double	av;

  DHT.read11(dht_dpin);
  Serial.print("Humidity = ");
  Serial.print(Hum = DHT.humidity);
  Serial.println("%");
  Serial.print("Temperature DHT = ");
  Serial.print(T_Dht = DHT.temperature);
  Serial.println(" C");
  
  Serial.print("Average Temp :");
  Serial.print(av = ((T_Bmp + T_Dht) /2));
  Serial.println(" C");
}
