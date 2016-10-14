/*
** init.ino for JardIOT
** Made by Elio Desnoulez <e@desnoulez.fr>
** 
** Started on  Sat Sep  3 17:32:00 2016 Elio Desnoulez
** Last update Sat Sep  3 17:56:18 2016 Elio Desnoulez
*/

#include <SFE_BMP180.h>
#include "led.h"

void		bmp_init(SFE_BMP180 *bmp)
{
  delay(1000);//Wait recommended delay before accessing BMP180
  (bmp.begin()) ? succes() : error();
}

double		bmp_bmp(SFE_BMP180 *bmp)
{
  char		status = 0;
  double	press = 0;
  double	T_Bmp = 0;

  status = bmp.startTemperature();
  if (status != 0)
    {
      // Wait for the measurement to complete:
      delay(status);
      status = bmp.getTemperature(T_Bmp);
      if (status != 0)
        {
          Serial.print("Temperature BMP180 = ");
          Serial.print(T_Bmp, 2);
          Serial.println(" C");
          // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
          // If request is successful, the number of ms to wait is returned.
          status = bmp.startBmp(3);
	  if (status != 0)
	    {
	      delay(status);
	      status = bmp.getBmp(Press, T_Bmp);
	      if (status != 0)
		{
		  Serial.print("Bmp = ");
		  Serial.print(Press,2);
		  Serial.println(" hPa");
	        }
	      else
		Serial.println("error retrieving bmp measurement\n");
	    }
	  else
	    Serial.println("error starting bmp measurement\n");
	}
      else
	Serial.println("error retrieving temperature measurement\n");
    }
  else
    Serial.println("error starting temperature measurement\n");
}
