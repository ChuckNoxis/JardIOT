//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
const int	ledRed = 11;
const int	ledGreen = 10;
const int	ledBlue = 9;

void	error(int error_n)
{
  int	wait;
  int	error;
  int	i;

  error	= error_n * 300;
  wait = 1000 - error;
  /*
  ** Nous vous devons une pause eternelllle.
  */
  while (1)
    {
      i = error_n;
      while (i)
	{
	  setColor(255, 0, 0);
	  delay(wait);
	  setColor(0, 0, 0);
	  delay(wait);
	  i--;
	}
      delay(5000);
    }
}

void		success(int succes_n)
{
  int	wait;
  int	succes;

  succes = succes_n * 300;
  wait = 1000 - succes;
  while (succes_n)
    {
      setColor(255, 0, 0);
      delay(wait);
      setColor(0, 0, 0);
      delay(wait);
      succes_n--;
    }
}

void	setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue);
}
