# Logic
A library for interfacing with the CCL (Configurable Custom Logic) peripherals of the megaAVR-0 MCUs.
Developed by MCUdude for use with [MegaCoreX](https://github.com/MCUdude/MegaCoreX), adapted to megaAVR ATtiny parts by [Tadashi G. Takaoka](https://github.com/tgtakaoka), and to Dx-series by [Spence Konde](https://github.com/SpenceKonde).
The library is compatible with all these parts, but this README only covers the megaAVR-0 functionality.
The megaAVR-0 has four independent internal logic blocks that can be individually customized.
All of the megaTiny parts have 2 blocks of CCL available. The examples included assume the use of megaTinyCore in their defines to detect the applicable part.
More useful information about CCL can be found in the [Microchip Application Note TB3218](http://ww1.microchip.com/downloads/en/AppNotes/TB3218-Getting-Started-with-CCL-90003218A.pdf) and in the [megaAVR-0 family data sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/megaAVR0-series-Family-Data-Sheet-DS40002015B.pdf), part in question.


## Logic
Class for interfacing with the built-in logic block (sometimes referred to as `LUT`s - "LookUp Table").
Use the predefined objects `Logic0`, `Logic1`, `Logic2` and `Logic3`. The logic blocks are paired, each pair sharing a single sequencer and `feedback` channel.
Additionally, each logic block is associated with a specific port, having it's input on pins 0 through 2, and it's output on pin 3 or 6. In order: `PORTA`, `PORTC`, `PORTD` and `PORTF`.

These objects expose all configuration options as member variables as documented below, as well as member methods to set the applicable registers.


### enable
Variable for enabling or disabling a logic block.
Accepted values:
```c++
true;  // Enable the current logic block
false; // Disable the current logic block
```

##### Usage
```c++
Logic0.enable = true; // Enable logic block 0
```

##### Default state
`Logic0.enable` defaults to `false` if not specified in the user program.

### input0..input2
Variable for setting what mode input 0..2 on a logic block should have.

Accepted values for megaAVR 0-series parts:

``` c++
in::masked;           // Pin not in use
in::unused;           // Pin not in use
in::disable;          // Pin not in use
in::feedback;         // Connect output of sequencer (if used) or even-numbered logic block (n or n-1) to this input
in::link;             // Connect output of logic block n+1 to this input
in::event_0;          // Connect input to event a
in::event_a;          // Connect input to event a
in::event_1;          // Connect input to event b
in::event_b;          // Connect input to event b
in::pin;              // Connect input to CCL IN0, IN1, IN2 for input 0, 1, 2, do not change pinMode
in::input_pullup;     // Connect input to CCL IN0, IN1, IN2 for input 0, 1, 2, set input, pullup on
in::input;            // Connect input to CCL IN0, IN1, IN2 for input 0, 1, 2, set input, pullup off
in::input_no_pullup;  // Connect input to CCL IN0, IN1, IN2 for input 0, 1, 2, set input, pullup off
in::ac;               // Connect input to the output of the internal analog comparator (input 0,1,2 from AC0,1,2)
in::uart;             // Connect input to UART TX. Input 0 connects to UART0 TX, input 1 to UART1 TX, and input 2 to UART2 TX
in::spi;              // Connect input to SPI. Input 0 and 1 connects to MOSI, and input 2 connects to SCK
in::tca0;             // Connect input to TCA0. Input 0 connects to WO0, input 1 to WO1 and input2 to WO2
in::tca;              // Connect input to TCA0. Input 0 connects to WO0, input 1 to WO1 and input2 to WO2
in::tcb;              // Connect input to TCB. Input 0 connects to TCB0 W0, input 1 to TCB1 WO, and input 2 to TCB2 WO.
```

Notes specific to ATmega parts
* On 28-pin versions of the ATmega 4808, 3208, 1608, and 808, IN1 and IN2 inputs for logic3 are not available. If all input pins for all logic blocks are needed, the event system can be used.
* According to the datasheet for SPI as input source, inputs 0 and 1 connect to MOSI. Thus, on these parts, there is no input to the logic blocks for MISO.
* If input on the highest-number Logic block is set to link, it will use the output of Logic0
* If you need to link input to logic block other than the n+1 block, you can use the event system for that.


##### Usage
``` c++
Logic0.input0 = in::link;         // Connect output from block 1 to input 0 of block 0
Logic0.input1 = in::input;        // Connect the input 1 from block 0 to its GPIO
Logic0.input2 = in::input_pullup; // Connect the input 2 from block 0 to its GPIO, with pullup on
```

##### Default state
`LogicN.inputN` defaults to `in::unused` if not specified in the user program.


### output
Variable for changing the logic block output pin behavior. Note that the output of the logic block still can be used internally if the output pin is disabled.
Accepted values:
```c++
out::disable; // Disable the output GPIO pin. Useful when triggering an interrupt instead.
out::enable;  // Enable the output GPIO pin
```

##### Usage
```c++
Logic0.output = out::disable; // Disable the output GPIO pin.
```

##### Default state
`LogicN.output` defaults to `out::disable` if not specified in the user program.


### output_swap
Variable for pin swapping the physical output pin to its alternative position. See the pinout diagrams in the main MegaCoreX README for detailed info.
Accepted values:
```c++
out::no_swap;  // Use default pin position, pin 3 on the port
out::pin_swap; // Use alternative position, pin 6 on the port
```

##### Usage
```c++
Logic0.output_swap = out::no_swap; // No pin swap for output of block0
```

##### Default state
`LogicN.output_swap` defaults to `out::no_swap` if not specified in the user program.


### filter
Variable to control whether the output passes through a synchronizer or filter.
Useful when multiple logic blocks are connected internally to prevent race conditions and glitches that could arise due to the asynchronous nature of CCL clocking.
Alternately, the delay itself may be desirable, or it can be combined with a configuration which would oscillate asynchronously to instead output a prescaled clock, which could, in turn, be used with "clock on event" to provide a type B timer with a prescaled clock.
Either filter or synchronizer is required for edge detector, below.
Accepted values:
```c++
filter::disable;      // No filter used, asynchronous output.
filter::synchronizer; // Connect synchronizer to output; delays output by 2 clock cycles.
filter::synch;        // Syntactic sugar for synchronizer
filter::sync;         // Syntactic sugar for synchronizer
filter::filter;       // Connect filter to output; delays output by 4 clock cycles, only passes output that is stable for >2 clock cycles.
```

##### Usage
```c++
Logic0.filter = filter::filter; // Enable filter on output of block 0
```

##### Default state
`LogicN.filter` defaults to `filter::disable` if not specified in the user program.


### clocksource
Variable to set the clock source for the logic block; this is used for the synchronizer and filter only (otherwise, the logic blocks are asynchronous).
If sequential logic is used, it is clocked from the clock source used by the even-numbered logic block.
Accepted values:
```c++
clocksource::clk_per;      // Clock from the peripheral clock (ie, system clock)
clocksource::in2;          // Clock from the selected input2; it is treated as a 0 in the truth table.
```

##### Usage
```c++
Logic0.clocksource = clocksource::clk_per;
```

##### Default state
`LogicN.clocksource` defaults to `clocksource::clk_per` if not specified in the user program.


### edgedetect
Variable for controlling use of the edge detector. The edge detector can be used to generate a pulse when detecting a rising edge on its input. To detect a falling edge, the TRUTH table should be programmed to provide inverted output. In order to avoid unpredictable behavior, a valid filter option must be enabled. Note that this is likely only of use when the output is being used for sequential logic or as the input to another logic block; it looks particularly useful on the odd LUT input to a J-K flip-flop sequential logic unit.

```c++
edgedetect::disable;      // No edge detection used
edgedetect::enable;       // Edge detection used
```

#### Usage
```c++
Logic0.edgedetect = edgedetect::enable;
```

##### Default state
`LogicN.edgedetect` defaults to `edgedetect::disable` if not specified in the user program.


### sequencer
Variable for connecting a "sequencer" to the logic block output - these are latches or flip-flops which remember a state. There is 1 sequencer per 2 CCLs, each controls one of the two inputs to a flip flop or latch; this option is ignored for the odd-numbered logic blocks. Flip-flops are clocked from the same clock source as the even logic block, latches are asynchronous.

Accepted values:
```c++
sequencer::disable;      // No sequencer connected
sequencer::d_flip_flop;  // D flip flop sequencer connected
sequencer::jk_flip_flop; // JK flip flop sequencer connected
sequencer::d_latch;      // Gated D latch sequencer connected - note that on most megaAVR parts, this doesn't work. See the Errata.
sequencer::rs_latch;     // RS latch sequencer connected
```

##### Usage
```c++
Logic0.sequencer = sequencer::disable; // Disable sequencer
```

##### Default state
`LogicN.sequencer` defaults to `sequencer::disable` if not specified in the user program.


### truth
Variable to hold the 8-bit truth table value.
Accepted values between 0x00 and 0xFF.

##### Usage
```c++
Logic0.truth = 0xF0;
```

##### Default state
`LogicN.truth` defaults to `0x00` if not specified in the user program.



## init()
Method for initializing a logic block; the settings you have previously configured will be applied and pins configured as requested at this time only.

##### Usage
```c++
Logic0.init(); // Initialize block 0
Logic1.init(); // Initialize block 1
```


## start()
Method for starting the CCL hardware after desired blocks have been initialized using `LogicN.init()`.

##### Usage
```c++
Logic::start(); // Start CCL hardware
```


## stop()
Method for stopping the CCL hardware, for example to reconfigure the logic blocks.

##### Usage
```c++
Logic::stop(); // Stop CCL
```

## Reconfiguring
There are TWO levels of "enable protection" on the CCL hardware. According to the Silicon Errata, only one of these is intended. 
As always, it's anyone's guess when or if this issue will be corrected in a future silicon revision. 
The intended enable-protection is that a given logic block cannot be reconfigured while enabled. 
This is handled by `init()` - you can write your new setting to a logic block, call `LogicN.init()` and it will briefly disable the logic block, make the changes, and reenable it.

The unintended layer is that no logic block can be reconfigured without also disabling the whole CCL system. 
Changes can be freely made to the `Logic` classes, however, only the `init()` method will apply those changes, and you must call `Logic::stop()` before calling them, and `Logic::start()` afterwards. 

##### Example
```c++
// logic blocks 0, 1 configured, initialized, and in use
Logic1.truth=0x55;      // new truth table
Logic1.input2=tca0;     // and different input 2
Logic3.enabled=true;    // enable another LUT
Logic3.input0=in::link; // Use link from LUT0
Logic3.input1=in::ac;   // and the analog comparator
Logic3.input2=in::pin;  // and the LUT3 IN2 pin
Logic3.truth=0x79;      // truth table for LUT3

Logic3.attachInterrupt(RISING,interruptFunction);

// Interrupt now attached - but - Logic3 not enabled, and logic1 is using old settings

Logic::stop();  // have to turn off Logic0 too, even though I might not want to
Logic1.init();  // apply changes to logic block 1
Logic3.init();  // apply settings to logic block 3 for the first time
Logic::start(); // reenable
```

## attachInterrupt()
Method for enabling interrupts for a specific block.
Valid arguments for the third parameters are `RISING`, `FALLING` and `CHANGE`.

##### Usage
```c++
Logic0.attachInterrupt(blinkLED, RISING); // Runthe blinkLED function when the putput goes high

void blinkLED()
{
  digitalWrite(myLedPin, CHANGE);
}
```


## detachInterrupt()
Method for disabling interrupts for a specific block.

##### Usage
```c++
Logic0.detachInterrupt(); // Disable interrupts for block 0
```
