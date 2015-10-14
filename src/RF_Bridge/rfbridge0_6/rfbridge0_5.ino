
unsigned long cmd_power = 0x10EF08F7;     // Logitech Z5500 Power Code
unsigned long cmd_vol_up = 0x10EF58A7;    // Logitech Z5500 Volume Up Code
unsigned long cmd_vol_down = 0x10EF708F;  // Logitech Z5500 Volume Down Code
unsigned long cmd_mute = 0x000C40BF;      // Logitech Z5500 Mute Code
unsigned long cmd_src = 0x10EFB847;       // Logitech Z5500 Effect Code

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
  long param[5];
// Receive Cmd Syntax: " 'type' + ',' + 'value' + ';' "

if (Serial.available() > 0) {
  
  buf[pos]=Serial.read();  

  if (buf[pos]==';')
    {     
    switch (buf[0])
   {
    case 'r': if(sscanf(buf, "%d, %d, %x, %d, %d, %d\n", &type, &param[0], &param[1], &param[2], &param[3], &param[4])==6) sendRF(param[0], param[1], param[2], param[3], param[4]); break;
    case 'i': if(sscanf(buf, "%d, %d\n", &type, &param[0], &param[1], &param[2])==4) sendIR(param[0], param[1], param[2]); break;
   } 
      pos=0;
    }
  else
    pos++;                 
  }
  
  
}


void sendRF(uint8_t protocol, long data, uint8_t bits, uint8_t state, uint8_t repetitions)
{
  for (uint8_t i=0; i<repetitions; i++)
  switch (protocol)
  {
    case 1: 
            switch (state)
            {
             case 0: mySwitch.switchOff(int(data),bits);
             case 1: mySwitch.switchOn(int(data),bits);
            }
    break;
    case 2: break;
            mySwitch.send(data, bits);
    case 3: break;
            mySwitch.send(data);
  }
  
  
  
  
 if (socket==1 || socket==2 || socket==3)
   for (uint8_t i=0;i<3;i++)
    {
     if(debug==1)
     {
     Serial.print("Repetition: ");
     Serial.println(i);
     }
     if (state==1) mySwitch.switchOn("11111", socket);
     if (state==0) mySwitch.switchOff("11111", socket);
     delay(15);
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

void sendIR(uint8_t protocol, long data, uint8_t bits)
{
  Serial.println("Switching");
   switch(cmd)
   {
     case 11: IR_Sender.send(NEC, cmd_vol_up, 32); Serial.println("Sending vol_up"); break;
     case 12: IR_Sender.send(NEC, cmd_vol_down, 32); Serial.println("Sending vol_down"); break;
     case 13: IR_Sender.send(NEC, cmd_power, 32); Serial.println("Sending On/Off"); break;
     case 14: IR_Sender.send(NEC, cmd_src, 32); Serial.println("Sending Effect"); break;
   }
   delay(20);
}
