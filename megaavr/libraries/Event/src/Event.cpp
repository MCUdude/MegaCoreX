#include "Event.h"

// Pre-defined objects
#if defined(EVSYS_CHANNEL0)
  Event Event0(0, EVSYS_CHANNEL0);
  Event Event_empty(255, EVSYS_CHANNEL0);
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
  : channel_number(channel_num), channel_address(channel_addr) {
}


/**
 * @brief Returns the event channel number in use
 *
 * @return uint8_t Event channel number
 */
uint8_t Event::get_channel_number() {
  return channel_number;
}


/**
 * @brief Returns the object associated with the passed channel number
 *
 * @param ch_number Channel number
 * @return Event& Event object associated with the channel number.
 *         Returns the Event_empty object if invalid channel number
 */
Event& Event::get_channel(uint8_t ch_number) {
  #if defined(EVSYS_CHANNEL0)
    if(Event0.channel_number == ch_number) {
      return Event0;
    }
  #endif
  #if defined(EVSYS_CHANNEL1)
    if(Event1.channel_number == ch_number) {
      return Event1;
    }
  #endif
  #if defined(EVSYS_CHANNEL2)
    if(Event2.channel_number == ch_number) {
      return Event2;
    }
  #endif
  #if defined(EVSYS_CHANNEL3)
    if(Event3.channel_number == ch_number) {
      return Event3;
    }
  #endif
  #if defined(EVSYS_CHANNEL4)
    if(Event4.channel_number == ch_number) {
      return Event4;
    }
  #endif
  #if defined(EVSYS_CHANNEL5)
    if(Event5.channel_number == ch_number) {
      return Event5;
    }
  #endif
  #if defined(EVSYS_CHANNEL6)
    if(Event6.channel_number == ch_number) {
      return Event6;
    }
  #endif
  #if defined(EVSYS_CHANNEL7)
    if(Event7.channel_number == ch_number) {
      return Event7;
    }
  #endif
  #if defined(EVSYS_CHANNEL8)
    if(Event8.channel_number == ch_number) {
      return Event8;
    }
  #endif
  #if defined(EVSYS_CHANNEL9)
    if(Event9.channel_number == ch_number) {
      return Event9;
    }
  #endif

  #if defined(EVSYS_CHANNEL0)
    else {
      return Event_empty;
    }
  #endif
}


/**
 * @brief Returns the event channel object used for a particular event generator
 *
 * @param generator Event generator
 * @return Event& Event channel object used with this event generator
 */
Event& Event::get_generator_channel(event::gen::generator_t generator) {
  #if defined(EVSYS_CHANNEL0)
    if(Event0.generator_type == generator) {
      return Event0;
    }
  #endif
  #if defined(EVSYS_CHANNEL1)
    if(Event1.generator_type == generator) {
      return Event1;
    }
  #endif
  #if defined(EVSYS_CHANNEL2)
    if(Event2.generator_type == generator) {
      return Event2;
    }
  #endif
  #if defined(EVSYS_CHANNEL3)
    if(Event3.generator_type == generator) {
      return Event3;
    }
  #endif
  #if defined(EVSYS_CHANNEL4)
    if(Event4.generator_type == generator) {
      return Event4;
    }
  #endif
  #if defined(EVSYS_CHANNEL5)
    if(Event5.generator_type == generator) {
      return Event5;
    }
  #endif
  #if defined(EVSYS_CHANNEL6)
    if(Event6.generator_type == generator) {
      return Event6;
    }
  #endif
  #if defined(EVSYS_CHANNEL7)
    if(Event7.generator_type == generator) {
      return Event7;
    }
  #endif
  #if defined(EVSYS_CHANNEL8)
    if(Event8.generator_type == generator) {
      return Event8;
    }
  #endif
  #if defined(EVSYS_CHANNEL9)
    if(Event9.generator_type == generator) {
      return Event9;
    }
  #endif

  #if defined(EVSYS_CHANNEL0)
    else {
      return Event_empty;
    }
  #endif
}


/**
 * @brief Returns the event channel object used for a particular event generator Arduino pin
 *
 * @param generator_pin Event generator Arduino pin number
 * @return Event& Event channel object used with this event generator
 */
