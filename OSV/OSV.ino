#include <ArduinoSTL.h>
#include <NewPing.h>
#include <Servo.h>
#include <Enes100.h>

#include "Navigator.h"

void setup()
{
  Serial.begin(9600);
  while (!Enes100.begin("MIXTAPE", FIRE, OSV::ARUCO_MARKER_ID, Pins::WIFI_TRANSMITTER, Pins::WIFI_RECEIVER))
  {
    Serial.println("Connecting to vision system...");
    delay(100);
  }
  Enes100.println("Connected!!!");
  Navigator* navigator = Navigator::getInstance();
  navigator->navigate();
  // navigator->countAndExtinguishFlames();
}

void loop()
{
}
