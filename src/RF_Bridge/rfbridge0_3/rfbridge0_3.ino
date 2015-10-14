/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <RCSwitch.h>
#include <IRremote.h>

IRsend irsend;
uint8_t debug=0;
RCSwitch mySwitch = RCSwitch();
char buf[50];
uint8_t pos=0;
int s1, s2, s3, s4, s5, s6;
uint8_t switches[10];
uint8_t socket;


void setup()
{
  Serial.begin(9600);
  mySwitch.enableTransmit(4);
}

void loop() {
  
// Receive Cmd Syntax: " 'type' + ',' + 'value' + ';' "

if (Serial.available() > 0) {

  buf[pos]=Serial.read();
  //Uncomment for Serial-Debugging
  //Serial.print("buf[");
  //Serial.print(pos, DEC);
  //Serial.print("] = ");
  //Serial.print(buf[pos]);         

  if (buf[pos]==';')
    {
      if (debug==1)
    {
      Serial.print("SScanF= ");
      Serial.println(sscanf(buf, "%d,%d\n", &socket, &switches[buf[0]]));
      
      Serial.print("\nSocket: ");
      Serial.println(socket);
      Serial.print("Value: ");
      Serial.println(switches[buf[0]]);
      Serial.print("Buffer: ");
      Serial.println(buf);
    }
          
     if (sscanf(buf, "%d,%d\n", &socket, &switches[buf[0]])==2)
       if (socket<11)
         setswitch(socket, switches[buf[0]]);
       else
         setIR(socket);
      pos=0;
    }
  else
    pos++;                 
  }
  
  
}


void setswitch(uint8_t s, uint8_t v)
{
 if (s==1 || s==2 || s==3)
   for (uint8_t i=0;i<3;i++)
    {
     if(debug==1)
     {
     Serial.print("Repetition: ");
     Serial.println(i);
     }
     if (v==1) mySwitch.switchOn("11111", s);
     if (v==0) mySwitch.switchOff("11111", s);
     delay(15);
    }
    
 if(s==4) mySwitch.send(5592256, 24);
 if(s==5) mySwitch.send(5592112, 24);
 if(s==6) mySwitch.send(5592067, 24);
 
 if(s==7) mySwitch.send(4433,24);
 if(s==8) mySwitch.send("110101000100");
 if(s==9) mySwitch.send("110101000010");
 
}

void setIR(uint8_t cmd)
{
  Serial.println("Switching");
   switch(cmd)
   {
     case 13:  irsend.sendNEC(0x10EF08F7, 32); Serial.println("Sending On/Off"); break;
     case 11:  irsend.sendNEC(0x10EF58A7, 32); Serial.println("Sending vol_up"); break;
     case 12:  irsend.sendNEC(0x10EF708F, 32); Serial.println("Sending vol_down"); break;
   }
   delay(20);
}