Event& Event::get_generator_channel(uint8_t generator_pin) {
  uint8_t port = digitalPinToPort(generator_pin);
  uint8_t port_pin = digitalPinToBitPosition(generator_pin);

  if(port != NOT_A_PIN && port_pin != NOT_A_PIN) {
    uint8_t gen = 0x40 | (port & 0x01) << 3 | port_pin;
    if(port == PA || port == PB) {
      #if defined(EVSYS_CHANNEL0)
        if(Event0.generator_type == gen) {
          return Event0;
        }
      #endif
      #if defined(EVSYS_CHANNEL1)
       else if(Event1.generator_type == gen) {
        return Event1;
       }
      #endif
    }
    else if(port == PC || port == PD) {
      #if defined(EVSYS_CHANNEL2)
        if(Event2.generator_type == gen) {
          return Event2;
        }
      #endif
      #if defined(EVSYS_CHANNEL3)
        else if(Event3.generator_type == gen) {
          return Event3;
        }
      #endif
    }
    else if(port == PE || port == PF) {
      #if defined(EVSYS_CHANNEL4)
        if(Event4.generator_type == gen) {
          return Event4;
        }
      #endif
      #if defined(EVSYS_CHANNEL5)
        else if(Event5.generator_type == gen) {
          return Event5;
        }
      #endif
    }
    #if defined(Dx_64_PINS)
    else if(port == PG) {
      if(Event6.generator_type == gen) {
        return Event6;
      }
      else if(Event7.generator_type == gen) {
        return Event7;
      }
    }
    #endif
  }

  #if defined(EVSYS_CHANNEL0)
    return Event_empty;
  #endif
}


/**
 * @brief Returns the generator type a particular channel has
 *
 * @return uint8_t Generator type. Returns 0 if no generator is used
 */
uint8_t Event::get_generator() {
  return generator_type;
}


/**
 * @brief Sets a generator for a particular event channel
 *
 * @param event_generator Set generator.
 *                        Use event::gen:: for functionality present on all event channels.
 *                        Use genN:: for functionality present on channel N.
 */
void Event::set_generator(event::gen::generator_t event_generator) {
  // Store event generator setting for use in start() and stop()
  generator_type = (uint8_t)event_generator;
}


/**
 * @brief Function that lets you use an Arduino pin as event generator.
 *        Note that you'll have to manually keep track of which event channel
 *        objects to use to make sure the passed Arduino pin is supported.
 *        A different approach is to use Event::assign_generator_pin(), which
 *        automatically picks the correct event channel for you.
 *
 * @param pin_number Arduino pin number to use as event generator
 */
void Event::set_generator(uint8_t pin_number) {
  uint8_t port = digitalPinToPort(pin_number);
  uint8_t port_pin = digitalPinToBitPosition(pin_number);

  // Store event generator setting for use in start() and stop()
  if(port != NOT_A_PIN && port_pin != NOT_A_PIN) {
    generator_type = 0x40 | (port & 0x01) << 3 | port_pin;
  }
  else {
    generator_type = event::gen::disable;
  }
}


/**
 * @brief Static member function that sets a port pin as event
 *        generator and returns the object it has select as event channel.
 *        It will always try to select the lowest channel number as possible.
 *
 * @param port Port to use as event generator
 * @param port_pin Pin number on port to use as event generator
 * @return Event& Event channel object used as the event channel. Returns the
 *         Event_empty object if passed Arduino pin is invalid or no event
 *         channel is available
 */
