#include <Wire.h>

//for transmitter - 3wirebus
const int cePin = 8;
const int ckPin = 13;
const int daPin = 7;

//for receiver - I2C
double frequency=104.5; //starting frequency
unsigned int frequencyB = 4*(frequency*1000000+225000)/32768; //calculating PLL word;
unsigned char frequencyH=frequencyB>>8;
unsigned char frequencyL=frequencyB&0XFF;

void sendBit (boolean x)
{
  //TXer
  digitalWrite(daPin, x);
  delayMicroseconds(16);
  digitalWrite(ckPin, HIGH);
  delayMicroseconds(16);
  digitalWrite(ckPin, LOW);
}

void setup()
{
  //TXer
  pinMode(cePin, OUTPUT); pinMode(ckPin, OUTPUT); pinMode(daPin, OUTPUT);
  digitalWrite(cePin, LOW); digitalWrite(ckPin, LOW); digitalWrite(daPin, LOW);
  
  //RXer
  Wire.begin();
  //frequency=104.5; //starting frequency
  //frequencyB=4*(frequency*1000000+225000)/32768; //calculating PLL word
  //frequencyH=frequencyB>>8;
  //frequencyL=frequencyB&0XFF;
  delay(100);
  Wire.beginTransmission(0x60);   //writing TEA5767
  Wire.write(frequencyH);
  Wire.write(frequencyL);
  Wire.write(0xB0);
  Wire.write(0x10);
  Wire.write(0x00);
  Wire.endTransmission();
  
  delay(1000);
}
void loop()
{
  //TX-START////////////////////////////////////////////////////////////
  digitalWrite(cePin, HIGH);
  //104.5Mhz
  sendBit(1); //D00
  sendBit(0); //D01
  sendBit(1); //D02
  sendBit(0); //D03
  sendBit(1); //D04
  sendBit(0); //D05
  sendBit(0); //D06
  sendBit(0); //D07
  sendBit(0); //D08
  sendBit(0); //D09
  sendBit(1); //D10
  
  sendBit(0); //MONO=0
  sendBit(0); //PD0
  sendBit(0); //PD1
  sendBit(0); //PWD
  sendBit(0); //CP
  
  sendBit(0); //T00
  sendBit(0); //T01
  sendBit(1); //T02
  sendBit(1); //T03
  sendBit(0); //T04
  sendBit(0); //T05
  sendBit(1); //T06
  sendBit(0); //T07
  digitalWrite(cePin, LOW);
  delay(10000);
  //TX-END////////////////////////////////////////////////////////////////////

  /*digitalWrite(ckPin, true);
  delayMicroseconds(16);
  digitalWrite(ckPin, false);
  delayMicroseconds(16);
  */
}
