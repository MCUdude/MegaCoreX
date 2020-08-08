#include "Logic.h"

#if defined(CCL_CCL_vect)
// Array for storing ISR function pointers
#if defined(TRUTH5)
static volatile voidFuncPtr intFuncCCL[6];
#else
static volatile voidFuncPtr intFuncCCL[4];
#endif
#endif

struct Logic::CCLBlock
{
    const uint8_t number;
    const uint8_t input0_bm;
    const uint8_t input1_bm;
    const uint8_t input2_bm;
    const uint8_t output_bm;
    const uint8_t output_alt_bm;
    PORT_t& PORT_IN;
    PORT_t& PORT_OUT;
    PORT_t& PORT_ALT_OUT;
    volatile register8_t& SEQCTRL;
    volatile register8_t& LUTCTRLA;
    volatile register8_t& LUTCTRLB;
    volatile register8_t& LUTCTRLC;
    volatile register8_t& TRUTH;
};

static const struct Logic::CCLBlock blocks[] = {
#if defined(__AVR_ATtiny202__) || defined(__AVR_ATtiny402__) ||  \
    defined(__AVR_ATtiny204__) || defined(__AVR_ATtiny404__) ||  \
    defined(__AVR_ATtiny804__) || defined(__AVR_ATtiny1604__) || \
    defined(__AVR_ATtiny212__) || defined(__AVR_ATtiny412__) ||  \
    defined(__AVR_ATtiny214__) || defined(__AVR_ATtiny414__) ||  \
    defined(__AVR_ATtiny814__) || defined(__AVR_ATtiny1614__)
    {
      0,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN6_bm, 0,
      PORTA, PORTA, PORTA,
      CCL.SEQCTRL0, CCL.LUT0CTRLA, CCL.LUT0CTRLB, CCL.LUT0CTRLC, CCL.TRUTH0,
    },
    {
      1,
      0, 0, 0, PIN7_bm, 0,
      PORTA, PORTA, PORTA,
      CCL.SEQCTRL0, CCL.LUT1CTRLA, CCL.LUT1CTRLB, CCL.LUT1CTRLC, CCL.TRUTH1,
    },
#endif
#if defined(__AVR_ATtiny406__) || defined(__AVR_ATtiny806__) || \
    defined(__AVR_ATtiny1606__) ||                              \
    defined(__AVR_ATtiny416__) || defined(__AVR_ATtiny816__) || \
    defined(__AVR_ATtiny1616__) || defined(__AVR_ATtiny3216__)
#define PORTMUX_CCL PORTMUX.CTRLA
#define PORTMUX_ALTOUT_bm (1 << (block.number + 4))
    {
      0,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN6_bm, PIN4_bm,
      PORTA, PORTA, PORTB,
      CCL.SEQCTRL0, CCL.LUT0CTRLA, CCL.LUT0CTRLB, CCL.LUT0CTRLC, CCL.TRUTH0,
    },
    {
      1,
      PIN3_bm, 0, 0, PIN7_bm, PIN1_bm,
      PORTC, PORTA, PORTC,
      CCL.SEQCTRL0, CCL.LUT1CTRLA, CCL.LUT1CTRLB, CCL.LUT1CTRLC, CCL.TRUTH1,
    },
#endif
#if defined(__AVR_ATtiny807__) || defined(__AVR_ATtiny1607__) || \
    defined(__AVR_ATtiny417__) || defined(__AVR_ATtiny817__) ||  \
    defined(__AVR_ATtiny1617__) || defined(__AVR_ATtiny3217__)
#define PORTMUX_CCL PORTMUX.CTRLA
#define PORTMUX_ALTOUT_bm (1 << (block.number + 4))
    {
      0,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN6_bm, PIN4_bm,
      PORTA, PORTA, PORTB,
      CCL.SEQCTRL0, CCL.LUT0CTRLA, CCL.LUT0CTRLB, CCL.LUT0CTRLC, CCL.TRUTH0,
    },
    {
      1,
      PIN3_bm, PIN4_bm, PIN5_bm, PIN7_bm, PIN1_bm,
      PORTC, PORTA, PORTC,
      CCL.SEQCTRL0, CCL.LUT1CTRLA, CCL.LUT1CTRLB, CCL.LUT1CTRLC, CCL.TRUTH1,
    },
#endif
#if defined(__AVR_ATmega808__) || defined(__AVR_ATmega1608__) || \
    defined(__AVR_ATmega3208__) || defined(__AVR_ATmega4808__)|| \
    defined(__AVR_AVR128DA64__)||defined(__AVR_AVR64DA64__) || defined(__AVR_AVR128DA48__)||defined(__AVR_AVR64DA48__)||defined(__AVR_AVR32DA48__) || \
    defined(__AVR_AVR128DA32__)||defined(__AVR_AVR64DA32__)||defined(__AVR_AVR32DA32__) || defined(__AVR_AVR128DA28__)||defined(__AVR_AVR64DA28__)||defined(__AVR_AVR32DA28__)

#define PORTMUX_CCL PORTMUX.CCLROUTEA
#define PORTMUX_ALTOUT_bm (1 << block.number)
    {
      0,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTA, PORTA, PORTA,
      CCL.SEQCTRL0, CCL.LUT0CTRLA, CCL.LUT0CTRLB, CCL.LUT0CTRLC, CCL.TRUTH0,
    },
    {
      1,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTC, PORTC, PORTC,
      CCL.SEQCTRL0, CCL.LUT1CTRLA, CCL.LUT1CTRLB, CCL.LUT1CTRLC, CCL.TRUTH1,
    },
    {
      2,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTD, PORTD, PORTD,
      CCL.SEQCTRL1, CCL.LUT2CTRLA, CCL.LUT2CTRLB, CCL.LUT2CTRLC, CCL.TRUTH2,
    },
    { // Note: 28-Pin version doesn't have input2 and output_alt.
      3,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTF, PORTF, PORTF,
      CCL.SEQCTRL1, CCL.LUT3CTRLA, CCL.LUT3CTRLB, CCL.LUT3CTRLC, CCL.TRUTH3,
    },
#endif
#if defined(__AVR_AVR128DA64__)||defined(__AVR_AVR64DA64__) || defined(__AVR_AVR128DA48__)||defined(__AVR_AVR64DA48__)||defined(__AVR_AVR32DA48__)
    { // Note: 28-Pin version doesn't have input2 and output_alt.
      4,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTB, PORTB, PORTB,
      CCL.SEQCTRL2, CCL.LUT4CTRLA, CCL.LUT4CTRLB, CCL.LUT4CTRLC, CCL.TRUTH4,
    },
    { // Note: 28-Pin version doesn't have input2 and output_alt.
      5,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTG, PORTG, PORTG,
      CCL.SEQCTRL2, CCL.LUT5CTRLA, CCL.LUT5CTRLB, CCL.LUT5CTRLC, CCL.TRUTH5,
    },

#endif
#if defined(__AVR_ATmega809__) || defined(__AVR_ATmega1609__) || \
    defined(__AVR_ATmega3209__) || defined(__AVR_ATmega4809__)
#define PORTMUX_CCL PORTMUX.CCLROUTEA
#define PORTMUX_ALTOUT_bm (1 << block.number)
    {
      0,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTA, PORTA, PORTA,
      CCL.SEQCTRL0, CCL.LUT0CTRLA, CCL.LUT0CTRLB, CCL.LUT0CTRLC, CCL.TRUTH0,
    },
    { // Note: 40-Pin version doesn't have output_alt.
      1,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTC, PORTC, PORTC,
      CCL.SEQCTRL0, CCL.LUT1CTRLA, CCL.LUT1CTRLB, CCL.LUT1CTRLC, CCL.TRUTH1,
    },
    {
      2,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTD, PORTD, PORTD,
      CCL.SEQCTRL1, CCL.LUT2CTRLA, CCL.LUT2CTRLB, CCL.LUT2CTRLC, CCL.TRUTH2,
    },
    {
      3,
      PIN0_bm, PIN1_bm, PIN2_bm, PIN3_bm, PIN6_bm,
      PORTF, PORTF, PORTF,
      CCL.SEQCTRL1, CCL.LUT3CTRLA, CCL.LUT3CTRLB, CCL.LUT3CTRLC, CCL.TRUTH3,
    },
#endif
};