Event& Event::assign_generator_pin(uint8_t port, uint8_t port_pin) {
  if(port != NOT_A_PIN && port_pin != NOT_A_PIN) {
    #if defined(MEGACOREX) || defined(DXCORE)
      uint8_t gen = 0x40 | (port & 0x01) << 3 | port_pin;
      if(port == PA || port == PB) {
        if(Event0.generator_type == event::gen::disable || Event0.generator_type == gen) {
          Event0.generator_type = gen;
          return Event0;
        }
        else if(Event1.generator_type == event::gen::disable || Event1.generator_type == gen) {
          Event1.generator_type = gen;
          return Event1;
        }
      }
      else if(port == PC || port == PD) {
        if(Event2.generator_type == event::gen::disable || Event2.generator_type == gen) {
          Event2.generator_type = gen;
          return Event2;
        }
        else if(Event3.generator_type == event::gen::disable || Event3.generator_type == gen) {
          Event3.generator_type = gen;
          return Event3;
        }
      }
      else if(port == PE || port == PF) {
        if(Event4.generator_type == event::gen::disable || Event4.generator_type == gen) {
          Event4.generator_type = gen;
          return Event4;
        }
        else if(Event5.generator_type == event::gen::disable || Event5.generator_type == gen) {
          Event5.generator_type = gen;
          return Event5;
        }
      }
      #if defined(Dx_64_PINS)
      else if(port == PG) {
        if(Event6.generator_type == event::gen::disable || Event6.generator_type == gen) {
          Event6.generator_type = gen;
          return Event6;
        }
        else if(Event7.generator_type == event::gen::disable || Event7.generator_type == gen) {
          Event7.generator_type = gen;
          return Event7;
        }
      }
      #endif

    return Event_empty;
  #elif defined(TINY_2_SERIES)
    if(port != PC) {
      uint8_t gen = port_pin | (port == PB ? 0x40 : 0x48);
      if(Event0.generator_type == event::gen::disable || Event0.generator_type == gen) {
        Event0.generator_type = gen;
        return Event0;
      }
      else if(Event1.generator_type == event::gen::disable || Event1.generator_type == gen) {
        Event1.generator_type = gen;
        return Event1;
      }
    }
    if(port != PB) {
      uint8_t gen = port_pin | (port == PA ? 0x40 : 0x48);
      if(Event2.generator_type == event::gen::disable || Event2.generator_type == gen) {
        Event2.generator_type = gen;
        return Event2;
      }
      else if(Event3.generator_type == event::gen::disable || Event3.generator_type == gen) {
        Event3.generator_type = gen;
        return Event3;
      }
    }
    if(port != PA)
    {
      uint8_t gen = port_pin | (port == PC ? 0x40 : 0x48);
      if(Event4.generator_type == event::gen::disable || Event4.generator_type == gen) {
        Event4.generator_type = gen;
        return Event4;
      }
      else if(Event5.generator_type == event::gen::disable || Event5.generator_type == gen) {
        Event5.generator_type = gen;
        return Event5;
      }
    }
    return Event_empty;
  #elif defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
    uint8_t gen = port_pin + 0x0A;
      #if !defined(__AVR_ATtinyxy2__)
        if(port == PA) {
      #endif
        if(Event2.generator_type == event::gen::disable || Event2.generator_type == gen) {
          Event2.generator_type = gen;
          return Event2;
        }
        gen += 3;
        if(Event0.generator_type == event::gen::disable || Event0.generator_type == gen) {
          Event0.generator_type = gen;
          return Event0;
        }
      #if !defined(__AVR_ATtinyxy2__)
        }
      #endif
      if(port == PB) {
        if(Event3.generator_type == event::gen::disable || Event3.generator_type == gen) {
          Event3.generator_type = gen;
          return Event3;
        }
        #if defined(TINY_1_SERIES) // No Event1 on 0-series
          gen -= 2;
          if(Event1.generator_type == event::gen::disable || Event1.generator_type == gen) {
            Event1.generator_type = gen;
            return Event1;
          }
        #endif
      }
      #if defined(PIN_PC0) // can't test if PORTx is defined - all are defined everywhere)
        if(port == PC) {
          #if defined(TINY_1_SERIES) // no event 4 on 0-series
            if(Event4.generator_type == event::gen::disable || Event4.generator_type == gen) {
              Event4.generator_type = gen;
              return Event4;
            }
          #endif
          gen -= 3;
          if(Event0.generator_type == event::gen::disable || Event0.generator_type == gen) {
            Event0.generator_type = gen;
            return Event0;
          }
        }
      #endif // PC-bearing parts end here

    #endif // end of tiny 0/1 assign_generator_pin()
  }
  return Event_empty;
}


/**
 * @brief Static member function that sets an Arduino pin as event
 *        generator and returns the object it has select as event channel.
 *        It will always try to select the lowest channel number as possible.
 *
 * @param pin_number Arduino pin number to use as event generator
 * @return Event& Event channel object used as the event channel. Returns the
 *         Event_empty object if passed Arduino pin is invalid or no event
 *         channel is available
 */
Event& Event::assign_generator_pin(uint8_t pin_number) {
  uint8_t port = digitalPinToPort(pin_number);
  uint8_t port_pin = digitalPinToBitPosition(pin_number);
  return Event::assign_generator_pin(port, port_pin);
}


