#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

// Helper macros to prevent us from having to check for every possible target
#if defined(__AVR_ATmega4809__) || defined(__AVR_ATmega4808__)   \
||  defined(__AVR_ATmega3209__) || defined(__AVR_ATmega3208__)   \
||  defined(__AVR_ATmega1609__) || defined(__AVR_ATmega1608__)   \
||  defined(__AVR_ATmega809__)  || defined(__AVR_ATmega808__)
  #define MEGAAVR_0
#elif defined(__AVR_AVR128DA64__) || defined(__AVR_AVR128DA48__) \
|| defined(__AVR_AVR128DA32__)    || defined(__AVR_AVR128DA28__) \
|| defined(__AVR_AVR64DA64__)     || defined(__AVR_AVR64DA48__)  \
|| defined(__AVR_AVR64DA32__)     || defined(__AVR_AVR64DA28__)  \
|| defined(__AVR_AVR32DA48__)     || defined(__AVR_AVR32DA32__)  \
|| defined(__AVR_AVR32DA28__)
  #define AVR_DA
#elif defined(__AVR_AVR128DB64__) || defined(__AVR_AVR128DB48__) \
|| defined(__AVR_AVR128DB32__)    || defined(__AVR_AVR128DB28__) \
|| defined(__AVR_AVR64DB64__)     || defined(__AVR_AVR64DB48__)  \
|| defined(__AVR_AVR64DB32__)     || defined(__AVR_AVR64DB28__)  \
|| defined(__AVR_AVR32DB48__)     || defined(__AVR_AVR32DB32__)  \
|| defined(__AVR_AVR32DB28__)
  #define AVR_DB
#endif


// Features present on all generator channels
namespace gen
{
  enum generator_t : uint8_t
  {
    disable       = 0x00,
    off           = 0x00,
    updi_synch    = 0x01,
    rtc_ovf       = 0x06,
    rtc_cmp       = 0x07,
    ccl0_out      = 0x10,
    ccl1_out      = 0x11,
    ccl2_out      = 0x12,
    ccl3_out      = 0x13,
    ac0_out       = 0x20,
    adc0_ready    = 0x24,
    usart0_xck    = 0x60,
    usart1_xck    = 0x61,
    usart2_xck    = 0x62,
    usart3_xck    = 0x63,
    spi0_sck      = 0x68,
    tca0_ovf_lunf = 0x80,
    tca0_hunf     = 0x81,
    tca0_cmp0     = 0x84,
    tca0_cmp1     = 0x85,
    tca0_cmp2     = 0x86,
    tcb0_capt     = 0xA0,
    tcb1_capt     = 0xA2,
    tcb2_capt     = 0xA4,
    tcb3_capt     = 0xA6,
    #if defined(AVR_DA) || defined(AVR_DB)
      ccl4_out      = 0x14,
      ccl5_out      = 0x15,
      ac1_out       = 0x21,
      ac2_out       = 0x22,
      zcd0_out      = 0x30,
      zcd1_out      = 0x31,
      zcd2_out      = 0x32,
      usart4_xck    = 0x64,
      usart5_xck    = 0x65,
      spi1_sck      = 0x69,
      tca1_ovf_lunf = 0x88,
      tca1_hunf     = 0x89,
      tca1_cmp0     = 0x8C,
      tca1_cmp1     = 0x8D,
      tca1_cmp2     = 0x8E,
      tcb0_ovf      = 0xA1,
      tcb1_ovf      = 0xA3,
      tcb2_ovf      = 0xA5,
      tcb3_ovf      = 0xA7,
      tcb4_capt     = 0xA8,
      tcb4_ovf      = 0xA9,
      tcd0_cmpbclr  = 0xB0,
      tcd0_cmpaset  = 0xB1,
      tcd0_cmpbset  = 0xB2,
      tcd0_progev   = 0xB3,
    #endif
    #if defined(AVR_DB)
      mvio_ok       = 0x05,
      opamp0_ready  = 0x34,
      opamp1_ready  = 0x35,
      opamp2_ready  = 0x36,
    #endif
  };
};

// Features unique to event generator channel 0
#if defined(EVSYS_CHANNEL0)
  namespace gen0
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
      pin_pb0     = 0x48,
      pin_pb1     = 0x49,
      pin_pb2     = 0x4A,
      pin_pb3     = 0x4B,
      pin_pb4     = 0x4C,
      pin_pb5     = 0x4F,
      pin_pb6     = 0x4E,
      pin_pb7     = 0x4F,
    };
  };
