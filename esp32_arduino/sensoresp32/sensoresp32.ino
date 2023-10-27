#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2QcqbfGz7"
#define BLYNK_TEMPLATE_NAME "sensor"
#define BLYNK_AUTH_TOKEN "6WDkI6FB8G9UhfZ0kMsfIXdHfKAeRBBL"
#define BlYNK_WIFI_SSID "CN"
#define BlYNK_WIFI_PASS "acencio30"
#define BlYNK_FIRWARE_VERSION ""
#define APP_DEBUG

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//#include "BlynkEdgent.h"

int echo= 26;
int trig= 27;
int LED1=2;
int LED2=4;

char ssid[]="CN";
char pass[]="acencio30";
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

//Enter your tank max value(CM)
int MaxLevel = 100;

int Level1 = (MaxLevel * 5) / 100;
int Level2 = (MaxLevel * 75) / 100;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);


  //Call the functions
  timer.setInterval(100, ultrasonic);
}

//Get the ultrasonic sensor values
void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  int distance = t / 29 / 2;

  int blynkDistance = (distance - MaxLevel) * -1;
  if (distance <= MaxLevel) {
    Blynk.virtualWrite(V0, blynkDistance);
  } else {
    Blynk.virtualWrite(V0, 0);
  }
 

  if (Level1 <= distance) {
 
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);

  } else if (Level2 >= distance) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}