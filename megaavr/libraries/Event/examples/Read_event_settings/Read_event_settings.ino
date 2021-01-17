/***********************************************************************|
| megaAVR event system library                                          |
|                                                                       |
| Read_event_settings.ino                                               |
|                                                                       |
| A library for interfacing with the megaAVR event system.              |
| Developed in 2021 by MCUdude                                          |
| https://github.com/MCUdude/                                           |
|                                                                       |
| In this example, we demonstrate the possibilities of reading out what |
| event channel we're working with, what generator is used, and which   |
| channel an event user has been connected to.                          |
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

void print_user_info(user::user_t my_user)
{
  // Event::get_user_channel() returns -1 if the user isn't connected to any event generator
  Serial2.printf("User 0x%02x is connected to event channel no. %d\n\n", my_user, Event::get_user_channel(my_user));
}

void setup()
{
  Serial2.begin(9600); // Initialize hardware serial port

  Event4.set_generator(gen4::pin_pe0); // Set pin PE0 as event generator
  Event5.set_generator(gen5::pin_pe1); // Set pin PE1 as event generator

  // For more information about EVOUT, see the PORTMUX section in the datasheet
  Event4.set_user(user::evoute_pin_pe2); // Set EVOUTE as event user
  Event5.set_user(user::evoutf_pin_pf2); // Set EVOUTF as event user

  // Start event channels
  Event4.start();
  Event5.start();
}

void loop()
{
  // Print info about Event4 and its event user
  print_event_info(Event4);
  print_user_info(user::evoute_pin_pe2);

  // Print info about Event5 and its event user
  print_event_info(Event5);
  print_user_info(user::evoutf_pin_pf2);

  delay(5000);
}