#endif

// Features unique to event generator channel 1
#if defined(EVSYS_CHANNEL1)
  namespace gen1
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
      pin_pb0     = 0x48,
      pin_pb1     = 0x49,
      pin_pb2     = 0x4A,
      pin_pb3     = 0x4B,
      pin_pb4     = 0x4C,
      pin_pb5     = 0x4F,
      pin_pb6     = 0x4E,
      pin_pb7     = 0x4F,
    };
  };
#endif

// Features unique to event generator channel 2
#if defined(EVSYS_CHANNEL2)
  namespace gen2
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
      pin_pc0     = 0x40,
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
      pin_pc6     = 0x46,
      pin_pc7     = 0x47,
      pin_pd0     = 0x48,
      pin_pd1     = 0x49,
      pin_pd2     = 0x4A,
      pin_pd3     = 0x4B,
      pin_pd4     = 0x4C,
      pin_pd5     = 0x4F,
      pin_pd6     = 0x4E,
      pin_pd7     = 0x4F,
    };
  };
#endif

// Features unique to event generator channel 3
#if defined(EVSYS_CHANNEL3)
  namespace gen3
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
      pin_pc0     = 0x40,
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
      pin_pc6     = 0x46,
      pin_pc7     = 0x47,
      pin_pd0     = 0x48,
      pin_pd1     = 0x49,
      pin_pd2     = 0x4A,
      pin_pd3     = 0x4B,
      pin_pd4     = 0x4C,
      pin_pd5     = 0x4F,
      pin_pd6     = 0x4E,
      pin_pd7     = 0x4F,
    };
  };
#endif

// Features unique to event generator channel 4
#if defined(EVSYS_CHANNEL4)
  namespace gen4
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
      pin_pe0     = 0x40,
      pin_pe1     = 0x41,
      pin_pe2     = 0x42,
      pin_pe3     = 0x43,
      pin_pe4     = 0x44,
      pin_pe5     = 0x45,
      pin_pe6     = 0x46,
      pin_pe7     = 0x47,
      pin_pf0     = 0x48,
      pin_pf1     = 0x49,
      pin_pf2     = 0x4A,
      pin_pf3     = 0x4B,
      pin_pf4     = 0x4C,
      pin_pf5     = 0x4D,
      pin_pf6     = 0x4E,
    };
  };
#endif

// Features unique to event generator channel 5
#if defined(EVSYS_CHANNEL5)
  namespace gen5
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
      pin_pe0     = 0x40,
      pin_pe1     = 0x41,
      pin_pe2     = 0x42,
      pin_pe3     = 0x43,
      pin_pe4     = 0x44,
      pin_pe5     = 0x45,
      pin_pe6     = 0x46,
      pin_pe7     = 0x47,
      pin_pf0     = 0x48,
      pin_pf1     = 0x49,
      pin_pf2     = 0x4A,
      pin_pf3     = 0x4B,
      pin_pf4     = 0x4C,
      pin_pf5     = 0x4D,
      pin_pf6     = 0x4E,
    };
  };
#endif

// Features unique to event generator channel 6
#if defined(EVSYS_CHANNEL6)
  namespace gen6
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
      #if defined(AVR_DA) || defined(AVR_DB)
        pin_pg0   = 0x40,
        pin_pg1   = 0x41,
        pin_pg2   = 0x42,
        pin_pg3   = 0x43,
        pin_pg4   = 0x44,
        pin_pg5   = 0x45,
        pin_pg6   = 0x46,
        pin_pg7   = 0x47,
      #endif
    };
  };
#endif

// Features unique to event generator channel 7
#if defined(EVSYS_CHANNEL7)
  namespace gen7
  {
    enum generator_t : uint8_t
    {
      disable    = 0x00,
      off        = 0x00,
      rtc_div512 = 0x08,
      rtc_div256 = 0x09,
      rtc_div128 = 0x0A,
      rtc_div64  = 0x0B,
      #if defined(AVR_DA) || defined(AVR_DB)
        pin_pg0   = 0x40,
        pin_pg1   = 0x41,
        pin_pg2   = 0x42,
        pin_pg3   = 0x43,
        pin_pg4   = 0x44,
        pin_pg5   = 0x45,
        pin_pg6   = 0x46,
        pin_pg7   = 0x47,
      #endif
    };
  };