/**
 * @brief Static member function that takes a event::gen:: generator as a parameter and
 * finds an available channel for it. Starts with the highest possible channel
 * number, 7, and iterate down to 0
 *
 * @param event_generator generator to assign to an event channel
 * @return Event& Reference to the event object the generator has been assigned to.
 * Returns the Event_empty object if no generator has been assigned to a channel
 */
Event& Event::assign_generator(event::gen::generator_t event_generator) {
  // Check if generator is already in use
  Event& channel = Event::get_generator_channel(event_generator);
  if(channel.get_channel_number() != 255) {
    return channel;
  }

  else {
    #if defined(EVSYS_CHANNEL9)
      if(Event9.get_generator() == event::gen::disable) {
        Event9.set_generator(event_generator);
        return Event9;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL8)
      if(Event8.get_generator() == event::gen::disable) {
        Event8.set_generator(event_generator);
        return Event8;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL7)
      if(Event7.get_generator() == event::gen::disable) {
        Event7.set_generator(event_generator);
        return Event7;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL6)
      if(Event6.get_generator() == event::gen::disable) {
        Event6.set_generator(event_generator);
        return Event6;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL5)
      if(Event5.get_generator() == event::gen::disable) {
        Event5.set_generator(event_generator);
        return Event5;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL4)
      if(Event4.get_generator() == event::gen::disable) {
        Event4.set_generator(event_generator);
        return Event4;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL3)
      if(Event3.get_generator() == event::gen::disable) {
        Event3.set_generator(event_generator);
        return Event3;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL2)
      if(Event2.get_generator() == event::gen::disable) {
        Event2.set_generator(event_generator);
        return Event2;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL1)
      if(Event1.get_generator() == event::gen::disable) {
        Event1.set_generator(event_generator);
        return Event1;
      }
      else
    #endif
    #if defined(EVSYS_CHANNEL0)
      if(Event0.get_generator() == event::gen::disable) {
        Event0.set_generator(event_generator);
        return Event0;
      }
      else
    #endif
    return channel; // if we're on this branch, we know chan is Event_empty
  }
}


/**
 * @brief Returns the Event channel number a particular user is connected to
 *
 * @param event_user The event user to check
 * @return int8_t Event channel number.
 *         Returns -1 if not connected to any event channel
 */
int8_t Event::get_user_channel_number(event::user::user_t event_user) {
  // Figure out what user register to read from to based on the passed parameter
  volatile uint8_t *user_register = &EVSYS_USERCCLLUT0A + (volatile uint8_t&)event_user;

  // Return which channel the user is connected to
  return *user_register - 1;
}


/**
 * @brief Returns the Event channel object a particular user is connected to
 *
 * @param event_user The event user to check
 * @return Event& Event channel object. Returns the Event_empty object if the
 *         user is not connected to any event channel
 */
Event& Event::get_user_channel(event::user::user_t event_user) {
  int8_t ch_number = get_user_channel_number(event_user);

  #if defined(EVSYS_CHANNEL0)
    if(Event0.channel_number == ch_number) {
      return Event0;
    }
  #endif
  #if defined(EVSYS_CHANNEL1)
    if(Event1.channel_number == ch_number) {
      return Event1;
    }
  #endif
  #if defined(EVSYS_CHANNEL2)
    if(Event2.channel_number == ch_number) {
      return Event2;
    }
  #endif
  #if defined(EVSYS_CHANNEL3)
    if(Event3.channel_number == ch_number) {
      return Event3;
    }
  #endif
  #if defined(EVSYS_CHANNEL4)
    if(Event4.channel_number == ch_number) {
      return Event4;
    }
  #endif
  #if defined(EVSYS_CHANNEL5)
    if(Event5.channel_number == ch_number) {
      return Event5;
    }
  #endif
  #if defined(EVSYS_CHANNEL6)
    if(Event6.channel_number == ch_number) {
      return Event6;
    }
  #endif
  #if defined(EVSYS_CHANNEL7)
    if(Event7.channel_number == ch_number) {
      return Event7;
    }
  #endif
  #if defined(EVSYS_CHANNEL8)
    if(Event8.channel_number == ch_number) {
      return Event8;
    }
  #endif
  #if defined(EVSYS_CHANNEL9)
    if(Event9.channel_number == ch_number) {
      return Event9;
    }
  #endif

  #if defined(EVSYS_CHANNEL0)
    else {
      return Event_empty;
    }
  #endif
}


