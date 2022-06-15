/***********************************************************************|
| megaAVR event system library                                          |
|                                                                       |
| Simple_Event.ino                                                      |
|                                                                       |
| A library for interfacing with the megaAVR event system.              |
| Developed in 2021 by MCUdude                                          |
| https://github.com/MCUdude/                                           |
|                                                                       |
| In this example we look at two different ways of setting up a simple  |
| Event generator ans user. In the first example use pin PA0 as an      |
| event generator, and pin PC2 and PD2 as event users. In practice,     |
| pin PC2 and PD2 will follow PA0's state.                              |
| In the other example we just provide "Arduino pins" as generator and  |
| user, and let the library take care of the rest.                      |
|                                                                       |
| See Microchip's application note AN2451 for more information.         |
|***********************************************************************/

#include <Event.h>

void setup()
{
  // Since pin PE0 is only available on event generator channel 4 and 5, we use Event4 as our object
  // Note that we use gen4:: to refer to functionality unique to event channel 4
  Event0.set_generator(event::gen0::pin_pa0); // Set pin PA0 as event generator

  // For more information about EVOUT, see the PORTMUX section in the datasheet
  Event0.set_user(event::user::evoutc_pin_pc2); // Set EVOUTC as event user
  Event0.set_user(event::user::evoutd_pin_pd2); // Set EVOUTD as event user

  // Start event channel
  Event0.start();



  // A different approach is to let the library itself take care of which Event channel to use:

  // Assign generator to an available channel
  Event& myEvent = Event::assign_generator_pin(PIN_PA1);

  // Connect a user, in this case an Arduino pin, to the myEvent channel
  myEvent.set_user_pin(PIN_PA2);

  // Start event channel
  myEvent.start();
}

void loop()
{

}