#if defined(CCL_TRUTH0)
Logic Logic0(0);
#endif
#if defined(CCL_TRUTH1)
Logic Logic1(1);
#endif
#if defined(CCL_TRUTH2)
Logic Logic2(2);
#endif
#if defined(CCL_TRUTH3)
Logic Logic3(3);
#endif
#if defined(CCL_TRUTH4)
Logic Logic4(4);
#endif
#if defined(CCL_TRUTH3)
Logic Logic5(5);
#endif

Logic::Logic(const uint8_t block_number)
    : enable(false),
      input0(in::masked),
      input1(in::masked),
      input2(in::masked),
      output(out::disable),
      output_swap(out::no_swap),
      filter(filter::disable),
      edgedetect(edgedetect::disable),
      truth(0x00),
      sequencer(sequencer::disable),
      clocksource(clocksource::clk_per),
      block(blocks[block_number])
{
}

// static
void Logic::start(bool state)
{
  CCL.CTRLA = (state ? CCL_ENABLE_bm : 0);
}


// static
void Logic::stop()
{
  start(false);
}

static volatile register8_t& PINCTRL(PORT_t& port, const uint8_t pin_bm)
{
  if(pin_bm == PIN0_bm) return port.PIN0CTRL;
  if(pin_bm == PIN1_bm) return port.PIN1CTRL;
  if(pin_bm == PIN2_bm) return port.PIN2CTRL;
  if(pin_bm == PIN3_bm) return port.PIN3CTRL;
  if(pin_bm == PIN4_bm) return port.PIN4CTRL;
  if(pin_bm == PIN5_bm) return port.PIN5CTRL;
  if(pin_bm == PIN6_bm) return port.PIN6CTRL;
  return port.PIN7CTRL;
}

