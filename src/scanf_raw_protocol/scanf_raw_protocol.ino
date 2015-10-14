char buf[50];
uint8_t nargs;
char cmd;
uint8_t pos=0;
int value[5];

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
// Receive Cmd Syntax: " '?#ofarguments' + ',' + 'type' + ',' + 'value[0]' ... +  ';' "

if (Serial.available() > 0) {
  
  buf[pos]=Serial.read();  

  if (buf[pos]==';')
    {     
      Serial.println("sscanf...");
      Serial.println(buf);
      // Test if number of read arguments is correct
      // TODO!! eventuell noch prüfsumme am als letztes element
      if (sscanf(buf,"?%d,%c,%d,%d,%d,%d,%d\n", &nargs, &cmd, &value[0], &value[1], &value[2], &value[3], &value[4])==nargs+2)
        {
          Serial.print("nargs = ");
          Serial.println(nargs);
          Serial.print("cmd = ");
          Serial.println(cmd);
          for (uint8_t i=0;i<5;i++) Serial.println(value[i]);
          
          switch (cmd)
          {
          case 'g': Serial.println("GENERIC"); 
            //send all values 
            break;
          case 'r': Serial.println("RGB"); 
            break;
          case 'i': Serial.println("IR"); 
            break;
          case 's': Serial.println("SOCKETS"); 
            break;
          default: Serial.println("UNKNOWN");
          }
        }
      pos=0;
    }
  else
    pos++;                 
  }
  
  
}
