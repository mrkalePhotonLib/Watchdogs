/*
  NAME:
  Demonstration of the Watchdogs library

  DESCRIPTION:
  This sketch demonstrates the basic usage of the library.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/

// Debugging
#define PHOTON_PUBLISH_DEBUG      // Publishing debug events to the particle cloud
#define PHOTON_PUBLISH_VALUE      // Publishing regular events to the particle cloud
//#define PHOTON_SERIAL             // Outputing to the serial port

// Libraries
#include "watchdogs/watchdogs.h"
#define SKETCH "WATCHDOGS_DEMO 1.0.0"

const unsigned int PERIOD_PUBLISH = 3000;      // Publishing time period in ms 
const unsigned int TIMEOUT_WATCHDOG = 10000;   // Watchdog timeout in ms
const unsigned int COUNT_WATCHDOG = 5;         // Number of publishes to simulate freezing

unsigned char cntPublish = 0;

void setup() {
#ifdef PHOTON_SERIAL
    Serial.begin(9600);
    while(!Serial.available()); // Wait for pressing ENTER in Serial Terminal
#endif
  // Publish sketch and libraries identification as public events
#ifdef PHOTON_PUBLISH_DEBUG
    Particle.publish("Sketch",  String(SKETCH));
    Particle.publish("Library", String(WATCHDOGS_VERSION));
#endif
#ifdef PHOTON_SERIAL
    Serial.println(SKETCH);
    Serial.println(WATCHDOGS_VERSION);
    // Print header
    Serial.println("---");
#endif
    // Start watchdogs
    Watchdogs::begin(TIMEOUT_WATCHDOG);
}

void loop() {
  if (cntPublish < COUNT_WATCHDOG) Watchdogs::tickle();
  publish();
}

void publish() {
    static unsigned long tsPublish = millis();
    if (millis() - tsPublish >= PERIOD_PUBLISH) {
      tsPublish = millis();
      ++cntPublish;
#ifdef PHOTON_PUBLISH_VALUE
      Particle.publish("Watchdog", String::format("%4d. Alive", cntPublish));
#endif
#ifdef PHOTON_SERIAL
      Serial.printlnf("%4d. Alive", cntPublish);
#endif
    }
}