void Logic::initInput(in::input_t& input, PORT_t& port, const uint8_t pin_bm)
{
  if((input&0x30) && pin_bm)
  {
    port.DIRCLR = pin_bm;
    if ((input&in::input_pullup) == in::input_pullup) {
      PINCTRL(port, pin_bm) |= PORT_PULLUPEN_bm;
    } else {
      PINCTRL(port, pin_bm) &= ~PORT_PULLUPEN_bm;
    }
    input = in::input;
  }
}


void Logic::init()
{
  initInput(input0, block.PORT_IN, block.input0_bm);
  initInput(input1, block.PORT_IN, block.input1_bm);
  initInput(input2, block.PORT_IN, block.input2_bm);

  // Set inputs modes
  block.LUTCTRLB = (input1 << CCL_INSEL1_gp) | (input0 << CCL_INSEL0_gp);
  block.LUTCTRLC = (input2 << CCL_INSEL2_gp);

  // Set truth table
  block.TRUTH = truth;

  // Set sequencer
  if (!(block.number&1))
  {
    block.SEQCTRL = sequencer;
  }
  // Set output pin state and output pin swap
  if(output == out::enable)
  {
    if(output_swap == out::pin_swap && block.output_alt_bm)
    {
#if defined(PORTMUX_CCL)
      PORTMUX_CCL |= PORTMUX_ALTOUT_bm;
#endif
      block.PORT_OUT.DIRSET = block.output_alt_bm;
    }
    else if(output_swap == out::no_swap && block.output_bm)
    {
#if defined(PORTMUX_CCL)
      PORTMUX_CCL &= ~PORTMUX_ALTOUT_bm;
#endif
      block.PORT_ALT_OUT.DIRSET = block.output_bm;
    }
  }

  // Set logic output state and output filter
  block.LUTCTRLA = (output ? CCL_OUTEN_bm : 0)
      | (edgedetect ? CCL_EDGEDET_EN_gc : 0 )
      | (filter << CCL_FILTSEL_gp)
      | (clocksource << CCL_CLKSRC_gp)
      | (enable ? CCL_ENABLE_bm : 0);
}


