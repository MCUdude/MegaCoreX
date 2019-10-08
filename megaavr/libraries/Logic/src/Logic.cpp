#include "Logic.h"

// Array for storing ISR function pointers
static volatile voidFuncPtr intFuncCCL[4];

// Preinstantiate Object
CustomLogic Logic;

CustomLogic::CustomLogic()
{
}

void CustomLogic::start(bool state)
{
  CCL.CTRLA = (state << CCL_ENABLE_bp);
}


void CustomLogic::end()
{
  start(false);
}


void CustomLogic::init(block_t &block)
{
  // Block input 0 pin dir
  if(block.input0 == in::input)
    block.PORT->DIRCLR = PIN0_bm;
  else if(block.input0 == in::input_pullup)
  {
    block.PORT->DIRCLR = PIN0_bm;
    block.PORT->PIN0CTRL |= PORT_PULLUPEN_bm;
    block.input0 = in::input;
  }
  // Block input 1 pin dir
  if(block.input1 == in::input)
    block.PORT->DIRCLR = PIN1_bm;
  else if(block.input1 == in::input_pullup)
  {
    block.PORT->DIRCLR = PIN1_bm;
    block.PORT->PIN1CTRL |= PORT_PULLUPEN_bm;
    block.input1 = in::input;
  }
  // Block input 2 pin dir
  if(block.input2 == in::input)
    block.PORT->DIRCLR = PIN2_bm;
  else if(block.input2 == in::input_pullup)
  {
    block.PORT->DIRCLR = PIN2_bm;
    block.PORT->PIN2CTRL |= PORT_PULLUPEN_bm;
    block.input2 = in::input;
  }
  
  // Set inputs modes
  *block.LUTCTRLB = (block.input1 << 4) | block.input0;
  *block.LUTCTRLC = block.input2;

  // Set truth table
  *block.TRUTH = block.truth;
  
  // Set sequencer
  *block.SEQCTRL = block.sequencer;    

  // Set output pin state and output pin swap
  if(block.output == out::enable)
  {
    if(block.output_swap == out::pin_swap)
    {
      PORTMUX.CCLROUTEA |= (1 << block.block_number);
      block.PORT->DIRSET = PIN6_bm;
    }
    else if(block.output_swap == out::no_swap)
    {
      PORTMUX.CCLROUTEA &= ~(1 << block.block_number);
      block.PORT->DIRSET = PIN3_bm;
    }
  }
  
  // Set logic output state and output filter
  *block.LUTCTRLA = (block.output << 6) | (block.filter << 4) | (block.enable << 0);
}


void CustomLogic::attachInterrupt(block_t &block, void (*userFunc)(void), PinStatus mode)
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
  const int intmode_bp = block.block_number * 2;
  CCL.INTCTRL0 = (CCL.INTCTRL0 & ~(0x3 << intmode_bp))
      | (intmode << intmode_bp);
  
  // Store function pointer
  intFuncCCL[block.block_number] = userFunc;
}


void CustomLogic::detachInterrupt(block_t &block)
{
  // Disable interrupt for a given block output
  CCL.INTCTRL0 &= ~(0x03 << (block.block_number * 2));
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
