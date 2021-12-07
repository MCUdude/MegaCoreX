/***********************************************************************|
| megaAVR event system library                                          |
|                                                                       |
| Read_event_settings.ino                                               |
|                                                                       |
| A library for interfacing with the megaAVR event system.              |
| Developed in 2021 by MCUdude                                          |
| https://github.com/MCUdude/                                           |
|                                                                       |
| In this example, we demonstrate the possibilities of reading out      |
| which event channel we're working with, which generator is used, and  |
| which channel an event user has been connected to.                    |
|                                                                       |
| See Microchip's application note AN2451 for more information.         |
|***********************************************************************/

#include <Event.h>

// Function to print information about the passed event
void print_event_info(Event& my_event)
{
  Serial2.printf("This is event channel no. %d\n", my_event.get_channel_number());
  Serial2.printf("This channel uses generator no. 0x%02x, which you can find in Event.h\n", my_event.get_generator());
}

// Function to print information about the passed event user
void print_user_info(user::user_t my_user)
{
  // Event::get_user_channel() returns -1 if the user isn't connected to any event generator
  Serial2.printf("User 0x%02x is connected to event channel no. %d\n\n", my_user, Event::get_user_channel_number(my_user));
}

void setup()
{
  Serial2.begin(9600); // Initialize hardware serial port

  Event1.set_generator(gen0::pin_pa3); // Set pin PA3 as event generator for event channel 1
  Event2.set_generator(gen2::pin_pc3); // Set pin PC3 as event generator for event channel 2
  Event& myEvent = Event::assign_generator_pin(PIN_PA2); // Set pin PA2 as event generator for an available channel

  // For more information about EVOUT, see the PORTMUX section in the datasheet
  Event1.set_user(user::evoutc_pin_pc2); // Set EVOUTC as event user
  Event2.set_user(user::evouta_pin_pa2); // Set EVOUTA as event user
  myEvent.set_user_pin(PIN_PD2); // Set pin PD2 (EVOUTD) as event user

  // Start event channels
  Event1.start();
  Event2.start();
  myEvent.start();
}

void loop()
{
  // Print info about Event4 and its event user
  print_event_info(Event1);
  print_user_info(user::evoutc_pin_pc2);

  // Print info about Event5 and its event user
  print_event_info(Event2);
  print_user_info(user::evouta_pin_pa2);

  // Print info about myEvent and its user
  Event& myEvent = Event::get_generator_channel(PIN_PA2);
  print_event_info(myEvent);
  print_user_info(user::evoutd_pin_pd2);

  delay(5000);
}
