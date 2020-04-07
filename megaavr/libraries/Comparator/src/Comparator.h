#ifndef COMPARATOR_h
#define COMPARATOR_h

#include <Arduino.h>

namespace out
{
  enum output_t : uint8_t
  {
    disable = 0x00,
    enable  = 0x40,
    invert  = 0x80,
  };
};

namespace hyst
{
  enum hysteresis_t : uint8_t
  {
    disable = 0x00, // No hysteresis
    small   = 0x02, // 10 mV
    medium  = 0x04, // 25 mV
    large   = 0x06, // 50 mV
  };
};

namespace in_p
{
  enum inputP_t : uint8_t
  {
    in0    = 0x00,
    in1    = 0x01,
    in2    = 0x02,
    in3    = 0x03,
  };
};

namespace in_n
{
  enum inputN_t : uint8_t
  {
    in0    = 0x00,
    in1    = 0x01,
    in2    = 0x02,
    dacref = 0x03,
  };
};

namespace ref
{
  enum reference_t : uint8_t
  {
    vref_0v55 = 0x00, // 0.55V
    vref_1v1  = 0x01, // 1.1V
    vref_1v5  = 0x04, // 1.5V
    vref_2v5  = 0x02, // 2.5V
    vref_4v3  = 0x03, // 4.3V
    vref_avcc = 0x07, // Vcc
    disable   = 0x08,
  };
};

class AnalogComparator
{
  public:
    AnalogComparator(const uint8_t comparator_number, AC_t& ac);
    void init();
    void start(bool state = true);
    void stop();
    void attachInterrupt(voidFuncPtr callback, uint8_t mode);
    void detachInterrupt();

    out::output_t      output = out::disable;
    hyst::hysteresis_t hysteresis = hyst::disable;
    in_p::inputP_t     input_p = in_p::in0;
    in_n::inputN_t     input_n = in_n::in0;
    ref::reference_t   reference = ref::disable;
    uint8_t dacref = 0xff;

  private:
    const uint8_t comparator_number;
    AC_t& AC;
    bool enable = false;   
};

#if defined(AC0_AC_vect)
extern AnalogComparator Comparator0;
#define Comparator Comparator0
#endif

#endif
