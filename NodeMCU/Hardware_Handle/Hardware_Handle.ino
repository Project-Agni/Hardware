/*
 Web calling info
  1. /pumpon to turn on the pump
  2. /pumpoff to turn off the pump 
  3. /ledon to turn on LEDs
  4. /ledoff to turn off LEDs 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define SSID "Home"
#define PASS "q7qfia5b"
#define WATER_PUMP 5
#define LED 4
#define BUZZER 14

#define BUZZER_DELAY 500  // Time in milli seconds for the buzzer
#define LED_DELAY 100

ESP8266WebServer server(80);

bool buzzer_status;
unsigned long t2;
unsigned long t1;
unsigned long t3;
unsigned long t4;
bool x = 1;

int LED_ARRAY[5] = {16, 0, 12, 13, 4};
uint8_t LED_ARRAY_STATUS = 0;
void write_LED_array(uint8_t LED_status)
{
  digitalWrite(LED_ARRAY[0], (LED_status & 0b00001));
  digitalWrite(LED_ARRAY[1], (LED_status & 0b00010));
  digitalWrite(LED_ARRAY[2], (LED_status & 0b00100));
  digitalWrite(LED_ARRAY[3], (LED_status & 0b01000));
  digitalWrite(LED_ARRAY[4], (LED_status & 0b10000));
}
void handle_LED_array()
{
   if(buzzer_status)
  {
    t4=millis();
    if (t4-t3 >= LED_DELAY)
    {
      t3 = millis();
      write_LED_array(LED_ARRAY_STATUS);
      LED_ARRAY_STATUS = (LED_ARRAY_STATUS == 0) ? 0b00001 : LED_ARRAY_STATUS<<1;
    }
  }
  else
    write_LED_array(0);
}
void handle_buzzer()
{
  if(buzzer_status)
  {
    t2=millis();
    if (t2-t1 >= BUZZER_DELAY)
    {
      t1 = millis();
      digitalWrite(BUZZER,x);
      
      x = !x;
    }
  }
  else
    digitalWrite(BUZZER,0);
}
void handleRoot() 
{
  server.send(200, "text/plain", "Hello\n 1. /pumpon to turn on the pump\n 2. /pumpoff to turn off the pump \n 3. /ledon to turn on LEDs\n 4. /ledoff to turn off LEDs ");
}
void pump_on() 
{
  digitalWrite(WATER_PUMP, HIGH);
  server.send(200, "text/plain", "PUMP ON!!!");
}
void pump_off() 
{
  digitalWrite(WATER_PUMP, LOW);
  server.send(200, "text/plain", "PUMP OFF!!!");
}
void LED_on() 
{
  digitalWrite(LED, HIGH);
  buzzer_status = 1;
  server.send(200, "text/plain", "LED ON!!!");
}
void LED_off() 
{
  digitalWrite(LED, LOW);
  buzzer_status = 0;
  server.send(200, "text/plain", "LED OFF!!!");
}
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(WATER_PUMP, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    pinMode(LED_ARRAY[0], OUTPUT);
    pinMode(LED_ARRAY[1], OUTPUT);
    pinMode(LED_ARRAY[2], OUTPUT);
    pinMode(LED_ARRAY[3], OUTPUT);
    pinMode(LED_ARRAY[4], OUTPUT);
    
    digitalWrite(LED, LOW);
    digitalWrite(WATER_PUMP, LOW);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASS); //begin WiFi connection
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/pumpon", pump_on);
    server.on("/pumpoff", pump_off);
    server.on("/ledon", LED_on);
    server.on("/ledoff", LED_off);

    server.begin();
    Serial.println("HTTP server started");
}


void loop()
{
  server.handleClient();
  handle_LED_array();
  handle_buzzer();
}
