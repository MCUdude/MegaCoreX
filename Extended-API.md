# Extended Arduino API

MegaCoreX is Arduino compatible out of the box, but also includes extra functionality that's not available on the official Arduino "megaavr" core. This is functionality that I personally have been missing in the official Arduino API, and have added to MegaCoreX instead.

My goal isn't to "Arduino wrap" all hardware functionality the megaAVR-0 series brings to the table, but to expose functionality advanced users may benefit from and actually use. If you have a very niche application that utilizes one of the more obscure features the chip has, you're probably better off writing the low-level code yourself. Very spesific needs for ADC readings? Obscure timer needs? Read the approperiate Microchip application note w!


## Table of contents
* [Analog read resolution](#analog-read-resolution)
* [Fast IO](#fast-io)
* [Peripheral pin swapping](#peripheral-pin-swapping)
* [pinConfigure](#pinConfigure---extended-pin-configuration)
* [Printf support](#printf-support)


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
