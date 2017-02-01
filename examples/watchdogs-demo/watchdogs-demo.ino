/*
  NAME:
  Demonstration of the Watchdogs library.

  DESCRIPTION:
  This sketch demonstrates the basic usage of the library and reseting the
  microcontroller after the timeout.
  * At first the sketch taps the watchdogs several times.
  * Then it stops tapping watchdogs and they reset the microcontroller
    after defined timeout past the last tap.
  * Don't forget include the library SparkIntervalTimer to the application.
    

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#include <watchdogs.h>
#define SKETCH "WATCHDOGS-DEMO 1.0.0"

const unsigned int PERIOD_PUBLISH = 3000;      // Publishing time period in ms 
const unsigned int TIMEOUT_WATCHDOG = 10000;   // Watchdog timeout in ms
const unsigned int COUNT_WATCHDOG = 5;         // Number of publishes to simulate freezing

byte cntPublish = 0;

void setup()
{
    Particle.publish("Sketch",  String(SKETCH));
    Particle.publish("Library", String(WATCHDOGS_VERSION));

    // Start watchdogs
    Watchdogs::begin(TIMEOUT_WATCHDOG);
}

void loop()
{
  // Normal usage - frequent tapping the watchdogs 
  // Watchdogs::tickle();  
  
  // Demonstration usage - stop tapping after some number of tapping
  if (cntPublish < COUNT_WATCHDOG) Watchdogs::tickle();
  publish();
}

void publish()
{
    static unsigned long timeStamp;
    if (millis() - timeStamp >= PERIOD_PUBLISH || timeStamp == 0)
    {
      timeStamp = millis();
      cntPublish++;
      Particle.publish("Watchdog", String::format("%4d. Alive", cntPublish));
    }
}