/**
 * @brief Sets a user for a particular event channel
 *
 * @param event_user The event user to connect to a particular channel
 */
void Event::set_user(event::user::user_t event_user) {
  // Figure out what user register to write to based on the passed parameter
  uint8_t event_user_mask = event_user & 0x7F;

  #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
    volatile uint8_t *user_register = &EVSYS_ASYNCUSER0 + (volatile uint8_t&)event_user_mask;
  #else
    volatile uint8_t *user_register = &EVSYS_USERCCLLUT0A + (volatile uint8_t&)event_user_mask;
  #endif

  // Connect user to the channel we're working with
  *user_register = channel_number + 1;

  // Set PORTMUX pin swap for EVOUT if selected as channel generator
  #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
    if(event_user >= 0x08 && event_user <= 0x0A) {
      PORTMUX.CTRLA |= (1 << (event_user - 0x08));
    }
  #else
    if(event_user & 0x80) {
      #if defined(MEGACOREX)
        PORTMUX_EVSYSROUTEA |= (1 << ((event_user & 0x7F) - 0x09));
      #elif defined(__AVR_DA__)
        PORTMUX_EVSYSROUTEA |= (1 << ((event_user & 0x7F) - 0x0E));
      #elif defined(__AVR_DB__) || defined(__AVR_DD__) || defined(TINY_2_SERIES)
        PORTMUX_EVSYSROUTEA |= (1 << ((event_user & 0x7F) - 0x0D));
      #endif
    }
  #endif
}


/**
 * @brief Sets an Arduino pin as a user for a particular event channel
 *
 * @param pin_number The Arduino pin number to use as a channel user
 * @return uint8_t Event channel user enum
           (for instance event::user::evouta_pin_pa2 pin PIN_PA2 is passed)
 *         Returns -1 if invalid pin is passed
 */
int8_t Event::set_user_pin(uint8_t pin_number) {
  uint8_t port = digitalPinToPort(pin_number);
  uint8_t port_pin = digitalPinToBitPosition(pin_number);
  int8_t event_user = -1;

  if(port != NOT_A_PIN && port_pin != NOT_A_PIN) {
    uint8_t evout_user = (uint8_t)event::user::evouta_pin_pa2;
    if(port_pin == 2) {
      event_user = (event::user::user_t)(evout_user + port);
    }
    #if !defined(TINY_0_SERIES) && !defined(TINY_1_SERIES)
      else if(port_pin == 7) {
        event_user = (event::user::user_t)(evout_user + port);
      }

    #endif
    else {
      return -1;
    }
    set_user((event::user::user_t)event_user);
  }
  return event_user;
}


/**
 * @brief Clears/removed a user from a particular event channel if set
 *
 * @param event_user The event user to remove from a particular channel
 */
void Event::clear_user(event::user::user_t event_user) {
  // Figure out what user register to write to based on the passed parameter
  uint8_t event_user_mask = event_user & 0x7F;
  volatile uint8_t *user_register = &EVSYS_USERCCLLUT0A + (volatile uint8_t&)event_user_mask;

  // Disconnect from event generator
  *user_register = 0x00;

  // Clear PORTMUX pin swap for EVOUT if selected as channel generator
  #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
    if(event_user >= 0x08 && event_user <= 0x0A) {
      PORTMUX.CTRLA &= ~(1 << (event_user - 0x08));
    }
  #else
    if(event_user & 0x80) {
      #if defined(MEGACOREX)
        PORTMUX_EVSYSROUTEA &= ~(1 << ((event_user & 0x7F) - 0x09));
      #elif defined(__AVR_DA__)
        PORTMUX_EVSYSROUTEA &= ~(1 << ((event_user & 0x7F) - 0x0E));
      #elif defined(__AVR_DB__) || defined(__AVR_DD__) || defined(TINY_2_SERIES)
        PORTMUX_EVSYSROUTEA &= ~(1 << ((event_user & 0x7F) - 0x0D));
      #endif
    }
  #endif
}


/**
 * @brief Creates a software event for a particular event channel
 *
 */
