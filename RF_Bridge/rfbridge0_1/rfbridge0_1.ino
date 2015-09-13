/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
char buf[50];
uint8_t pos=0;
int s1, s2, s3, s4, s5, s6;
void setup()
{
  Serial.begin(9600);
  mySwitch.enableTransmit(4);
}

void loop() {



	// Receive Cmd Syntax: "Type,value1,value2,value3;"

	//	1: RC-Switch	"Type,s1,s2,s3;"

	//	2: Laser		"Type,e,x,y;"

	//	3: RGB			"Type,r,g,b;"

	//	4: IR			"Type,cmd;"

	if (Serial.available() > 0) {

              buf[pos]=Serial.read();

			  

			  //Uncomment for Serial-Debugging

              Serial.print("buf[");

              Serial.print(pos, DEC);

              Serial.print("] = ");

              Serial.println(buf[pos]);

              

			if (buf[pos]==';')

              {

              Serial.print("SScanF= ");

			  switch (buf[0])

			  {

				case '1':

						Serial.println(sscanf(buf, "%d,%d,%d,%d,%d,%d,%d\n", &pos, &s1, &s2, &s3, &s4, &s5, &s6));

						setswitch();

						Serial.print("s1 = ");

						Serial.println(s1);

						Serial.print("s2 = ");

						Serial.println(s2);

						Serial.print("s3 = ");

						Serial.println(s3);

					break;

			}			  

              //Serial.println("Done!");

              pos=0;

              }

              else

              pos++;                 

	}

}

void setswitch()
{
 for (uint8_t i=0;i<2;i++)
  {
   Serial.print("Sending No. ");
   Serial.println(i);
   if(s1==1) mySwitch.switchOn("11111",1);
   if(s1==0) mySwitch.switchOff("11111",1);
   if(s2==1) mySwitch.switchOn("11111",2);
   if(s2==0) mySwitch.switchOff("11111",2);
   if(s3==1) mySwitch.switchOn("11111",3);
   if(s3==0) mySwitch.switchOff("11111",3);
   delay(25);
  }
   if(s4==1) mySwitch.send(5592256, 24);
   if(s5==1) mySwitch.send(5592112, 24);
   if(s6==1) mySwitch.send(5592067, 24);
}
