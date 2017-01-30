<a id="library"></a>
# Watchdogs
The library utilizes hardware watchdogs of the microcontroller STM32F205 for ensuring unattended operation of the Photon.
- Particle Photon uses the STM32F205 ARM Cortex M3, which has two hardware watchdogs. One window watchdog and one independent watchdog.
- The library depends on the external library SparkIntervalTimer.
- The library is based on the library 'photon-wdgs', but fixed, reformatted, and simplified in this way:
  - Both watchdog timers are always enabled.
  - Watchdog TIMER7 is always used.


<a id="dependency"></a>
## Dependency
- **SparkIntervalTimer.h**: Includes interval timer library.


<a id="constants"></a>
## Constants
- **WATCHDOGS\_VERSION**: Name and semantic version of the library
- **WATCHDOGS\_TIMEOUT\_DEF**: Default watchdog timeout in milliseconds
- **WATCHDOGS\_TIMEOUT\_MIN**: Minimal valid watchdog timeout in milliseconds
- **WATCHDOGS\_TIMEOUT\_MAX**: Maximal valid watchdog timeout in milliseconds


<a id="interface"></a>
## Interface
- [begin()](#begin)
- [tickle()](#tickle)


<a id="begin"></a>
## begin()
#### Description
The method starts one or both hardware watchdogs.
- A watchdog resets the microcontroller, if it does not get a tickle within the timeout.
- The constructor has all arguments defaulted. If some argument after some defaulted arguments should have a specific value, use corresponding constants in place of those defaulted arguments.

#### Syntax
    voind begin(unsigned long timeout);

#### Parameters
<a id="prm_timeout"></a>
- **timeout**: Time in milliseconds of waiting for petting the watchdogs. The percision is 10ms.
	- *Valid values*: non-negative 32-bit integer 0 to (2^32-1) ([WATCHDOGS\_TIMEOUT\_MIN ~ WATCHDOGS\_TIMEOUT\_MAX](#constants))
	- *Default value*: 10000 ms ([WATCHDOGS\_TIMEOUT\_DEF](#constants)) 

#### Returns
None

#### Example
The method has the argument defaulted. The calling method without the parameter is equivalent to calling with the argument set by corresponding constant with default value:

``` cpp
Watchdogs::begin();               // It is equivalent to
Watchdogs::begin(WATCHDOGS_TIMEOUT_DEF);
```

[Back to interface](#interface)


<a id="tickle"></a>
## tickle()
#### Description
The method resets watchdog timer and should be called regularly from a program.
- If the method is not called by the end of the timeout period, a watchdog resets the microcontroller.

#### Syntax
	void tickle();

#### Parameters
None

#### Returns
None

#### Example
``` cpp
void loop()
{
  Watchdogs::tickle();  
}
```
[Back to interface](#interface)