#endif

// Features unique to event generator channel 8
#if defined(EVSYS_CHANNEL8)
  namespace gen8
  {
    enum generator_t : uint8_t
    {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
    };
  };
#endif

// Features unique to event generator channel 9
#if defined(EVSYS_CHANNEL9)
  namespace gen9
  {
    enum generator_t : uint8_t
    {
      disable    = 0x00,
      off        = 0x00,
      rtc_div512 = 0x08,
      rtc_div256 = 0x09,
      rtc_div128 = 0x0A,
      rtc_div64  = 0x0B,
    };
  };
#endif

// Generator users
namespace user
{
  enum user_t : uint8_t
  {
    #if defined(MEGAAVR_0)
      ccl0_event_a   = 0x00,
      ccl0_event_b   = 0x01,
      ccl1_event_a   = 0x02,
      ccl1_event_b   = 0x03,
      ccl2_event_a   = 0x04,
      ccl2_event_b   = 0x05,
      ccl3_event_a   = 0x06,
      ccl3_event_b   = 0x07,
      adc0_start     = 0x08,
      evouta_pin_pa2 = 0x09,
      evoutb_pin_pb2 = 0x0A,
      evoutc_pin_pc2 = 0x0B,
      evoutd_pin_pd2 = 0x0C,
      evoute_pin_pe2 = 0x0D,
      evoutf_pin_pf2 = 0x0E,
      usart0_irda    = 0x0F,
      usart1_irda    = 0x10,
      usart2_irda    = 0x11,
      usart3_irda    = 0x12,
      tca0           = 0x13,
      tcb0           = 0x14,
      tcb1           = 0x15,
      tcb2           = 0x16,
      tcb3           = 0x17,
      // "Unofficial" user generators. Uses EVOUT, but swaps the output pin using PORTMUX
      evouta_pin_pa7 = 0x89,
      evoutc_pin_pc7 = 0x8B,
      evoutd_pin_pd7 = 0x8C,
    #endif
    #if defined(AVR_DA)
      ccl0_event_a   = 0x00,
      ccl0_event_b   = 0x01,
      ccl1_event_a   = 0x02,
      ccl1_event_b   = 0x03,
      ccl2_event_a   = 0x04,
      ccl2_event_b   = 0x05,
      ccl3_event_a   = 0x06,
      ccl3_event_b   = 0x07,
      ccl4_event_a   = 0x08,
      ccl4_event_b   = 0x09,
      ccl5_event_a   = 0x0A,
      ccl5_event_b   = 0x0B,
      adc0_start     = 0x0C,
      ptc_start      = 0x0D,
      evouta_pin_pa2 = 0x0E,
      evoutb_pin_pb2 = 0x0F,
      evoutc_pin_pc2 = 0x10,
      evoutd_pin_pd2 = 0x11,
      evoute_pin_pe2 = 0x12,
      evoutf_pin_pf2 = 0x13,
      evoutg_pin_pg2 = 0x14,
      usart0_irda    = 0x15,
      usart1_irda    = 0x16,
      usart2_irda    = 0x17,
      usart3_irda    = 0x18,
      usart4_irda    = 0x19,
      usart5_irda    = 0x1A,
      tca0_cnta      = 0x1B,
      tca0_cntb      = 0x1C,
      tca1_cnta      = 0x1D,
      tca1_cntb      = 0x1E,
      tcb0_capt      = 0x1F,
      tcb0_cnt       = 0x20,
      tcb1_capt      = 0x21,
      tcb1_cnt       = 0x22,
      tcb2_capt      = 0x23,
      tcb2_cnt       = 0x24,
      tcb3_capt      = 0x25,
      tcb3_cnt       = 0x26,
      tcb4_capt      = 0x27,
      tcb4_cnt       = 0x28,
      tcd0_in_a      = 0x29,
      tcd0_in_b      = 0x2A,
      // "Unofficial" user generators. Uses EVOUT, but swaps the output pin using PORTMUX
      evouta_pin_pa7 = 0x8E,
      evoutb_pin_pb7 = 0x8F,
      evoutc_pin_pc7 = 0x90,
      evoutd_pin_pd7 = 0x91,
      evoute_pin_pe7 = 0x92,
      evoutg_pin_pg7 = 0x94,
    #endif
    #if defined(AVR_DB)
      ccl0_event_a   = 0x00,
      ccl0_event_b   = 0x01,
      ccl1_event_a   = 0x02,
      ccl1_event_b   = 0x03,
      ccl2_event_a   = 0x04,
      ccl2_event_b   = 0x05,
      ccl3_event_a   = 0x06,
      ccl3_event_b   = 0x07,
      ccl4_event_a   = 0x08,
      ccl4_event_b   = 0x09,
      ccl5_event_a   = 0x0A,
      ccl5_event_b   = 0x0B,
      adc0_start     = 0x0C,
      evouta_pin_pa2 = 0x0D,
      evoutb_pin_pb2 = 0x0E,
      evoutc_pin_pc2 = 0x0F,
      evoutd_pin_pd2 = 0x10,
      evoute_pin_pe2 = 0x11,
      evoutf_pin_pf2 = 0x12,
      evoutg_pin_pg2 = 0x13,
      usart0_irda    = 0x14,
      usart1_irda    = 0x15,
      usart2_irda    = 0x16,
      usart3_irda    = 0x17,
      usart4_irda    = 0x18,
      usart5_irda    = 0x19,
      tca0_cnta      = 0x1A,
      tca0_cntb      = 0x1B,
      tca1_cnta      = 0x1C,
      tca1_cntb      = 0x1D,
      tcb0_capt      = 0x1E,
      tcb0_cnt       = 0x1F,
      tcb1_capt      = 0x20,
      tcb1_cnt       = 0x21,
      tcb2_capt      = 0x22,
      tcb2_cnt       = 0x23,
      tcb3_capt      = 0x24,
      tcb3_cnt       = 0x25,
      tcb4_capt      = 0x26,
      tcb4_cnt       = 0x27,
      tcd0_in_a      = 0x28,
      tcd0_in_b      = 0x29,
      opamp0_enable  = 0x2A,
      opamp0_disable = 0x2B,
      opamp0_dump    = 0x2C,
      opamp0_drive   = 0x2D,
      opamp1_enable  = 0x2E,
      opamp1_disable = 0x2F,
      opamp1_dump    = 0x30,
      opamp1_drive   = 0x31,
      opamp2_enable  = 0x32,
      opamp2_disable = 0x33,
      opamp2_dump    = 0x34,
      opamp2_drive   = 0x35,
      // "Unofficial" user generators. Uses EVOUT, but swaps the output pin using PORTMUX
      evouta_pin_pa7 = 0x8D,
      evoutb_pin_pb7 = 0x8E,
      evoutc_pin_pc7 = 0x8F,
      evoutd_pin_pd7 = 0x90,
      evoute_pin_pe7 = 0x91,
      evoutf_pin_pf7 = 0x92,
      evoutg_pin_pg7 = 0x93,
    #endif
  };
};

