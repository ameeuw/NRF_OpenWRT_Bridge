#define TOPBIT 0x80000000
#define NEC_HDR_MARK      9000
#define NEC_HDR_SPACE     4500
#define NEC_BIT_MARK       560
#define NEC_ONE_SPACE     1690
#define NEC_ZERO_SPACE     560
#define NEC_BITS           32

#define DUTY_CYCLE         1/3       // Carrier duty cycle
#define PERIOD             26        // 38kHz, 1/38kHz =~ 26us
#define ACTIVE_HIGH       (PERIOD * DUTY_CYCLE)
#define ACTIVE_LOW        (PERIOD - (PERIOD * DUTY_CYCLE))

int IR_LED = 3;
unsigned long cmd_power = 0x10EF08F7;     // Logitech Z5500 Power Code
unsigned long cmd_vol_up = 0x10EF58A7;    // Logitech Z5500 Volume Up Code
unsigned long cmd_vol_down = 0x10EF708F;  // Logitech Z5500 Volume Down Code
unsigned long cmd_mute = 0x000C40BF;      // Logitech Z5500 Mute Code
unsigned long cmd_src = 0x10EFB847;       // Logitech Z5500 Effect Code

// Include and Init RCSwitch Library Instance
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

// Set debut=1 for serial debug-output
uint8_t debug=0;

// Buffer size is 50 Characters
char buf[50];
uint8_t pos=0;

void setup()
{
  // Init serial communication
  Serial.begin(9600);
  // Set IR-Transmitter to IR_LED-Pin
  pinMode(IR_LED, OUTPUT);
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

void setIR(uint8_t cmd)
{
  Serial.println("Switching");
   switch(cmd)
   {
     case 11: sendNEC(cmd_vol_up); Serial.println("Sending vol_up"); break;
     case 12: sendNEC(cmd_vol_down); Serial.println("Sending vol_down"); break;
     case 13: sendNEC(cmd_power); Serial.println("Sending On/Off"); break;
     case 14: sendNEC(cmd_src); Serial.println("Sending Effect"); break;
     case 15: digitalWrite(IR_LED, HIGH); break;
     case 16: digitalWrite(IR_LED, LOW); break;
   }
   delay(20);
}

void mark(long time)
{
  for(int i = 0; i < (time / PERIOD); i++)
  {
    digitalWrite(IR_LED, HIGH);
    delayMicroseconds(ACTIVE_HIGH - 4); // digitalWrite() takes 4us
    digitalWrite(IR_LED, LOW);
    delayMicroseconds(ACTIVE_LOW - 4); // digitalWrite() takes 4us
  }  
}

void sendNEC(unsigned long data)
{
    // Leader code
    mark(NEC_HDR_MARK);
    delayMicroseconds(NEC_HDR_SPACE); 
    for (int i = 0; i < NEC_BITS; i++)
    {
      mark(NEC_BIT_MARK);
      if (data & TOPBIT)
        delayMicroseconds(NEC_ONE_SPACE);
      else
        delayMicroseconds(NEC_ZERO_SPACE);
  
      data <<=1;
    }
    // stop bit
    mark(NEC_BIT_MARK); 
}  
