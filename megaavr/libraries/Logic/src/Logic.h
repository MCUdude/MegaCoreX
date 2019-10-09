#ifndef LOGIC_h
#define LOGIC_h

#include <Arduino.h>

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
    enable   = 0x01,
    no_swap  = 0x00,
    pin_swap = 0x01,
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

class Logic
{
  private:
    const uint8_t block_number;
    PORT_t& PORT;
    volatile register8_t& SEQCTRL;
    volatile register8_t& LUTCTRLA;
    volatile register8_t& LUTCTRLB;
    volatile register8_t& LUTCTRLC;
    volatile register8_t& TRUTH;
    
  public:
    static void start(bool state = true);
    static void end();

    Logic(const uint8_t block_number,
          PORT_t& port,
          register8_t& seq_ctrl,
          register8_t& lut_ctrla,
          register8_t& lut_ctrlb,
          register8_t& lut_ctrlc,
          register8_t& truth);
    void init();
    void attachInterrupt(voidFuncPtr callback, PinStatus mode);
    void detachInterrupt();

    uint8_t input0;
    uint8_t input1;
    uint8_t input2;
    uint8_t output;
    uint8_t enable;
    uint8_t truth;
    uint8_t output_swap;
    uint8_t filter;
    uint8_t sequencer;


};

extern Logic Logic0, Logic1, Logic2, Logic3;

#endif
