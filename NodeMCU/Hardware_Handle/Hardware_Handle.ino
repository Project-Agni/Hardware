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

ESP8266WebServer server(80);

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
  server.send(200, "text/plain", "LED ON!!!");
}
void LED_off() 
{
  digitalWrite(LED, LOW);
  server.send(200, "text/plain", "LED OFF!!!");
}
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(WATER_PUMP, OUTPUT);\
    
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

}
