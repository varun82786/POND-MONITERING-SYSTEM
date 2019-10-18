#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServerSecureAxTLS.h>
#include <ESP8266WebServerSecureBearSSL.h>

//#include <WiFi.h>;

#include <WiFiClient.h>;
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>;

const char* ssid = "superior"; //Your Network SSID

const char* password = "techiguy"; //Your Network Password

int val;

int tdspin = 35; //tds Pin Connected at 35 Pin
float calibration = 0.00; //change this value to calibrate
const int analogInPin = 34; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;


WiFiClient client;

unsigned long myChannelNumber =868055; //Your Channel Number (Without Brackets)

const char * myWriteAPIKey ="G5TXKZPXH61ALZ08"; //Your Write API Key

void setup()

{

Serial.begin(9600);

delay(10);

// Connect to WiFi network

WiFi.begin(ssid, password);



ThingSpeak.begin(client);

}



void loop()

{
for(int i=0;i<10;i++) 
 { 
 buf[i]=analogRead(analogInPin);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buf[i]>buf[j])
 {
 temp=buf[i];
 buf[i]=buf[j];
 buf[j]=temp;
 }
 }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = -5.70 * pHVol + calibration;
 Serial.print("sensor = ");
 Serial.println(phValue);
 
 delay(100);
int tds = analogRead(tdspin); //Read Analog values and Store in val variable

Serial.println(tds); //Print on Serial Monitor

delay(100);

ThingSpeak.writeField(myChannelNumber, 1,tds, myWriteAPIKey); //Update in ThingSpeak
ThingSpeak.writeField(myChannelNumber, 2,phValue, myWriteAPIKey); //Update in ThingSpeak


delay(100);

}
