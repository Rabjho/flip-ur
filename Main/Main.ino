#include <Wire.h>
#include "MMA7660.h"
#include "rgb_lcd.h"
#include "FlipperClass.h"
#include "RandGen.h"

float x, y, z;
int state;
const int maxState = 4;

MMA7660 accelmeter;
rgb_lcd lcd;
Flipper flipX;

void setup() {
  state = 0;
  x,y,z = 0.0;
  
  Serial.begin(9600); // init random serial noise to random generator.
  randomSeed(analogRead(0));

	lcd.begin(16, 2);
	accelmeter.init(); 
}

void loop()
{ 

  accelmeter.getAcceleration(&x, &y, &z); // Tager memory address som input
	lcd.clear();
	lcd.print(x);

  if(flipX.onFlip(x)!=0)
  {
    digitalWrite(4,HIGH);
  } 
  else 
  {
    digitalWrite(4, LOW);
  }
  delay(50);

  if(flipX.onFlip(x)==1)
  {
    if(state == maxState) 
    {
      state = 0;
    } 
    else 
    {
      state += 1;  
    }
  }

  switch(state)
  {
    case 1:
      char elev = classState();
      lcd.print(elev);
      break;
    case 2:

      break;
    case 3:

      break;
    case maxState:

      break;
    default:
      break;
  }
}