#if defined(CCL_CCL_vect)
void Logic::attachInterrupt(void (*userFunc)(void), uint8_t mode)
{
  CCL_INTMODE0_t intmode;
  switch (mode)
  {
    // Set RISING, FALLING or CHANGE interrupt trigger for a block output
    case RISING:
      intmode = CCL_INTMODE0_RISING_gc;
      break;
    case FALLING:
      intmode = CCL_INTMODE0_FALLING_gc;
      break;
    case CHANGE:
      intmode = CCL_INTMODE0_BOTH_gc;
      break;
    default:
      // Only RISING, FALLING and CHANGE is supported
      return;
  }

#if defined(CCL_TRUTH4)
  if (block.number > 3)
  {
    const int intmode_bp = (block.number&0x03) * 2;
    CCL.INTCTRL1 = (CCL.INTCTRL1 & ~(CCL_INTMODE0_gm << intmode_bp))
        | (intmode << intmode_bp);
  } else {
    const int intmode_bp = (block.number&0x03) * 2;
    CCL.INTCTRL0 = (CCL.INTCTRL0 & ~(CCL_INTMODE0_gm << intmode_bp))
        | (intmode << intmode_bp);
  }
#else
  const int intmode_bp = block.number * 2;
  CCL.INTCTRL0 = (CCL.INTCTRL0 & ~(CCL_INTMODE0_gm << intmode_bp))
      | (intmode << intmode_bp);
#endif
  // Store function pointer
  intFuncCCL[block.number] = userFunc;
}


void Logic::detachInterrupt()
{
  // Disable interrupt for a given block output

#if defined(CCL_TRUTH4)
  if (block_number > 4) {
    CCL.INTCTRL1 &= ~(CCL_INTMODE1_gm << ((block.number&3) * 2));
  } else {
    CCL.INTCTRL0 &= ~(CCL_INTMODE0_gm << (block.number * 2));
  }
#else
  CCL.INTCTRL0 &= ~(CCL_INTMODE0_gm << (block.number * 2));
#endif
}


// CCL interrupt service routine
// Use attachIntterupt to activate this.
ISR(CCL_CCL_vect)
{
   // Cleck for block 0 interrupt
  if(CCL.INTFLAGS & CCL_INT0_bm)
  {
    // Run user function
    intFuncCCL[CCL_INT0_bp]();
    // Clear flag
    CCL.INTFLAGS |= CCL_INT0_bm;
  }
  if(CCL.INTFLAGS & CCL_INT1_bm)
  {
    intFuncCCL[CCL_INT1_bp]();
    CCL.INTFLAGS |= CCL_INT1_bm;
  }
  if(CCL.INTFLAGS & CCL_INT2_bm)
  {
    intFuncCCL[CCL_INT2_bp]();
    CCL.INTFLAGS |= CCL_INT2_bm;
  }
  // Cleck for block 3 interrupt
  if(CCL.INTFLAGS & CCL_INT3_bm)
  {
    // Run user function
    intFuncCCL[CCL_INT3_bp]();
    // Clear flag
    CCL.INTFLAGS |= CCL_INT3_bm;
  }
#if defined(TRUTH4)
  if(CCL.INTFLAGS & CCL_INT4_bm)
  {
    // Run user function
    intFuncCCL[CCL_INT4_bp]();
    // Clear flag
    CCL.INTFLAGS |= CCL_INT4_bm;
  }
#endif
#if defined(TRUTH5)
  if(CCL.INTFLAGS & CCL_INT5_bm)
  {
    // Run user function
    intFuncCCL[CCL_INT5_bp]();
    // Clear flag
    CCL.INTFLAGS |= CCL_INT5_bm;
  }
#endif

}
#endif // CCL_CCL_vect
