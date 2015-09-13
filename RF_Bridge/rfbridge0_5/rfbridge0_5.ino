
unsigned long cmd_power = 0x10EF08F7;     // Logitech Z5500 Power Code
unsigned long cmd_vol_up = 0x10EF58A7;    // Logitech Z5500 Volume Up Code
unsigned long cmd_vol_down = 0x10EF708F;  // Logitech Z5500 Volume Down Code
unsigned long cmd_mute = 0x10EF6897;      // Logitech Z5500 Mute Code
unsigned long cmd_eff = 0x10EFB847;       // Logitech Z5500 Effect Code

unsigned long cmd_tv_power = 0xF4BA2988;       // Samsung P2770HD Power Code
unsigned long cmd_tv_vol_up = 0xE0E0E01F;       // Samsung P2770HD Volume Up Code
unsigned long cmd_tv_vol_down = 0xE0E0D02F;    // Samsung P2770HD Volume Down Code
unsigned long cmd_tv_ch_up = 0xE0E048B7;       // Samsung P2770HD Channel Up Code
unsigned long cmd_tv_ch_down = 0xE0E008F7;       // Samsung P2770HD Channel Down Code
unsigned long cmd_tv_src = 0xE0E0807F;       // Samsung P2770HD Source Code
unsigned long cmd_tv_ent = 0xE0E016E9;       // Samsung P2770HD Enter Code
unsigned long cmd_tv_up = 0xE0E006F9;       // Samsung P2770HD Up Code
unsigned long cmd_tv_down = 0xE0E08679;       // Samsung P2770HD Down Code
unsigned long cmd_tv_left = 0xE0E0A659;       // Samsung P2770HD Left Code
unsigned long cmd_tv_right = 0xE0E046B9;       // Samsung P2770HD Right Code
unsigned long cmd_tv_mute = 0xE0E0F00F;       // Samsung P2770HD mute Code





// Include and Init RCSwitch Library Instance
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#include <IRLib.h>
IRsend IR_Sender;

// Set debut=1 for serial debug-output
uint8_t debug=0;

// Buffer size is 50 Characters
char buf[50];
uint8_t pos=0;

void setup()
{
  // Init serial communication
  Serial.begin(9600);
  // Set RF-Transmitter to Pin 4
  mySwitch.enableTransmit(4);
}

void loop() {
  uint8_t type;
  uint8_t value;
// Receive Cmd Syntax: " 'type' + ',' + 'value' + ';' "

if (Serial.available() > 0) {
  
  buf[pos]=Serial.read();  

  if (buf[pos]==';')
    {
      if (debug==1)
    {
      Serial.print("SScanF= ");
      Serial.println(sscanf(buf, "%d,%d\n", &type, &value));
      Serial.print("\nType: ");
      Serial.println(type);
      Serial.print("Value: ");
      Serial.println(value);
      Serial.print("Buffer: ");
      Serial.println(buf);
    }
          
     if (sscanf(buf, "%d,%d\n", &type, &value)==2)
       if (type<11)
         setswitch(type, value);
       else
         setIR(type);
      pos=0;
    }
  else
    pos++;                 
  }
  
  
}


void setswitch(uint8_t socket, uint8_t state)
{
 if (socket==1 || socket==2 || socket==3)
   for (uint8_t i=0;i<1;i++)
    {
     if(debug==1)
     {
     Serial.print("Repetition: ");
     Serial.println(i);
     }
     if (state==1) mySwitch.switchOn("11111", socket);
     if (state==0) mySwitch.switchOff("11111", socket);
     //delay(15);
    }
 // Codes for Florian Sassl's single-button RF-Switches   
 if(socket==4) mySwitch.send(5592256, 24);  // TV-Set
 if(socket==5) mySwitch.send(5592112, 24);  // Not in use
 if(socket==6) mySwitch.send(5592067, 24);  // Not in use
 
 // Space for more sockets
 if(socket==7) mySwitch.send(4433,24);
 if(socket==8) mySwitch.send("110101000100");
 if(socket==9) mySwitch.send("110101000010");
 
}

void setIR(uint8_t cmd)
{
   switch(cmd)
   {
     case 11: IR_Sender.send(NEC, cmd_vol_up, 32); break;
     case 12: IR_Sender.send(NEC, cmd_vol_down, 32); break;
     case 13: IR_Sender.send(NEC, cmd_power, 32); break;
     case 14: IR_Sender.send(NEC, cmd_mute, 32); break;
     case 15: IR_Sender.send(NEC, cmd_eff, 32); break;
     
     
     case 21: IR_Sender.send(NECX, cmd_tv_power, 32); break;
     case 22: IR_Sender.send(NECX, cmd_tv_vol_up, 32); break;
     case 23: IR_Sender.send(NECX, cmd_tv_vol_down, 32); break;
     case 24: IR_Sender.send(NECX, cmd_tv_ch_up, 32); break;
     case 25: IR_Sender.send(NECX, cmd_tv_ch_down, 32); break;
     case 26: IR_Sender.send(NECX, cmd_tv_mute, 32); break;
     case 27: IR_Sender.send(NECX, cmd_tv_src, 32); break;
     case 28: IR_Sender.send(NECX, cmd_tv_up, 32); break;
     case 29: IR_Sender.send(NECX, cmd_tv_down, 32); break;
     case 30: IR_Sender.send(NECX, cmd_tv_ent, 32); break;
   }
   delay(20);
}
