/*
** led.ino for JardIOT
** Made by Elio Desnoulez <e@desnoulez.fr>
** 
** Started on  Sat Sep  3 11:03:20 2016 Elio Desnoulez
** Last update Sat Sep  3 17:18:34 2016 Elio Desnoulez
*/

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
const int	redPin = 11;
const int	greenPin = 10;
const int	bluePin = 9;


//Blink in red if you have a problem (like an unwired sensor)
void	error()
{
  while (1)
    {
      setColor(255, 0, 0);
      delay(1000);
      setColor(0, 0, 0);
      delay(1000);
    }
}

//Blink in green if no problem
void	success()
{
  for (int i = 0; i < 2; ++i)
    {
      setColor(255, 0, 0);
      delay(500);
      setColor(0, 0, 0);
      delay(500);
    }
}

void	setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
