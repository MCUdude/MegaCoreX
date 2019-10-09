#include "Logic.h"

// Array for storing ISR function pointers
static volatile voidFuncPtr intFuncCCL[4];

// Preinstantiate Object
CustomLogic Logic;

// Object for logic block 0 (IOs connected to PORTA)
Logic Logic0(0, PORTA, CCL_SEQCTRL0, CCL_LUT0CTRLA, CCL_LUT0CTRLB, CCL_LUT0CTRLC, CCL_TRUTH0);

// Object for logic block 1 (IOs connected to PORTC)
Logic Logic1(1, PORTC, CCL_SEQCTRL0, CCL_LUT1CTRLA, CCL_LUT1CTRLB, CCL_LUT1CTRLC, CCL_TRUTH1);

// Object for logic block 2 (IOs connected to PORTD)
Logic Logic2(2, PORTD, CCL_SEQCTRL1, CCL_LUT2CTRLA, CCL_LUT2CTRLB, CCL_LUT2CTRLC, CCL_TRUTH2);

// Object for logic block 3 (IOs connected to PORTF)
Logic Logic3(3, PORTF, CCL_SEQCTRL1, CCL_LUT3CTRLA, CCL_LUT3CTRLB, CCL_LUT3CTRLC, CCL_TRUTH3);

Logic::Logic(
    const uint8_t block_number,
    PORT_t& port,
    register8_t& seq_ctrl,
    register8_t& lut_ctrla,
    register8_t& lut_ctrlb,
    register8_t& lut_ctrlc,
    register8_t& truth)
    : PORT(port),
      SEQCTRL(seq_ctrl),
      LUTCTRLA(lut_ctrla),
      LUTCTRLB(lut_ctrlb),
      LUTCTRLC(lut_ctrlc),
      TRUTH(truth),
      input0(in::masked),
      input1(in::masked),
      input2(in::masked),
      output(false),
      enable(false),
      truth(0x00),
      output_swap(out::no_swap),
      filter(filter::disable),
      sequencer(sequencer::disable)
{
}

// static
void Logic::start(bool state)
{
  CCL.CTRLA = (state << CCL_ENABLE_bp);
}


// static
void Logic::end()
{
  start(false);
}


void Logic::init()
{
  // Block input 0 pin dir
  if(input0 == in::input)
    PORT.DIRCLR = PIN0_bm;
  else if(input0 == in::input_pullup)
  {
    PORT.DIRCLR = PIN0_bm;
    PORT.PIN0CTRL |= PORT_PULLUPEN_bm;
    input0 = in::input;
  }
  // Block input 1 pin dir
  if(input1 == in::input)
    PORT.DIRCLR = PIN1_bm;
  else if(input1 == in::input_pullup)
  {
    PORT.DIRCLR = PIN1_bm;
    PORT.PIN1CTRL |= PORT_PULLUPEN_bm;
    input1 = in::input;
  }
  // Block input 2 pin dir
  if(input2 == in::input)
    PORT.DIRCLR = PIN2_bm;
  else if(input2 == in::input_pullup)
  {
    PORT.DIRCLR = PIN2_bm;
    PORT.PIN2CTRL |= PORT_PULLUPEN_bm;
    input2 = in::input;
  }
  
  // Set inputs modes
  LUTCTRLB = (input1 << 4) | input0;
  LUTCTRLC = input2;

  // Set truth table
  TRUTH = truth;
  
  // Set sequencer
  SEQCTRL = sequencer;

  // Set output pin state and output pin swap
  if(output == out::enable)
  {
    if(output_swap == out::pin_swap)
    {
      PORTMUX.CCLROUTEA |= (1 << block_number);
      PORT.DIRSET = PIN6_bm;
    }
    else if(output_swap == out::no_swap)
    {
      PORTMUX.CCLROUTEA &= ~(1 << block_number);
      PORT.DIRSET = PIN3_bm;
    }
  }
  
  // Set logic output state and output filter
  LUTCTRLA = (output << 6) | (filter << 4) | (enable << 0);
}


void Logic::attachInterrupt(void (*userFunc)(void), PinStatus mode)
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
  const int intmode_bp = block_number * 2;
  CCL.INTCTRL0 = (CCL.INTCTRL0 & ~(0x3 << intmode_bp))
      | (intmode << intmode_bp);
  
  // Store function pointer
  intFuncCCL[block_number] = userFunc;
}


void Logic::detachInterrupt()
{
  // Disable interrupt for a given block output
  CCL.INTCTRL0 &= ~(0x03 << (block_number * 2));
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
}
