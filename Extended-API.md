# Extended Arduino API

MegaCoreX is Arduino compatible out of the box, but also includes extra functionality that's not available on the official Arduino "megaavr" core. This is functionality that I personally have been missing in the official Arduino API, and have added to MegaCoreX instead.

My goal isn't to "Arduino wrap" all hardware functionality the megaAVR-0 series brings to the table, but to expose functionality advanced users may benefit from and actually use. If you have a very niche application that utilizes one of the more obscure features the chip has, you're probably better off writing the low-level code yourself. Very spesific needs for ADC readings? Obscure timer needs? Read the approperiate Microchip application note w!


## Table of contents
* [Analog read resolution](#analog-read-resolution)
* [Fast IO](#fast-io)
* [Peripheral pin swapping](#peripheral-pin-swapping)
* [pinConfigure](#pinConfigure---extended-pin-configuration)
* [Printf support](#printf-support)
* [pwmWrite](#pwmwrite---flexible-pwm-routing)
* [pwmPrescaler](#pwmprescaler---pwm-frequency-setting)
* [pwmSetResolution](#pwmsetresolution)


## Analog read resolution
The default analog read resolution for these chips is 10 bit, which gives you values between 0 - 1023. If you need lower resolution you can turn it down to 8 bits instead, which gives you values between 0 - 255.
Simply call `analogReadResolution` like this:
```c
analogReadResolution(8);  // Set resolution to 8 bits
analogReadResolution(10); // Set resolution to 10 bits
```


## Fast IO
For timing critical applications the standard `digitalRead()` and `digitalWrite()` functions may be too slow. To solve this, MegaCoreX also includes some improved variants that compiles down to a single instruction.
Call `digitalReadFast(myPin)` or `digitalWriteFast(mypin, state)` to use these.<br/>
**Note that the pin number and pin state has to be known at compile time!**

### Declaration
```c++
uint8_t digitalReadFast(uint8_t pinNumber);
void digitalWriteFast(uint8_t pinNumber, uint8_t state);
```


## Peripheral pin swapping
The megaAVR-0 microcontrollers support alternative pin assignments for some of their built-in peripherals.
This is specified by invoking the `swap()` or `pins()` method before `begin()` for the associated peripheral.
They will return `true` if that swap or pin combination is supported.
For `Serial` peripherals the method is `pins(tx,rx)`, for `Wire` it's `pins(sda,scl)` and for `SPI` it's `pins(mosi,miso,sck,ss)`.
(Note that this is the same pin sequence as used for the ESP8266 `pins` method, but the opposite of the one SoftwareSerial uses.)

Note that `swap()` and `pins()` do the exact same thing, but `swap()` is MUX swap oriented, while `pins()` is pin oriented.

If you want to use this feature to implement communication with two different external devices connected to different pins using one internal peripheral,
note that the proper way to switch is first to invoke `end()` to cleanly shut down, then `swap()` or `pins()` to switch assigned pins, and finally `begin()` to cleanly start again.

`swap()` or `pins()` are called like this. **Use either `swap()` or `pins()`, not both!**

``` c++
// UART pin swapping
Serial3.swap(1);
Serial3.begin(9600);

// Wire pin swapping
Wire.swap(1);
Wire.begin();

// SPI pin swapping
SPI.swap(1);
SPI.begin();
```

Available pin combinations for the *48 pin standard* pinout are:

| Peripheral | Default                        | Alternative 1                      | Alternative 2                      |
|------------|------------------------------- |------------------------------------|------------------------------------|
| Serial     | swap(0)  **or**  pins(0,1)     | swap(1)  **or**  pins(4,5)         |                                    |
| Serial1    | swap(0)  **or**  pins(14,15)   | swap(1)  **or**  pins(18,19)       |                                    |
| Serial2    | swap(0)  **or**  pins(34,35)   | swap(1)  **or**  pins(38,39)       |                                    |
| Serial3    | swap(0)  **or**  pins(8,9)     | swap(1)  **or**  pins(12,13)       |                                    |
| Wire       | swap(0)  **or**  pins(2,3)     | swap(1)  **or**  pins(16,17)       |                                    |
| SPI        | swap(0)  **or**  pins(4,5,6,7) | swap(1)  **or**  pins(14,15,16,17) | swap(2)  **or**  pins(30,31,32,33) |

Available pin combinations for the *28 pin* and *32 pin standard* pinouts are:

| Peripheral | Default                        | Alternative                      |
|------------|--------------------------------|----------------------------------|
| Serial     | swap(0)  **or**  pins(0,1)     | swap(1)  **or**  pins(4,5)       |
| Serial1    | swap(0)  **or**  pins(8,9)     |                                  |
| Serial2    | swap(0)  **or**  pins(20,21)   | swap(1)  **or**  pins(24,25)     |
| Wire       | swap(0)  **or**  pins(2,3)     | swap(1)  **or**  pins(10,11)     |
| SPI        | swap(0)  **or**  pins(4,5,6,7) | swap(1)  **or**  pins(8,9,10,11) |

Available pin combinations for the *Uno WiFi* pinout are:

| Peripheral | Default                                                      | Alternative                                            |
|------------|--------------------------------------------------------------|--------------------------------------------------------|
| Serial     | swap(0)  **or**  pins(27,26) <br/>(connected to mEDBG)       | swap(1)  **or**  pins(9,10)                            |
| Serial1    | swap(0)  **or**  pins(1,0)                                   | swap(1)  **or**  pins(32,33) (available on SPI header) |
| Serial2    | swap(0)  **or**  pins(24,23) <br/>(connected to Wifi module) | swap(1)  **or**  pins(2,7)                             |
| Serial3    | swap(0)  **or**  pins(6,3)                                   | swap(1)  **or**  pins(37,38) (not broken out)          |

Available pin combinations for the *Nano Every* pinout are:

| Peripheral | Default                                                          | Alternative                                   |
|------------|------------------------------------------------------------------|-----------------------------------------------|
| Serial     | swap(0)  **or**  pins(25,24) <br/>(connected to USB-serial chip) | swap(1)  **or**  pins(9,10)                   |
| Serial1    | swap(0)  **or**  pins(1,0)                                       | swap(1)  **or**  pins(34,35) (not broken out) |
| Serial2    | swap(0)  **or**  pins(2,7)                                       | swap(1)  **or**  pins(28,27) (not broken out) |
| Serial3    | swap(0)  **or**  pins(6,3)                                       | swap(1)  **or**  pins(37,38) (not broken out) |


## pinConfigure - extended pin configuration
pinConfigure is a template based function that exposes all functions that can be configured on a per-pin basis. The first argument is the Arduino pin number to configure, and the second to nth parameter are the configuration parameters. The order the arguments has does not matter. The function will set the pin functionality regardless if it "makes sense" or not. If you enable interupts on a pin and there's no interrupt handler in your code, the microcontroller will crash.

### Declaration
```c++
template <typename... MODES>
void pinConfigure(const uint8_t digital_pin, const pin_configure_t mode, const MODES&... modes);
```

### Example
```c++
// Set pin PA0 to output and drive the pin high
pinConfigure(PIN_PA0, PIN_DIR_OUTPUT, PIN_OUT_HIGH);
// Disable pin PA1 completely to save power
pinConfigure(PIN_PA1, PIN_INPUT_DISABLE);
```

### Table of valid pin modes
The following parameters ca be used to set the pinConfigure modes:
| Functionality |   Enable  | Disable            | Toggle |
|---------------|-------|---------------------|--------------------|
| Direction, pinMode() | `PIN_DIR_OUTPUT`<br/>`PIN_DIR_OUT`<br/>`PIN_DIRSET` | `PIN_DIR_INPUT`<br/>`PIN_DIR_IN`<br/>`PIN_DIRCLR`       | `PIN_DIR_TOGGLE`<br/>`PIN_DIRTGL` |
| Pin output, `HIGH` or LOW | `PIN_OUT_HIGH`<br/>`PIN_OUTSET`         | `PIN_OUT_LOW`<br/>`PIN_OUTCLR`          | `PIN_OUT_TOGGLE`<br/>`PIN_OUTTGL`       |
| Internal Pullup  | `PIN_PULLUP_ON`<br/>`PIN_PULLUP`        | `PIN_PULLUP_OFF`<br/>`PIN_NOPULLUP`       | `PIN_PULLUP_TGL`       |
| Invert `HIGH` and LOW |`PIN_INVERT_ON`        | `PIN_INVERT_OFF`       | `PIN_INVERT_TGL`       |
| Digital input buffer | `PIN_INPUT_ENABLE` or<br/> `PIN_ISC_ENABLE`    | `PIN_ISC_DISABLE` or<br/>`PIN_INPUT_DISABLE`    | Not supported |
| Interrupt on change | `PIN_ISC_ENABLE` or<br/> `PIN_INPUT_ENABLE`       | `PIN_ISC_ENABLE` or<br/>`PIN_ISC_DISABLE`     | Not applicable |
| Interrupt on Rise  | `PIN_ISC_RISE` or<br/> `PIN_INT_RISE`         | `PIN_ISC_ENABLE` or<br/>`PIN_ISC_DISABLE`     | Not applicable |
| Interrupt on Fall  | `PIN_ISC_FALL` or<br/> `PIN_INT_FALL` | `PIN_ISC_ENABLE` or<br/>`PIN_ISC_DISABLE`      | Not applicable |
| Interrupt on LOW  | `PIN_ISC_LEVEL`  or<br/> `PIN_INT_LEVEL` | `PIN_ISC_ENABLE` or<br/>`PIN_ISC_DISABLE`      | Not applicable |


## Printf support
Unlike the official Arduino core, MegaCoreX has printf support out of the box. If you're not familiar with printf you should probably [read this first](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). It's added to the Print class and will work with all libraries that inherit Print. Printf is a standard C function that lets you format text much easier than using Arduino's built-in print and println. 

Note that the default printf implementation will NOT print floats or doubles by default. This is a limitation of the avr-libc printf implementation on AVR microcontrollers, but can be enabled by setting a build flag. This can easily be done if you're using [PlatformIO](https://github.com/MCUdude/MegaCoreX/blob/master/PlatformIO.md).

If you're using a serial port, simply use `Serial.printf("Milliseconds since start: %ld\n", millis());`. Other common libraries that inherit the Print class (and thus supports printf) are SoftwareSerial, the LiquidCrystal LCD library and the u8g2 graphical LCD library.


# pwmWrite - flexible PWM routing
The Arduino pinout definition and the `analogWrite` function have the PWM output pins pre-defined, and can't be moved or routed to different pins using the default Arduino API, even though the chip itself supports this. The `pwmWrite` function lets to use every supported PWM output pin, and you can route the PWM signals as you like. Note that the chip limits which timer output can be routed to which pins, and you also need to make sure you don't route the PWM signal to a pins that's used for something else, like UART or SPI. Also keep in mind that the timer used for millis/micros is occupied and can not be used for PWM generation. For the Nano Every 4809 and Uno Wifi Rev2 this means timer TCB2, and for all the other pinouts TCB2. Also note that low-pinout parts does not have timer TCB3 and all the routing pin options due to the lack of physical IO.

### Declaration
```c++
void pwmWrite(pwm_timers_t pwmTimer, uint16_t val, timers_route_t timerRoute);
```

### Example
```c++
// Route timer TCB0 PWM output to pin PF4 and set the duty cycle to 50% (128/255)
pwmWrite(TCB_0, 128, ROUTE_TCB0_PF4);
// Set the timer TCB0 duty cycle to 30% but leave the routing as is
pwmWrite(TCB_0, 76);
// Route all TCA0 timer to PORTA, enable the 2nd TCA0 PWM output (PA2 in this case), and set dyty cycle to 50%
pwmWrite(TCA0_2, 128, ROUTE_TCA0_PORTA);
```

### Table of valid options

| Timer enums | Description                      |
|-------------|----------------------------------|
| `TCA0_0`    | Identifier for TCA0 PWM output 0 |
| `TCA0_1`    | Identifier for TCA0 PWM output 1 |
| `TCA0_2`    | Identifier for TCA0 PWM output 2 |
| `TCA0_3`    | Identifier for TCA0 PWM output 3 |
| `TCA0_4`    | Identifier for TCA0 PWM output 4 |
| `TCA0_5`    | Identifier for TCA0 PWM output 5 |
| `TCB_0`     | Identifier for TCB0 PWM output   |
| `TCB_1`     | Identifier for TCB1 PWM output   |
| `TCB_2`     | Identifier for TCB2 PWM output   |
| `TCB_3`     | Identifier for TCB3 PWM output   |

| PWM routing enums  | Description                                                                     |
|--------------------|---------------------------------------------------------------------------------|
| `ROUTE_TCA0_PORTA` | Route all six TCA0 PWM channels to PA0..PA5                                     |
| `ROUTE_TCA0_PORTB` | Route all six TCA0 PWM channels to PB0..PB5 (not present on low pincount parts) |
| `ROUTE_TCA0_PORTC` | Route all six TCA0 PWM channels to PC0..PC5                                     |
| `ROUTE_TCA0_PORTD` | Route all six TCA0 PWM channels to PD0..PD5                                     |
| `ROUTE_TCA0_PORTE` | Route all six TCA0 PWM channels to PE0..PE5 (not present on low pincount parts) |
| `ROUTE_TCA0_PORTF` | Route all six TCA0 PWM channels to PF0..PF5                                     |
| `ROUTE_TCB0_PA2`   | Route the TCB0 PWM output to pin PA2                                            |
| `ROUTE_TCB0_PF4`   | Route the TCB0 PWM output to pin PF4                                            |
| `ROUTE_TCB1_PA3`   | Route the TCB1 PWM output to pin PA3                                            |
| `ROUTE_TCB1_PF5`   | Route the TCB1 PWM output to pin PF5                                            |
| `ROUTE_TCB2_PC0`   | Route the TCB2 PWM output to pin PC0                                            |
| `ROUTE_TCB2_PB4`   | Route the TCB2 PWM output to pin PB4 (not present on low pincount parts)        |
| `ROUTE_TCB3_PB5`   | Route the TCB3 PWM output to pin PB5 (not present on low pincount parts)        |
| `ROUTE_TCB3_PC1`   | Route the TCB3 PWM output to pin PC1 (not present on low pincount parts)        |


# pwmPrescaler - PWM frequency setting
`pwmPrescaler` sets the clock source that drives timer. Timer TCA0 has the most options, while the TCB timers have fewer.
The prescaler direcly affects the PWM frequency, and this is the formula that determines the frequency:
`F_CPU / resolution / prescaler`. For instance, the default TCB PWM prescaler with a system clock of 16 MHz is 1/64, which results in a PWM frequency of just under 1 kHz.

### Declaration
```c++
void pwmPrescaler(pwm_timers_t pwmTimer, timers_prescaler_t prescaler);
```

### Example
```c++
// Set the TCA0 timer prescaler to 1/64 of the system clock frequency
pwmPrescaler(TCA0_0, TCA_DIV64);
// Set timer TCB0 to run off the TCA0 clock
pwmPrescaler(TCB_0, TCB_CLKTCA);
// Set timer TCB1 prescaler to 1/2 of the system clock frequency
pwmPrescaler(TCB_1, TCB_DIV2);
```

### Table of valid options

| Prescaler     | Timer   | Description                                        | Notes                                           |
|---------------|---------|----------------------------------------------------|-------------------------------------------------|
| `TCB_DIV1`    | TCB0..3 | Runs TCB at full system clock speed                |                                                 |
| `TCB_DIV2`    | TCB0..3 | Runs TCB at 1/2 of the system clock                |                                                 |
| `TCB_CLKTCA`  | TCB0..3 | Runs TCB at the same clock as TCA0 is running off  | Default option for all TCB timers               |
| `TCA_DIV1`    | TCA0    | Runs TCA0 full system clock speed                  |                                                 |
| `TCA_DIV2`    | TCA0    | Runs TCA0 at 1/2 of the system clock               |                                                 |
| `TCA_DIV4`    | TCA0    | Runs TCA0 at 1/4 of the system clock               |                                                 |
| `TCA_DIV8`    | TCA0    | Runs TCA0 at 1/8 of the system clock               |                                                 |
| `TCA_DIV16`   | TCA0    | Runs TCA0 at 1/16 of the system clock              |                                                 |
| `TCA_DIV64`   | TCA0    | Runs TCA0 at 1/64 of the system clock              | Default option when using a 16 MHz system clock |
| `TCA_DIV256`  | TCA0    | Runs TCA0 at 1/256 of the system clock             |                                                 |
| `TCA_DIV1024` | TCA0    | Runs TCA0 at 1/1024 the system clock               |                                                 |


# pwmSetResolution
This function lets you change the PWM resolution in favour of increased PWM frequency. The default PWM range is 0-255, but the upper limit can be set to anything between 1 and 254. The resolution also affects the PWM frequency. The frequency can be calculated using this formula:  
`F_CPU / resolution / prescaler`

### Declaration
```c++
void pwmSetResolution(pwm_timers_t pwmTimer, uint8_t maxValue);
```

### Example
```c++
// Set TCA0 timer max value to 127
pwmSetResolution(TCA0_0, 127);
// Set TCB0 timer max value to 31
pwmSetResolution(TCB_0, 31);
// Set TCB1 timer max value to 99
pwmSetResolution(TCB_1, 99);
```