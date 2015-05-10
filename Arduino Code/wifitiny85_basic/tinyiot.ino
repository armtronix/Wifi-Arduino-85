/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>
int relay01 = 0;
int led = 1;
int relay02 = 2;

SoftwareSerial mySerial(3, 4); // RX, TX  Port 4 ---Rx Esp8266 Port 3---- Tx Esp8266

void setup()  
{
  // Open serial communications and wait for port to open:
  //Serial.begin(57600);
  //while (!Serial) { wait for serial port to connect. Needed for Leonardo only
 // }//


 // Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  pinMode(relay01, OUTPUT);
  pinMode(led, OUTPUT);
  mySerial.begin(4800);
  delay(1000);
  esp8266_setup();
}


void esp8266_setup()
{
  serialFlush();
  
 mySerial.println("AT+RST");
 delay(3000);
 display_serial();
 serialFlush();
 mySerial.println("ATE1");
 delay(2000);
 display_serial();
 mySerial.println("AT");
 delay(2000);
 display_serial();
 serialFlush();
 delay(1000);
 mySerial.println("AT+CWMODE=3");
 delay(2000);
 display_serial();
 serialFlush();
 delay(1000);
 mySerial.println("AT+CIFSR");
 delay(3000);
 display_serial();
 serialFlush();
 mySerial.println("AT+CIPMUX=1");
 delay(2000);
 display_serial();
 serialFlush();
 mySerial.println("AT+CIPSERVER=1");
 delay(2000);
 display_serial();
 serialFlush();
  //mySerial.println("AT+CIPAP?");
 //delay(2000);
 //display_serial();
 //serialFlush();
 mySerial.println("ATE1");
 delay(2000);
 display_serial();
}

void loop() // run over and over
{
  //if (mySerial.available())
  //  Serial.write(mySerial.read());
  //if (Serial.available())
  //delay(20);
  //mySerial.write(mySerial.read());
   display_serial_loop();
    serialFlush(); 
}
void serialFlush(){
  while(mySerial.available() > 0) {
    char t = mySerial.read();
  }
}  
unsigned long display_serial() {delay(100);}
/*
//unsigned long display_serial() 
//{
//char data[100];
//char m;


//while (mySerial.available() > 0)
    {  
      for(m=0; m<100; m++) 
        {
         if (mySerial.available() > 0) 
          {
           data[m]=mySerial.read();
          }
         else 
          {
           data[m]=0;
          }
        } 
    }
  
    
}
*/

