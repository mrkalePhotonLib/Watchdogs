#include "Watchdogs.h"
#include "SparkIntervalTimer/SparkIntervalTimer.h"

//-------------------------------------------------------------------------
// External attributes
//-------------------------------------------------------------------------

IntervalTimer Watchdogs::_wdgTimer;
unsigned long Watchdogs::_aliveCount;
unsigned long Watchdogs::_timeoutval;
bool Watchdogs::_wwdgRunning;
bool Watchdogs::_iwdgRunning;

//-------------------------------------------------------------------------
// Public methods
//-------------------------------------------------------------------------

// Start watchdog timers
void Watchdogs::begin(unsigned long timeout) 
{
    bool enableWwdg = true;
    bool enableIwdg = true;
    
    Watchdogs::_timeoutval = constrain(timeout, WATCHDOGS_TIMOUT_MIN, WATCHDOGS_TIMOUT_MAX);
    Watchdogs::_timeoutval = Watchdogs::_timeoutval / 10;
    Watchdogs::_aliveCount = 0;
    
    RCC_LSICmd(ENABLE); //LSI is needed for Watchdogs
    
    Watchdogs::_wdgTimer.begin(Watchdogs::_tickleWDGs, 20, hmSec, TIMER7);
    System.disableUpdates();
    Watchdogs::_wwdgRunning = enableWwdg;
    if (enableWwdg) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
        WWDG_SetPrescaler(WWDG_Prescaler_8);
        WWDG_SetWindowValue(0x7F);
        WWDG_Enable(0x7F);
    }
    Watchdogs::_iwdgRunning = enableIwdg;
    if (enableIwdg) {
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_SetPrescaler(IWDG_Prescaler_256);
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_SetReload(0xFFF);
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_Enable();
    }
    System.on(firmware_update_pending, Watchdogs::_handler);
}

// Reset watchdog timer
void Watchdogs::tickle() 
{
    Watchdogs::_aliveCount = 0;
}

//-------------------------------------------------------------------------
// Private methods
//-------------------------------------------------------------------------
void Watchdogs::_tickleWDGs() 
{
    if (Watchdogs::_aliveCount < Watchdogs::_timeoutval) {
        if (Watchdogs::_wwdgRunning) {
            WWDG_SetCounter(0x7F);
        }
        if (Watchdogs::_iwdgRunning) {
            IWDG_ReloadCounter();
        }
        Watchdogs::_aliveCount++;
    }
}

void Watchdogs::_handler(system_event_t event, int param) {
    if (Watchdogs::_wwdgRunning) WWDG_DeInit();
    System.enableUpdates();
    Watchdogs::_wdgTimer.end();
}