void Event::soft_event() {
  // Write to the bit that represent the channel in the strobe register
  #if defined(EVSYS_STROBE)
    // megaAVR 0-series calls the register EVSYS.STROBE
    EVSYS.STROBE = (1 << channel_number);
  #elif defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
    // Channels 0 and 1 are the sync channels, which are strobbed with the syncstrobe registers. The others are the async channels,
    // strobed with the asyncstrobe. Since the sync strobe has only 2 possible thing s to strobe, bit 0 or bit 1 corresponding to byte
    // values 1 and 2, we can just add 1 to the byte value to achieve that.
    if(channel_number < 2) {
      EVSYS.SYNCSTROBE = (channel_number + 1);
    }
    else {
      EVSYS.ASYNCSTROBE = (1 << (channel_number - 2));
    }
  #else
    // Everything newer calls the registers EVSYS.SWEVENTA or SWEVENTB for the few devices lucky enough to have more than 8 channels.
    #if defined(EVSYS_SWEVENTB)
      if(channel_number < 8) {
        EVSYS.SWEVENTA = (1 << channel_number);
      }
      else {
        /* Dirty trick: No available part has more than 10 event channels.
         * So if we are strobing one of those last two, the value we are writing to the register is iwith 1 or 2 (as with sync channel
         * on tiny 0/1). So channel number is 8 or 9, subtract 7 to get 1 or 2, and write that.
         * Doesn't save much flash, but variable-shift operations are surprisignly inefficient in speed. The case for SWEVENTA involves
         * a loop, 5 clocks in duration per bit
         */
        EVSYS.SWEVENTB = channel_number - 7;
      }
    #else
      EVSYS.SWEVENTA = (1 << channel_number);
    #endif
  #endif
}


/**
 * @brief Creates a software event for a particular event channel with a set
 * time duration
 *
 * @param length Length in CPU clock cycles
 */
void Event::long_soft_event(uint8_t length) {
  uint8_t channel = channel_number;
  uint16_t strobeaddr;
  #if defined(EVSYS_STROBE)
    strobeaddr = (uint16_t)&EVSYS_STROBE;
  #elif defined(EVSYS_SYNCSTROBE)
    if(channel > 1)
      strobeaddr = (uint16_t)&EVSYS_ASYNCSTROBE;
    else
      strobeaddr = (uint16_t)&EVSYS_SYNCSTROBE;
  #elif defined(EVSYS_SWEVENTB)
    if(channel > 7) {
      channel -= 8;
      strobeaddr = (uint16_t)&EVSYS_SWEVENTB;
    }
    else {
      strobeaddr = (uint16_t)&EVSYS_SWEVENTA;
    }
  #elif defined(EVSYS_SWEVENTA)
    strobeaddr = (uint16_t)&EVSYS_SWEVENTA;
  #else
    #error "Don't know the strobe register!"
  #endif
  channel = (1 << channel);
  __asm__ __volatile__ (
    "in r0, 0x3F"     "\n\t" // Save SREG
    "cli"             "\n\t" // Interrupts off
    "cpi %1, 4"       "\n\t"
    "brcs long_soft2" "\n\t" // Less than 4 -> 2
    "breq long_soft4" "\n\t" // Equal to 4 -> 4
    "cpi %1, 10"      "\n\t" // Compare with 8
    "brcs long_soft6" "\n\t" // Less than 10 (but more than 4) -> 6
    "breq long_soft10""\n\t" // Equal to 10 -> 10
    "st Z, %0"        "\n\t" // Otherwise they get 16.
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
  "long_soft10:"      "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
  "long_soft6:"       "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
  "long_soft4:"       "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
  "long_soft2:"       "\n\t"
    "st Z, %0"        "\n\t"
    "st Z, %0"        "\n\t"
    "out 0x3f, r0"    "\n"   // Restore SREG, reenable interrupts
    ::"r"((uint8_t) channel),"d"((uint8_t) length),"z" ((uint16_t) strobeaddr));
}


/**
 * @brief Static function used to get the generator number the analog
 * comparator peripheral
 *
 * @param comp Analog comparator struct
 * @return event::gen::generator_t generator type
 */