unsigned long display_serial_loop() 
{
char data[100];
 int m=0;
 int n=100;
 int o=0;
 int x;
 int y;
 char ssid[24];
 for(m=0; m<n; m++) 
        {
        data[m]=0;     
        }
        
   while (mySerial.available() > 0)
       { 

               if(m<n)
                  {
                  data[m]=mySerial.read();
                  if(m>=2)
                    {
                    if(data[m-2]=='+')
                     {
                      if(data[m-1]=='I')
                       {
                         if(data[m]=='P')
                         {
                           o=m;
                         }
                         else
                         {
                         }
                       }
                       else
                       {
                       }
                    }
                    else
                    {
                    }
                  
                  }
                  else
                  {
                  }
                  m++;
                  delay(1);
                  }
               else
                 {
                  m=0;
                 }

   
       }
                        
     //for(m=0; m<n; m++) 
       //{
       if(data[o-2]=='+')
        {
                    if(data[o-1]=='I')
                     {
                       if(data[o]=='P')
                       {
                         //n=m;
                         //b=data[o+7];
                         //mySerial.println("AT+CIPSEND=0,2");
                         //delay(2000);
                         //mySerial.print(b);
                         //mySerial.print("\n\r");
                         //delay(200);
                         
                          if(((data[o+7]=='t')&&(data[o+8]=='u')&&(data[o+12]=='o')&&(data[o+13]=='n'))||((data[o+7]=='o')&&(data[o+8]=='n')))
                          {
                              digitalWrite(relay01, HIGH);
                              digitalWrite(led, HIGH);
                              mySerial.println("AT+CIPSEND=0,12");
                              delay(70);
                              mySerial.print("Relay is on"); 
                              mySerial.print("\n\r");

                            }
                          else if(((data[o+7]=='t')&&(data[o+8]=='u')&&(data[o+12]=='o')&&(data[o+13]=='f')&&(data[o+14]=='f'))||((data[o+7]=='o')&&(data[o+8]=='f')))
                            {
                              digitalWrite(relay01, LOW);
                              digitalWrite(led, LOW);
                              mySerial.println("AT+CIPSEND=0,13");
                              delay(70);
                              mySerial.print("Relay is off");
                              mySerial.print("\n\r"); 

                            }
                          else if((data[o+8]=='%')&&(data[o+11]==','))
                            { 
                               //char at_temp[15]="AT+CIPSEND=0,";
                               //char at_temp2[10]="AT+CWJAP=";
                               x=((((data[o+9])-'0')*10)+((data[o+10])-'0'))-2;   
                               //at_temp[13]=data[o+12];
                               //at_temp[14]=data[o+13];
                               //mySerial.println(at_temp);
                               //delay(200);
                               //mySerial.print(passwd);
                               //mySerial.print("\n\r");
                               //delay(2000);
                               //at_temp[13]=data[o+9];
                               //at_temp[14]=data[o+10];
                               //mySerial.println(at_temp);
                               //delay(200);
                               while(x>=0)
                                {
                                 ssid[x]=data[(o+12+x)];
                                 x--;
                                }
                               //mySerial.print(ssid);
                               //mySerial.print("\n\r");
                               
                              mySerial.print("AT+CWJAP=");
                              //mySerial.print("\"");
                              mySerial.print(ssid);
                              //mySerial.print(",");
                             // mySerial.print(passwd);
                              //mySerial.println("\"");
                              delay(50000);
                              esp8266_setup();
                             //break;

                            }

                         //break;
                        }
                       else
                       {

                       }
                     }
                     else
                         {

                         }
         }
       else
         {

         }
      //}
           
   /*    
    if((data[6]=='O')&&(data[7]=='n')&&(data[8]=='1'))
     {
      mySerial.println("AT+CIPSEND=0,17");
      delay(2000);
      mySerial.println("Relay one is on"); 
      //digitalWrite(relay01, HIGH);
      for(m=0; m<12; m++) 
        {
         data[m]=0;
         
        }
     }
    else if((data[6]=='O')&&(data[7]=='n')&&(data[8]=='2'))
     {
      mySerial.println("AT+CIPSEND=0,17");
      delay(2000);
      mySerial.println("Relay two is on"); 
      //digitalWrite(relay02, HIGH);
      for(m=0; m<12; m++) 
        {
         data[m]=0;
         
        }
     }
    else if((data[6]=='O')&&(data[7]=='f')&&(data[8]=='f')&&(data[9]=='1'))
     {
      mySerial.println("AT+CIPSEND=0,18");
      delay(2000);
      mySerial.println("Relay one is off"); 
      //digitalWrite(relay01, LOW);
      for(m=0; m<12; m++) 
        {
         data[m]=0;
         
        }  
     }
    else if((data[6]=='O')&&(data[7]=='f')&&(data[8]=='f')&&(data[9]=='2'))
     {
      mySerial.println("AT+CIPSEND=0,18");
      delay(2000);
      mySerial.println("Relay two is off"); 
      //digitalWrite(relay01, HIGH);
      for(m=0; m<12; m++) 
        {
         data[m]=0;
         
        }
     }
     else if((data[6]=='T')&&(data[7]=='e')&&(data[8]=='m')&&(data[9]=='p'))
      {
        
       mySerial.println("AT+CIPSEND=0,24");
       delay(2000);
       mySerial.print("Temperature is:");
       //mySerial.print(sensor.temp()); 
       mySerial.println(" C");
       
       for(m=0; m<12; m++) 
        {
         data[m]=0;     
        }  
     }
     */
     
     
   }
 
