/***********************************************************************|
| megaAVR analog comparator library                                     |
|                                                                       |
| Internal_reference.ino                                                |
|                                                                       |
| A library for interfacing with the megaAVR analog comparator.         |
| Developed in 2019 by MCUdude                                          |
| https://github.com/MCUdude/                                           |
|                                                                       |
| In this example we use an internal reference voltage instead of an    |
| external one on the negative pin. This eliminates the need for an     |
| external voltage divider to generate a reference. Note that the       |
| internal reference requires a stable voltage to function properly.    |
|                                                                       |
| This is the formula for the generated voltage:                        |
| Vdacref = (DACREF / 256) * Vref                                       |
|                                                                       |
| See Microchip's application note TB3211 for more information.         |
|***********************************************************************/

#include <Comparator.h>

void setup()
{
  // Configure relevant comparator parameters
  Comparator.input_p = comparator::in_p::in0;       // Use positive input 0 (PD2)
  Comparator.input_n = comparator::in_n::dacref;    // Connect the negative pin to the DACREF voltage
  Comparator.reference = comparator::ref::vref_2v5; // Set the DACREF voltage to 2.5V
  Comparator.dacref = 127;                          // Gives us 1.24V -> (127 / 256) * 2.5V = 1.24V
  Comparator.hysteresis = comparator::hyst::large;  // Use a 50mV hysteresis
  Comparator.output = comparator::out::enable;      // Enable output on digital pin 7 (PA7)

  // Initialize comparator
  Comparator.init();

  // Start comparator
  Comparator.start();
}

void loop()
{

}