event::gen::generator_t Event::gen_from_peripheral(AC_t& comp)
{
  #if defined(TINY_1_SERIES) && PROGMEM_SIZE > 8192
    badCall("gen_from_peripheral() does not support channel-specific generators. The AC's larger 1-series are.");
  #else
    #if defined(AC0)
      if(&comp == &AC0) {
        return event::gen::ac0_out;
      }
      #if defined(AC1)
        else if(&comp == &AC1) {
          return event::gen::ac1_out;
        }
        #if defined(AC2)
          else if(&comp == &AC2) {
            return event::gen::ac2_out;
          }
        #endif
      #endif
    #endif
  #endif
  return (event::gen::generator_t) -1;
}


/**
 * @brief Static function used to get the generator type from the CCL peripheral
 *
 * @param logic CCL struct
 * @param logic_block Logic block number (0, 1, 2 or 3 for megaAVR-0's)
 * @return event::gen::generator_t generator type
 */
event::gen::generator_t Event::gen_from_peripheral(CCL_t& logic, uint8_t logic_block) {
  uint8_t retval = -1;
  if(&logic == &CCL) {
    #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
      if(logic_block < 2)
    #elif defined(CCL_LUT4CTRLA)
      if(logic_block < 6)
    #else
      if(logic_block < 4)
    #endif
    {
      retval = (int8_t)(event::gen::ccl0_out) + logic_block;
    }
  }
  return (event::gen::generator_t)retval;
}


/**
 * @brief Static function used to get the possible users the CCL peripheral has
 * to offer
 *
 * @param logic CCL struct
 * @param user_type
 * @return event::user::user_t CCL user number.
 */
event::user::user_t Event::user_from_peripheral(CCL_t& logic, uint8_t user_type) {
  uint8_t retval = -1;
  if(&logic == &CCL) {
    #if !defined(TINY_0_SERIES) && !defined(TINY_1_SERIES)
      #if defined(CCL_TRUTH4)
        if(user_type < 13)
      #else
        if(user_type < 9)
      #endif
      {
        retval = user_type;
      }
    #else
      if(user_type < 5) {
        retval = user_type + 2;
      }
    #endif
  }
  return (event::user::user_t)retval;
}


/**
 * @brief Static function used to get the generator type from timer A
 *
 * @param logic TCA struct
 * @param event_type TCA has multiple generators. This parameter provides the number,
 * and ranges from 0 to 4 for megaAVR-0's
 * @return event::gen::generator_t generator type
 */
event::gen::generator_t Event::gen_from_peripheral(TCA_t& timer, uint8_t event_type) {
  uint8_t retval = -1;
  if(event_type < 5) {
    #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
      retval = event_type + 2;
    #else
      if(&TCA0 == &timer) {
        retval = event_type + 0x80;
      }
      #if defined(TCA1)
        else if(&TCA1 == &timer) {
          retval = event_type += 0x88;
        }
      #endif
    #endif
  }
  return (event::gen::generator_t)retval;
}


/**
 * @brief Static function used to get the possible users the TCA timer has to offer
 *
 * @param timer TCA struct
 * @param user_type TCA has only has one user on megaAVR-0's.
 * Leave this parameter unused
 * @return event::user::user_t TCA user number
 */
event::user::user_t Event::user_from_peripheral(TCA_t& timer, uint8_t user_type) {
  uint8_t user = -1;

  #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES) || defined(MEGACOREX)
    if(user_type != 0) {
      return (event::user::user_t) -1;
    }
  #else
    if(user_type > 1) {
      return (event::user::user_t) -1;
    }
  #endif
  user = user_type; // 0 or 1 for event user a or b (on parts with both, or 0 for parts that only have one
  #if defined(TCA1)
  if(&timer == &TCA1) {
    user += 2;
  } else
  #endif
  if(&timer != &TCA0) {
    return (event::user::user_t) -1;
  }
  #if defined(__AVR_DA__)
    user += 0x1B;
  #elif defined(__AVR_DB__) || defined(__AVR_DD__)
    user += 0x1A;
  #elif defined(MEGACOREX)
    user += 0x13;
  #elif defined(TINY_2_SERIES)
    user += 0x0E;
  #else
    user += 0x10;
  #endif
  return (event::user::user_t)user;
}


/**
 * @brief Static function used to get the generator type from timer B
 *
 * @param timer TCB struct
 * @param event_type TCB only has one generators on megaAVR-0's.
 * Leave this parameter unused
 * @return event::gen::generator_t generator type
 */
