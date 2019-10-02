// edge detect

#ifndef LOGIC_h
#define LOGIC_h

#include <Arduino.h>

// Array for storing ISR function pointers
static volatile voidFuncPtr intFuncCCL[4];

//Use in:: when working with logic inputs
namespace in
{
  enum
  {
    masked       = 0x00,
    unused       = 0x00,
    disable      = 0x00,
    feedback     = 0x01,
    link         = 0x02,
    event_a      = 0x03,
    event_b      = 0x04,
    input        = 0x05,
    ac           = 0x06,
    input_pullup = 0x07,
    usart        = 0x08,
    spi          = 0x09,
    tca0         = 0x0A,
    tcb          = 0x0C,
  };
};

// Use out:: when working with logic outputs
namespace out
{
  enum
  {
    disable  = 0x00,
    no_swap  = 0x00,
    enable   = 0x01,
    pin_swap = 0x02,
  };
}; 

// Use filter:: when working with logic output filter
namespace filter
{
  enum
  {
    disable      = 0x00,
    synchronizer = 0x01,
    filter       = 0x02,
  };
};

// Use sequencer:: when working with LUT sequencer
namespace sequencer
{
  enum
  {
    disable      = 0x00,
    d_flip_flop  = 0x01,
    jk_flip_flop = 0x02,
    d_latch      = 0x03,
    sr_latch     = 0x04,
    rs_latch     = 0x04,
  };
};

class CustomLogic
{
  private:
    // Struct that holds all information a single logic block needs
    typedef struct
    {
      const uint8_t block_number;
      PORT_t* PORT;
      volatile uint8_t* SEQCTRL;
      volatile uint8_t* LUTCTRLA;
      volatile uint8_t* LUTCTRLB;
      volatile uint8_t* LUTCTRLC;
      volatile uint8_t* TRUTH;
      uint8_t input0;
      uint8_t input1;
      uint8_t input2;
      uint8_t output;
      uint8_t enable;
      uint8_t truth;
      uint8_t output_swap;
      uint8_t filter;
      uint8_t sequencer;
    } block_t;

  public:
    CustomLogic();
    void start(bool state = true);
    void end();
    void init(block_t &block);
    void attachInterrupt(block_t &block, voidFuncPtr callback, PinStatus mode);
    void detachInterrupt(block_t &block);
    
    // Struct object for logic block 0 (IOs connected to PORTA)
    block_t block0 = {
      .block_number = 0,
      .PORT = &PORTA, 
      .SEQCTRL = &CCL_SEQCTRL0,
      .LUTCTRLA = &CCL_LUT0CTRLA, 
      .LUTCTRLB = &CCL_LUT0CTRLB, 
      .LUTCTRLC = &CCL_LUT0CTRLC, 
      .TRUTH = &CCL_TRUTH0, 
      .input0 = in::masked, 
      .input1 = in::masked, 
      .input2 = in::masked, 
      .output = false, 
      .enable = false, 
      .truth = 0x00,
      .output_swap = out::no_swap,
      .filter = filter::disable,
      .sequencer = sequencer::disable,
    };
    
    // Struct object for logic block 1 (IOs connected to PORTC)
    block_t block1 = {
      .block_number = 1,
      .PORT = &PORTC, 
      .SEQCTRL = &CCL_SEQCTRL0,
      .LUTCTRLA = &CCL_LUT1CTRLA, 
      .LUTCTRLB = &CCL_LUT1CTRLB, 
      .LUTCTRLC = &CCL_LUT1CTRLC, 
      .TRUTH = &CCL_TRUTH1, 
      .input0 = in::masked, 
      .input1 = in::masked, 
      .input2 = in::masked, 
      .output = out::disable, 
      .enable = false, 
      .truth = 0x00,
      .output_swap = out::no_swap,
      .filter = filter::disable,
      .sequencer = sequencer::disable,
    };
    
    // Struct object for logic block 2 (IOs connected to PORTD)
    block_t block2 = {
      .block_number = 2,
      .PORT = &PORTD,
      .SEQCTRL = &CCL_SEQCTRL1,
      .LUTCTRLA = &CCL_LUT2CTRLA, 
      .LUTCTRLB = &CCL_LUT2CTRLB, 
      .LUTCTRLC = &CCL_LUT2CTRLC, 
      .TRUTH = &CCL_TRUTH2, 
      .input0 = in::masked,
      .input1 = in::masked,
      .input2 = in::masked,
      .output = out::disable,
      .enable = false,
      .truth = 0x00,
      .output_swap = out::no_swap,
      .filter = filter::disable,
      .sequencer = sequencer::disable,
    };
    
    // Struct object for logic block 3 (IOs connected to PORTF)
    block_t block3 = {
      .block_number = 3,
      .PORT = &PORTF,
      .SEQCTRL = &CCL_SEQCTRL1,
      .LUTCTRLA = &CCL_LUT3CTRLA, 
      .LUTCTRLB = &CCL_LUT3CTRLB, 
      .LUTCTRLC = &CCL_LUT3CTRLC, 
      .TRUTH = &CCL_TRUTH3, 
      .input0 = in::masked,
      .input1 = in::masked,
      .input2 = in::masked,
      .output = out::disable,
      .enable = false,
      .truth = 0x00,
      .output_swap = out::no_swap,
      .filter = filter::disable,
      .sequencer = sequencer::disable,
    };
};

extern CustomLogic Logic;

#endif
