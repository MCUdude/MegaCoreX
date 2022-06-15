# Comparator
A library for interfacing with the analog comparator peripheral in the megaAVR-0 series MCUs.
Developed by [MCUdude](https://github.com/MCUdude/).
The megaAVR-0 has one comparator where four positive and three negative pins are available for use. An alternative for the negative pin is to use an internally generated reference voltage instead.
More useful information about the analog comparator can be found in the [Microchip Application Note TB3211](http://ww1.microchip.com/downloads/en/AppNotes/TB3211-Getting-Started-with-AC-90003211A.pdf) and in the [megaAVR-0 family data sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/megaAVR0-series-Family-Data-Sheet-DS40002015B.pdf).


## Comparator
Class for interfacing with the built-in comparator. Use the predefined objects `Comparator` or `Comparator0`.


### input_p
Variable for setting what input pin the positive input of the comparator should be connected to
Accepted values:
``` c++
comparator::in_p::in0; // Use positive input pin 0 (PD2) as input
comparator::in_p::in1; // Use positive input pin 1 (PD4) as input
comparator::in_p::in2; // Use positive input pin 2 (PD6) as input
comparator::in_p::in3; // Use positive input pin 3 (PD1) as input
```

##### Usage
``` c++
Comparator.input_p = comparator::in_p::in0;  // Connect positive input pin 0 to the positive pin of the comparator
```

##### Default state
`Comparator.input_p` defaults to `comparator::in_p::in0` if not specified in the user program.


### input_n
Variable for setting what input pin the negative input of the comparator should be connected to
Accepted values:
``` c++
comparator::in_n::in0;    // Use positive input pin 0 (PD3) as input
comparator::in_n::in1;    // Use positive input pin 1 (PD5) as input
comparator::in_n::in2;    // Use positive input pin 2 (PD7) as input
comparator::in_n::dacref; // Use DACREF as input
```

##### Usage
``` c++
Comparator.input_n = comparator::in_n::in0;  // Connect negative input pin 0 to the negative pin of the comparator
```

##### Default state
`Comparator.input_n` defaults to `comparator::in_n::in0` if not specified in the user program.


### reference
Variable for setting what reference voltage the DACREF should be derived from. This voltage is internally generated.
Accepted values:
``` c++
comparator::ref::disable;   // Do not use any reference
comparator::ref::vref_0v55; // 0.55V internal voltage
comparator::ref::vref_1v1;  // 1.1V internal voltage
comparator::ref::vref_1v5;  // 1.5V internal voltage
comparator::ref::vref_2v5;  // 2.5V internal voltage
comparator::ref::vref_4v3;  // 4.3V internal voltage
comparator::ref::vref_avcc; // Use voltage on AVCC pin
```

##### Usage
``` c++
Comparator.reference = comparator::ref::vref_2v5;  // Use the internal 2.5V reference for the DACREF
```

##### Default state
`Comparator.reference` defaults to `comparator::ref::disable` if not specified in the user program.


### dacref
Variable for setting the DACREF value. This voltage can be selected as the input for the negative side of the comparator.
This is the formula for the DACREF output voltage:

<img src="http://latex.codecogs.com/svg.latex?V_{DACREF} = \frac{Comparator.dacref}{256} * Comparator.reference" border="0"/>

##### Usage
``` c++
Comparator.dacref = 127;  // Divide the reference voltage by two
```

##### Default state
`Comparator.dacref` defaults to `255` if not specified in the user program.


### hysteresis
Variable for setting the comparator input hysteresis. Useful for eliminating "bouncing".
Accepted values:
``` c++
comparator::hyst::disable; // No hysteresis
comparator::hyst::small;   // 10mV hysteresis (±5mV)
comparator::hyst::medium;  // 25mV hysteresis (±12.5mV)
comparator::hyst::large;   // 50mV hysteresis (±25mV)
```

##### Usage
``` c++
Comparator.hysteresis = comparator::hyst::large;  // Use 50V hysteresis
```

##### Default state
`Comparator.hysteresis` defaults to `comparator::hyst::disable` if not specified in the user program.


### output
Variable for setting the comparator output, internally and/or externally.
Accepted values:
``` c++
comparator::out::disable;        // No output pin, signal not inverted internally
comparator::out::disable_invert; // No output pin, signal inverted internally
comparator::out::enable;         // Enable output pin (PA7), signal not inverted internally
comparator::out::invert;         // Enable output pin (PA7), signal inverted internally
comparator::out::enable_invert;  // Identical to out::invert
```

##### Usage
``` c++
Comparator.output = comparator::out::enable; // Enable output pin (PA7)
```

##### Default state
`Comparator.output` defaults to `comparator::out::disable` if not specified in the user program.


## init()
Method for initializing the comparator.

##### Usage
```c++
Comparator.init(); // Initialize comparator
```


## start()
Method for starting the analog comparator.
##### Usage
```c++
Comparator.start(); // Start comparator
```


## stop()
Method for stopping the analog comparator.

##### Usage
```c++
Comparator.stop(); // Stop comparator
```


## read()
Reads the state of the analog comparator output. Works also when the physical output pin is disabled.

##### Usage
```c++
bool comp_state = Comparator.read(); // Read comparator
```


## attachInterrupt()
Method for enabling analog comparator interrupt. The interrupt will trigger when the the comparator output changes.
Valid arguments for the third parameters are `RISING`, `FALLING` and `CHANGE`.

##### Usage
```c++
Comparator.attachInterrupt(blinkLED, RISING); // Run the blinkLED function when the comparator output goes high

void blinkLED()
{
  digitalWrite(myLedPin, CHANGE);
}
```


## detachInterrupt()
Method for disabling analog comparator interrupt.

##### Usage
```c++
Comparator.detachInterrupt(); // Disable interrupt
```
