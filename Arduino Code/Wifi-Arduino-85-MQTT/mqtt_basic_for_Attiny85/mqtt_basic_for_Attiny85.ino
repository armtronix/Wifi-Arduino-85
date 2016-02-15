/*
  Mqtt for Attiny85 microcontroller to send serial commands to esp8266-01 module 
  for Wifi Arduino 85 board
 

 
 */
#include <SoftwareSerial.h>
int led = 0;
int relay01 = 1;
int pir = 2;
//int PIR_STATUS_FLAG = 0;
boolean ENABLE_SENSOR =0;
boolean PREVIOUS_STATE =0;
int pir_status;

SoftwareSerial mySerial(3, 4); // RX, TX  Port 4 ---Rx Esp8266 Port 3---- Tx Esp8266

void setup()  
{
  // Open serial communications and wait for port to open:
  //Serial.begin(57600);
  //while (!Serial) { wait for serial port to connect. Needed for Leonardo only
 // }//


 // Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  pinMode(led, OUTPUT);
  pinMode(relay01, OUTPUT);
  pinMode(pir, INPUT);
  mySerial.begin(4800);
  delay(1000);
  
}



void loop() // run over and over
{
  //if (mySerial.available())
  //  Serial.write(mySerial.read());
  //if (Serial.available())
  //delay(20);
  //mySerial.write(mySerial.read());
   display_serial_loop();
   // serialFlush(); 
}
//void serialFlush(){
//  while(mySerial.available() > 0) {
//    char t = mySerial.read();
//  }
//}  
//unsigned long display_serial() {delay(100);}
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
char data[45];
 int m=0;
 int n=45;
 int o=0;
 int x;
 int y;
 char ssid[24];
 pir_status=digitalRead(pir);
 

 
 
 
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
                      if(data[m-1]=='A')
                       {
                         if(data[m]=='T')
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
                    if(data[o-1]=='A')
                     {
                       if(data[o]=='T')
                       {
                         //n=m;
                         //b=data[o+7];
                         //mySerial.println("AT+CIPSEND=0,2");
                         //delay(2000);
                         //mySerial.print(b);
                         //mySerial.print("\n\r");
                         //delay(200); //+IP,x,xx:turn_on //+APturn_on
                                       //  o
                          if(((data[o+1]=='t')&&(data[o+2]=='u')&&(data[o+6]=='o')&&(data[o+7]=='n'))||((data[o+1]=='o')&&(data[o+2]=='n')))
                          {
                              digitalWrite(relay01, HIGH);
                              digitalWrite(led, LOW);
                              //mySerial.println("AT+CIPSEND=0,12");
                              //delay(70);
                              mySerial.print("Relay on"); 
                              mySerial.print("\n\r");

                            }//+APturn_off
                          else if(((data[o+1]=='t')&&(data[o+2]=='u')&&(data[o+6]=='o')&&(data[o+7]=='f')&&(data[o+8]=='f'))||((data[o+1]=='o')&&(data[o+2]=='f')))
                            {
                              digitalWrite(relay01, LOW);
                              digitalWrite(led, HIGH);
                              //mySerial.println("AT+CIPSEND=0,13");
                              //delay(70);
                              mySerial.print("Relay off");
                              mySerial.print("\n\r"); 

                            }
                          else if(((data[o+1]=='s')&&(data[o+2]=='t')&&(data[o+3]=='a')&&(data[o+5]=='t')))
                            {
                               //+APstart
                               //  o
                              //digitalWrite(led, LOW);
                              ENABLE_SENSOR=1;
                             // mySerial.println("AT+CIPSEND=0,15");
                             // delay(70);
                              mySerial.print("Sensor Enb");
                              mySerial.print("\n\r"); 

                            }
                         else if(((data[o+1]=='s')&&(data[o+2]=='t')&&(data[o+3]=='o')))
                            {
                              //+APstop
                              //digitalWrite(led, HIGH);
                              ENABLE_SENSOR=0;
                             // mySerial.println("AT+CIPSEND=0,16");
                             // delay(70);
                              mySerial.print("Sensor Dis");
                              mySerial.print("\n\r"); 

                            }
                          else if(((data[o+1]=='s')&&(data[o+2]=='t')&&(data[o+5]=='u')))
                            { //+APstatus
                              if(pir_status==1)
                              {
                                //digitalWrite(led, HIGH);
                               // mySerial.println("AT+CIPSEND=0,20");
                               // delay(70);
                                mySerial.print("PIR HIGH");
                                mySerial.print("\n\r"); 
                              }
                              else if(pir_status==0)
                              {
                                //digitalWrite(led, LOW);
                                //mySerial.println("AT+CIPSEND=0,18");
                                //delay(70);
                                mySerial.print("PIR LOW");
                                mySerial.print("\n\r");
                              }
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
delay(500);
  if((ENABLE_SENSOR ==1) && (pir_status ==1)&& (PREVIOUS_STATE ==0))
 {
   mySerial.print("PIR HIGH");
   mySerial.print("\n\r");
   PREVIOUS_STATE=1;
   digitalWrite(relay01, HIGH);
   digitalWrite(led, LOW);
 }
 else if((ENABLE_SENSOR ==1) && (pir_status==0)&& (PREVIOUS_STATE==1))
 {
  mySerial.print("PIR LOW");
  mySerial.print("\n\r");
  PREVIOUS_STATE=0;
   digitalWrite(relay01, LOW);
   digitalWrite(led, HIGH);
 }
 else
 {
 }   
     
   }
 
