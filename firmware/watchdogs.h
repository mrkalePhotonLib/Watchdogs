/*
  NAME:
  Watchdogs

  DESCRIPTION:
  The library utilizes hardware watchdogs of the microcontroller STM32F205
  for ensuring unattended operation of the Photon.
  - Particle Photon uses the STM32F205 ARM Cortex M3, which has two hardware
    watchdogs. One window watchdog and one independent watchdog.
  - The library depends on the external library SparkIntervalTimer.
  - The library is based on the library 'photon-wdgs', but fixed, reformatted,
    and simplified in this way:
    - Both watchdog timers are always enabled.
    - Watchdog TIMER7 is always used.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
  (related to original code) and MIT License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkalePhotonLib/Watchdogs.git
  
  CREDITS:
  - Kevin Kasal, Alexander Partsch: Library photon-wdgs
    (https://github.com/raphitheking/photon-wdgs.git)
  - flaz83 (https://github.com/flaz83): Issue solution proposal
    (https://github.com/raphitheking/photon-wdgs/issues/2)
  - Kevin Kasal: Watchdog library for particle photon
    (http://stasheddragon.com/2015/watchdog-library-for-particle-photon/)
  - Paul Kourany: SparkIntervalTimer
    (https://github.com/pkourany/SparkIntervalTimer)
 */
#ifndef WATCHDOGS_H
#define WATCHDOGS_H
#define WATCHDOGS_VERSION "Watchdogs 1.0.0"

#include "Particle.h"
#include "SparkIntervalTimer/SparkIntervalTimer.h"

#define WATCHDOGS_TIMOUT_DEF 15000      // Default timeout in ms
#define WATCHDOGS_TIMOUT_MIN 10         // Minimal valid timeout in ms
#define WATCHDOGS_TIMOUT_MAX 30000      // Maximal valid timeout in ms

namespace Watchdogs
{
//-------------------------------------------------------------------------
// External attributes
//-------------------------------------------------------------------------
  extern IntervalTimer _wdgTimer;
  extern unsigned long _aliveCount;
  extern unsigned long _timeoutval;
  extern bool _wwdgRunning;          // Window watchdog
  extern bool _iwdgRunning;          // Independent watchdog

//-------------------------------------------------------------------------
// Public methods
//-------------------------------------------------------------------------

/*
  Reset watchdog timers

  DESCRIPTION:
  The method starts one or both hardware watchdogs.
  - A watchdog resets the microcontroller, if it does not get a tickle 
    within the timeout.
  - The constructor has all arguments defaulted. If some argument after
    some defaulted arguments should have a specific value, use corresponding
    constants in place of those defaulted arguments.

  PARAMETERS:
  timeout - time in milliseconds of waiting for petting the watchdogs.
            The percision is 10ms.
          - Data type: non-negative 32-bit integer
          - Default value: WATCHDOGS_TIMOUT_DEF
          - Limited range: WATCHDOGS_TIMOUT_MIN ~ WATCHDOGS_TIMOUT_MAX

  RETURN: none
*/
  void begin(unsigned long timeout = WATCHDOGS_TIMOUT_DEF);

/*
  Reset watchdog timers

  DESCRIPTION:
  The method resets running watchdog timers. It should be called regularly
  from a program.
  - If the method is not called by the end of the timeout period, a watchdog
    resets the microcontroller.

  PARAMETERS: none

  RETURN: none
*/
  void tickle();

//-------------------------------------------------------------------------
// Private methods
//-------------------------------------------------------------------------
  void _tickleWDGs();
  void _handler(system_event_t event, int param);
};

#endif
