#include <RBDdimmer.h>
#include <SoftwareSerial.h>
#define rx_pin 0
#define tx_pin 1
#define pwm 3
#define zerocross 2
#define resetPin 9

SoftwareSerial BTSerial(rx_pin, tx_pin);
dimmerLamp lampu(pwm);

String BTInput;
int waiting = 1000;
int minBright = 0;
int maxBright = 95;
int value, counter;
int storeData[300];
boolean isPowered = false;

void setup()
{ 
    digitalWrite(resetPin, HIGH);
    BTSerial.begin(9600);
    pinMode(resetPin,OUTPUT);
    lampu.begin(NORMAL_MODE,ON);             
}

void loop()
{
  arrayCheck();
  if (BTSerial.available())
  {
    BTInput = BTSerial.readString();
    powerCheck();
      if (value <= maxBright && isPowered == false)
      {
        delay(waiting);
        lampu.setPower(minBright);
      }
    
      else if (value > minBright && isPowered == true)
      {
        delay(waiting);
        lampu.setPower(value);
      }
  }

  else if (value == minBright)
  {
    delay(waiting);
    lampu.setPower(storeData[counter-1]);
  }
}

void powerCheck()
{
    if (BTInput.equals("ON"))
    {
      isPowered = true;
    }

    else if (BTInput.equals("OFF"))
    {
      isPowered = false;
    }
    
    else
    {
      value = BTInput.toInt();
      counter = counter + 1;
      storeData[counter] = value;
    }
}

void arrayCheck()
{
  if (counter == 295)
  {
    digitalWrite(resetPin, LOW);
  }
}
