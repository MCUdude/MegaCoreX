#include "Event.h"

// Pre-defined objects
#if defined(EVSYS_CHANNEL0)
  Event Event0(0, EVSYS_CHANNEL0);
#endif
#if defined(EVSYS_CHANNEL1)
  Event Event1(1, EVSYS_CHANNEL1);
#endif
#if defined(EVSYS_CHANNEL2)
  Event Event2(2, EVSYS_CHANNEL2);
#endif
#if defined(EVSYS_CHANNEL3)
  Event Event3(3, EVSYS_CHANNEL3);
#endif
#if defined(EVSYS_CHANNEL4)
  Event Event4(4, EVSYS_CHANNEL4);
#endif
#if defined(EVSYS_CHANNEL5)
  Event Event5(5, EVSYS_CHANNEL5);
#endif
#if defined(EVSYS_CHANNEL6)
  Event Event6(6, EVSYS_CHANNEL6);
#endif
#if defined(EVSYS_CHANNEL7)
  Event Event7(7, EVSYS_CHANNEL7);
#endif
#if defined(EVSYS_CHANNEL8)
  Event Event8(8, EVSYS_CHANNEL8);
#endif
#if defined(EVSYS_CHANNEL9)
  Event Event9(9, EVSYS_CHANNEL9);
#endif


/**
 * @brief Construct a new Event object
 *
 * @param channel_num Event channel number
 * @param channel_addr Register address to channel generator
 */
Event::Event(uint8_t channel_num, volatile uint8_t &channel_addr)
  : channel_number(channel_num), channel_address(channel_addr)
{
}


/**
 * @brief Returns the event channel number in use
 *
 * @return uint8_t Event channel number
 */
uint8_t Event::get_channel_number()
{
  return channel_number;
}


/**
 * @brief Returns the Event channel number a particular user is connected to
 *
 * @param event_user The event user to check
 * @return int8_t Event channel number. Returns -1 if not connected to any event channel
 */
int8_t Event::get_user_channel(user::user_t event_user)
{
  // Figure out what user register to read from to based on the passed parameter
  volatile uint8_t *user_register = &EVSYS_USERCCLLUT0A + (volatile uint8_t&)event_user;

  // Return what channel the user is connected to
  return *user_register - 1;
}


/**
 * @brief Sets a generator for a particular event channel
 *
 * @param event_generator Set generator.
 *                        Use gen:: for functionality present on all event channels.
 *                        Use genN:: for functionality present on channel N.
 */
void Event::set_generator(uint8_t event_generator)
{
  // Store event generator setting for use in start() and stop()
  generator_type = event_generator;
}


/**
 * @brief Returns the generator type a particular channel has
 *
 * @return uint8_t Generator type. Returns 0 if no generator is used
 */
uint8_t Event::get_generator()
{
  return generator_type;
}


/**
 * @brief Sets a user for a particular event channel
 *
 * @param event_user The event user to connect to a particular channel
 */
void Event::set_user(user::user_t event_user)
{
  // Figure out what user register to write to based on the passed parameter
  uint8_t event_user_mask = event_user & 0x7F;
  volatile uint8_t *user_register = &EVSYS_USERCCLLUT0A + (volatile uint8_t&)event_user_mask;

  // Connect user to the channel we're working with
  *user_register = channel_number + 1;

  // Set PORTMUX pin swap for EVOUT if selected as channel generator
  if (event_user & 0x80)
  {
    #if defined(MEGAAVR_0)
      PORTMUX_EVSYSROUTEA |= (1 << ((event_user & 0x7F) - 0x09));
    #elif defined(AVR_DA)
      PORTMUX_EVSYSROUTEA |= (1 << ((event_user & 0x7F) - 0x0E));
    #elif defined(AVR_DB)
      PORTMUX_EVSYSROUTEA |= (1 << ((event_user & 0x7F) - 0x0D));
    #endif
  }
}


/**
 * @brief Clears/removed a user from a particular event channel if set
 *
 * @param event_user The event user to remove from a particular channel
 */
void Event::clear_user(user::user_t event_user)
{
  // Figure out what user register to write to based on the passed parameter
  uint8_t event_user_mask = event_user & 0x7F;
  volatile uint8_t *user_register = &EVSYS_USERCCLLUT0A + (volatile uint8_t&)event_user_mask;

  // Disconnect from event generator
  *user_register = 0x00;

  // Clear PORTMUX pin swap for EVOUT if selected as channel generator
  if (event_user & 0x80)
  {
    #if defined(MEGAAVR_0)
      PORTMUX_EVSYSROUTEA &= ~(1 << ((event_user & 0x7F) - 0x09));
    #elif defined(AVR_DA)
      PORTMUX_EVSYSROUTEA &= ~(1 << ((event_user & 0x7F) - 0x0E));
    #elif defined(AVR_DB)
      PORTMUX_EVSYSROUTEA &= ~(1 << ((event_user & 0x7F) - 0x0D));
    #endif
  }
}


/**
 * @brief Creates a software event for a particular event channel
 *
 */
void Event::soft_event()
{
  // Write to the bit that represent the channel in the strobe register
  #if defined(MEGAAVR_0)
    EVSYS_STROBE = (1 << channel_number);
  #elif defined(AVR_DA) || defined(AVR_DB)
    if(channel_number < 8)
      EVSYS_SWEVENTA = (1 << channel_number);
    else
      EVSYS_SWEVENTB = (1 << (channel_number - 8));
  #endif
}


/**
 * @brief Starts the event generator for a particular event channel
 *
 * @param state Optional parameter. Defaults to true
 */
void Event::start(bool state)
{
  if (state)
  {
    // Write event generator setting to EVSYS_CHANNELn register
    channel_address = generator_type;
  }
  else
  {
    // Disable event generator
    channel_address = gen::disable;
  }
}


/**
 * @brief Stops the event generator for a particular event channel
 *
 */
void Event::stop()
{
  start(false);
}
