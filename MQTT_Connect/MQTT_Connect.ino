#include "SoftwareSerial.h"
SoftwareSerial mySerial(D2, D3);//RX - TX
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "redmi";  //EIU FACULTY/STAFF
const char* password =  "1234567890"; //EIU.edu@!%
const char* mqttServer = "postman.cloudmqtt.com";
const int mqttPort =  11702;
const char* mqttUser = "uoycuhvy";
const char* mqttPassword = "mPJJ9IU0qY4F";
long lastMsg = 0;
 int num_t = 50;
 String A = "";
 unsigned char data  ;

WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() 
{
 
  Serial.begin(115200);
   mySerial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword ))
    {
      Serial.println("connected");  
    } 
    else 
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
 
  
 client.subscribe("nut");
 
}
 
void callback(char* topic, byte* nut, unsigned int length) 
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
  
    //Serial.print((char)nut[i]);
      A += (char)nut[i];     
         
  }
     Serial.print("gia tri cua a: ");Serial.println(A);
     data = A.toInt();   
       mySerial.println(data);
    // delay(1000);
     
    A = "";
 
}
 void reconnect()
 {
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");
      //client.publish("outTopic", "hello world");
      client.subscribe("DUYNHAT");   
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void loop()
{
   if (!client.connected())
   {
    reconnect();
   }
  client.loop();
  
  unsigned long now = millis();
  if (now - lastMsg > 5000) 
  { 
    lastMsg = now;
    char nd[16];
    itoa(num_t, nd, 10);
    client.publish("nhietdo",nd); 
    } 
 //Serial.print("gia tri cua data: ");Serial.println(data);
   
     
}