event::gen::generator_t Event::gen_from_peripheral(TCB_t& timer, uint8_t event_type) {
  int8_t gentype = -1;
  #if defined(TINY_0_OR_1_SERIES)
    badCall("gen_from_peripheral() does not support channel-specific generators. The TCBs on 0/1-series are.");
  #else
    #if defined(MEGACOREX)  // Dx-series and 2-series have ovf event, others don't.
      if(event_type != 1) {
        return (event::gen::generator_t) -1;
      }
      else {
        gentype = 0;
      }
    #else
      if(event_type < 2) {
        gentype = event_type;
      }
    #endif
    if(&timer == &TCB0) {
      gentype += (uint8_t)event::gen::tcb0_capt;
    } else
    #if defined(TCB1)
    if (&timer == &TCB1) {
      gentype += (uint8_t)event::gen::tcb1_capt;
    } else
    #endif
    #if defined(TCB2)
    if (&timer == &TCB2) {
      gentype += (uint8_t)event::gen::tcb2_capt;
    } else
    #endif
    #if defined(TCB3)
    if (&timer == &TCB3) {
      gentype += (uint8_t)event::gen::tcb3_capt;
    } else
    #endif
    #if defined(TCB4)
    if (&timer == &TCB4) {
      gentype += (uint8_t)event::gen::tcb4_capt;
    } else
    #endif
    {
      gentype = -1;
    }
  #endif
  return (event::gen::generator_t) gentype;
}


/**
 * @brief Static function used to get the possible users the TCB timer has to offer
 *
 * @param timer TCB struct
 * @param user_type
 * @return event::user::user_t TCA user number
 */
event::user::user_t Event::user_from_peripheral(TCB_t& timer, uint8_t user_type) {
  uint8_t user = -1;
  #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES) || defined(MEGACOREX) // Dx-series and 2-series have event count input, others don't.
    if (user_type != 1) {
      return (event::user::user_t) -1;
    }
    else {
      user = 0;
    }
  #else
    if (user_type < 2) {
      user = user_type;
    }
  #endif
  if (&timer == &TCB0) {
    user += (uint8_t)event::user::tcb0_capt;
  } else
  #if defined(TCB1)
  if (&timer == &TCB1) {
    user += (uint8_t)event::user::tcb1_capt;
  } else
  #endif
  #if defined(TCB2)
  if (&timer == &TCB2) {
    user += (uint8_t)event::user::tcb2_capt;
  } else
  #endif
  #if defined(TCB3)
  if (&timer == &TCB3) {
    user += (uint8_t)event::user::tcb3_capt;
  } else
  #endif
  #if defined(TCB4)
  if (&timer == &TCB4) {
    user += (uint8_t)event::user::tcb4_capt;
  } else
  #endif
  {
    user = -1;
  }
  return (event::user::user_t)user;
}


/**
 * @brief Static function used to get the possible users the USART peripheral has
 * to offer
 *
 * @param usart USART struct
 * @return event::user::user_t USART related event channel user
 */
event::user::user_t Event::user_from_peripheral(USART_t& usart) {
  if(&usart == &USART0) {
    return event::user::usart0_irda;
  }
  #if defined(USART1)
    else if(&usart == &USART1) {
      return event::user::usart1_irda;
    }
  #endif
  #if defined(USART2)
    else if(&usart == &USART2) {
      return event::user::usart2_irda;
    }
  #endif
  #if defined(USART3)
    else if(&usart == &USART3) {
      return event::user::usart3_irda;
    }
  #endif
  #if defined(USART4)
    else if(&usart == &USART4) {
      return event::user::usart4_irda;
    }
  #endif
  #if defined(USART5)
    else if(&usart == &USART5) {
      return event::user::usart5_irda;
    }
  #endif
  return (event::user::user_t) -1;
}


/**
 * @brief Starts the event generator for a particular event channel
 *
 * @param state Optional parameter. Defaults to true
 */
void Event::start(bool state) {
  if(state) {
    // Write event generator setting to EVSYS_CHANNELn register
    channel_address = generator_type;
  }
  else {
    // Disable event generator
    channel_address = event::gen::disable;
  }
}


/**
 * @brief Stops the event generator for a particular event channel
 *
 */
void Event::stop() {
  start(false);
}