class Event
{
  public:
    Event(uint8_t channel_num, volatile uint8_t &channel_addr);
    uint8_t get_channel_number();
    static int8_t get_user_channel(user::user_t event_user);
    void set_generator(uint8_t generator);
    uint8_t get_generator();
    void set_user(user::user_t event_user);
    void clear_user(user::user_t event_user);
    void soft_event();
    void start(bool state = true);
    void stop();

  private:
    const uint8_t channel_number;      // Holds the event generator channel number
    volatile uint8_t &channel_address; // Reference to the event channel address
    uint8_t generator_type;            // Generator type the event channel is using
};

#if defined(EVSYS_CHANNEL0)
  extern Event Event0;
#endif
#if defined(EVSYS_CHANNEL1)
  extern Event Event1;
#endif
#if defined(EVSYS_CHANNEL2)
  extern Event Event2;
#endif
#if defined(EVSYS_CHANNEL3)
  extern Event Event3;
#endif
#if defined(EVSYS_CHANNEL4)
  extern Event Event4;
#endif
#if defined(EVSYS_CHANNEL5)
  extern Event Event5;
#endif
#if defined(EVSYS_CHANNEL6)
  extern Event Event6;
#endif
#if defined(EVSYS_CHANNEL7)
  extern Event Event7;
#endif
#if defined(EVSYS_CHANNEL8)
  extern Event Event8;
#endif
#if defined(EVSYS_CHANNEL9)
  extern Event Event9;
#endif

#endif // EVENT_H
