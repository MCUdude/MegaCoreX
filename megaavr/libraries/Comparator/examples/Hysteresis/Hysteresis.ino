/***********************************************************************|
| megaAVR analog comparator library                                     |
|                                                                       |
| Hysteresis.ino                                                        |
|                                                                       |
| A library for interfacing with the megaAVR analog comparator.         |
| Developed in 2019 by MCUdude                                          |
| https://github.com/MCUdude/                                           |
|                                                                       |
| In this example we use the negative and positive input 0 of the       |
| comparator. The output goes high if the positive input is higher than |
| the negative input, and low otherwise. We'll also use the built-in    |
| hysteresis functionality to prevent false spikes.                     |
|                                                                       |
| See Microchip's application note TB3211 for more information.         |
|***********************************************************************/

#include <Comparator.h>

void setup()
{
  // Configure relevant comparator parameters
  Comparator.input_p = in_p::in0;      // Use positive input 0 (PD2)
  Comparator.input_n = in_n::in0;      // Use negative input 0 (PD3)
  Comparator.hysteresis = hyst::large; // Use a 50mV hysteresis
  Comparator.output = out::enable;     // Enable output on digital pin 7 (PA7)

  // Initialize comparator
  Comparator.init();

  // Start comparator
  Comparator.start();
}

void loop()
{

}
