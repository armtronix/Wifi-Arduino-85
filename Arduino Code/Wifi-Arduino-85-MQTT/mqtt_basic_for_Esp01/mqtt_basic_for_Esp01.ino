/*
 Basic MQTT example 
 
  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
char* topic = "Relay_Control";
const char *ssid =  "Omega_Naren";   // cannot be longer than 32 characters!
const char *pass =  "naren_1234578906";   //

// Update these with values suitable for your network.
//IPAddress server(192, 168, 1, 9);
IPAddress server(192, 168, 3, 1);
//IPAddress server(10, 5, 5, 1);//eg of broker ip need to be ur ip

WiFiClient wclient;
PubSubClient client(wclient, server,1883);


#define BUFFER_SIZE 100

void callback(const MQTT::Publish& pub) {
  //Serial.print(pub.topic());
  //Serial.print(" => ");
  Serial.println(pub.payload_string());
  String command = pub.payload_string();
   
}

void setup() {
  // Setup console
  Serial.begin(4800);
  delay(10);
  Serial.println("Starting");
  Serial.println("Mqtt Client");
  
}

void loop() {
  char serialinData[30];
  char serialinChar=-1; 
  byte serialIndex = 0;
  int stringComplete = 0;
  
  if (WiFi.status() != WL_CONNECTED) {
   // Serial.print("Connecting to ");
   // Serial.print(ssid);
   // Serial.println("...");
    WiFi.begin(ssid, pass);
   
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      return;
    }
      
  //  Serial.println("WiFi connected");
  //  Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect("esp_mqtt_Client")) {
        client.set_callback(callback);
        client.subscribe(topic);
        client.publish(topic, "Send or receive serial data from controller ");
      }
    }

    if (client.connected())
      client.loop();
      
      while (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):

    if(serialIndex < 29) // One less than the size of the array
        {
            serialinChar = Serial.read(); // Read a character
            serialinData[serialIndex] = serialinChar; // Store it
            serialIndex++; // Increment where to write next
            serialinData[serialIndex] = '\0'; // Null terminate the string
        }
    
    //String attiny_Data = String(Serial.read(),HEX);
    if (serialinChar == '\n') {
      stringComplete=1;
    }
    
   }
   delay(350);
   
    if(stringComplete==1)
    {
         //Serial.println(WiFi.localIP());
         //delay(300);
         client.publish(topic,serialinData);
         
         for (int i=0;i<19;i++)
         {
            serialinData[i]=0;
         }
        serialIndex=0;
        stringComplete=0;
        
     }
  }
 
   
}

