# MegaCoreX
[![Build Status](https://travis-ci.org/MCUdude/MegaCoreX.svg?branch=master)](https://travis-ci.org/MCUdude/MegaCoreX)

An Arduino core for ATmega4809, ATmega4808, ATmega3209, ATmega3208, ATmega1609, ATmega1608, ATmega809 and ATmega808. This megaAVR-0 chip family offers lots of features and peripherals at an incredible price point. Its largest variant, the ATmega4809 can be found in products like the Arduino Uno WiFi Rev2 and the Arduino Nano Every. Some of their key features include multiple serial ports, SPI and i2c interfaces, built-in programmable logic, up to 16 analog input pins, and an analog comparator with a built-in programmable voltage reference and hysteresis.

Compared to older AVR families they also have more advanced and accurate internal oscillators which can provide base frequencies of 16 and 20 MHz. These can again be divided down internally to reduce the processor speed and power consumption. This means in most applications an external clock isn't necessary anymore. You can read more about clocks and clock frequencies in the [Supported clock frequencies](#supported-clock-frequencies) section.

For programming, these chips use a UPDI programming interface. This is a bi-directional single wire interface and requires a programmer that supports UPDI. If you rather prefer uploading using a USB to serial adapter there is an option to use the Optiboot bootloader. Read more about UPDI and bootloaders in the [Programming](#programming) section below.

If you're looking for a sleek, reliable UPDI programmer that also acts as a USB to serial adapter, check out the microUPDI programmer! It's a small breakout board where you add your own Arduino Pro Micro board, and flash it with the right firmware using Arduino IDE. You can buy the microUPDI programmer over at my [Tindie store](https://www.tindie.com/products/MCUdude/microupdi-programmer/), and you can flash your Arduino Pro Micro with the correct firmware by installing [microUPDIcore](https://github.com/MCUdude/microUPDI).

<img src="https://i.imgur.com/4QNsoYy.jpg" width="270"> <img src="https://i.imgur.com/wRKdPAw.jpg" width="270"> <img src="https://i.imgur.com/actXUKu.png" width="270">

# Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Programming](#programming)
  - [Using a UPDI programmer](#using-a-updi-programmer)
  - [Using a bootloader](#using-a-bootloader)
* [Supported clock frequencies](#supported-clock-frequencies)
* [BOD option](#bod-option)
* [Reset pin](#reset-pin)
* [Printf support](#printf-support)
* [Fast IO](#fast-io)
* [Pin macros](#pin-macros)
* [Pinout](#pinout)
* [Hardware features](#hardware-features)
  - [PWM output](#pwm-output)
  - [Analog read resolution](#analog-read-resolution)
  - [Configurable Custom Logic (CCL)](#configurable-custom-logic-ccl)
  - [Analog Comparator (AC)](#analog-comparator-ac)
  - [Alternative pins](#alternative-pins)
* [How to install](#how-to-install)
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
* [Minimal setup](#minimal-setup)
* [Getting your hardware working](#getting-your-hardware-working)
  - [Arduino Uno WiFi Rev2](#arduino-uno-wifi-rev2)
  - [Arduino Nano Every](#arduino-nano-every)
  - [Curiosity Nano](#curiosity-nano)
  - [AVR-IOT-WG](#avr-iot-wg)
  - [4809 Xplained Pro](#atmega4809-xplained-pro)


## Supported microcontrollers

|                  | Mega4809                   | Mega4808                          | Mega3209          | Mega3208                          | Mega1609          | Mega1608                          | Mega809           | Mega808                           |
|------------------|----------------------------|-----------------------------------|-------------------|-----------------------------------|-------------------|-----------------------------------|-------------------|-----------------------------------|
| **Flash**        | 48 kiB                     | 48 kiB                            | 32 kiB            | 32 kiB                            | 16 kiB            | 16 kiB                            | 8 kiB             | 8 kiB                             |
| **RAM**          | 6 kiB                      | 6 kiB                             | 4 kiB             | 4 kiB                             | 2 kiB             | 2 kiB                             | 1 kiB             | 1 kiB                             |
| **EEPROM**       | 256 B +<br/>64 B†          | 256 B +<br/>64 B†                 | 256 B +<br/>64 B† | 256 B +<br/>64 B†                 | 256 B +<br/>64 B† | 256 B +<br/>64 B†                 | 256 B +<br/>64 B† | 256 B +<br/>64 B†                 |
| **Serial ports** | 4                          | 3                                 | 4                 | 3                                 | 4                 | 3                                 | 4                 | 3                                 |
| **IO pins**      | 41<br/>33&ast;&ast;&ast;   | 27&ast;<br/>24&ast;&ast;          | 41                | 27&ast;<br/>24&ast;&ast;          | 41                | 27&ast;<br/>24&ast;&ast;          | 41                | 27&ast;<br/>24&ast;&ast;          |
| **Packages**     | TQFP48<br/>QFN48<br/>DIP40 | TQFP32<br/>QFN32<br/>SSOP28       | TQFP48<br/>QFN48  | TQFP32<br/>QFN32<br/>SSOP28       | TQFP48<br/>QFN48  | TQFP32<br/>QFN32<br/>SSOP28       | TQFP48<br/>QFN48  | TQFP32<br/>QFN32<br/>SSOP28       |

<b>†</b> 64 bytes of USERROW, accessible from address 256 to 319 using the EEPROM.h library
<b>&ast;</b> TQFP32/QFN32 package
<b>&ast;&ast;</b> SSOP28 package
<b>&ast;&ast;&ast;</b> DIP40 package


## Programming
### Using a UPDI programmer
Programming must be done with a UPDI compatible programmer, such as the [microUPDI](https://github.com/MCUdude/microUPDI), [JTAG2UPDI](https://github.com/ElTangas/jtag2updi) or an official Atmel/Microchip UPDI compatible programmer.

Unlike the Arduino UNO WiFi Rev2 boards package MegaCoreX does not auto-detect the programmer you're using. You'll have to select the correct programmer in the *Programmers*. If you're using an Arduino Uno Wifi Rev2 board, a Curiosity Nano or an Xplained Pro board you'll have to choose mEDBG, nEDBG or EDBG.

### Using a bootloader
Programming can also be done using the [Optiboot bootloader](https://github.com/optiboot/Optiboot). It is available for all megaAVR-0 chips and can be used with all hardware serial ports including alternative pin positions. Simply select what UART number to use, default/alternative pin position and click "Burn bootloader". The bootloader will flash an LED connected to PA7 (digital pin 7 on most pinouts) twice when a hardware reset occurs. The upload speed is 115200 baud. Note that that the reset pin cannot be used as a GPIO when using a bootloader. It doesn't matter if you have set the reset pin as GPIO in the tools menu or not; the bootloader option will override this setting.

## Supported clock frequencies
MegaCoreX lets you choose what clock frequency you want to run your microcontroller at.

| Frequency | Oscillator type     | Other                    |
|-----------|---------------------|--------------------------|
| 20 MHz    | Internal oscillator |                          |
| 16 MHz    | Internal oscillator | **Default option**       |
| 10 MHz    | Internal oscillator | Derived from 20 MHz osc. |
| 8 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 5 MHz     | Internal oscillator | Derived from 20 MHz osc. |
| 4 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 2 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 1 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 20 MHz    | External clock      |                          |
| 16 MHz    | External clock      |                          |
| 12 MHz    | External clock      |                          |
| 8 MHz     | External clock      |                          |
| 1 MHz     | External clock      |                          |

Note that unlike other AVRs **none of these chips can drive an external crystal or resonator**. If you need an external oscillator it has to be one with a driven clock output.
The microcontroller will freeze if the external clock suddenly drops out. If not present on boot, it will automatically choose the 16 MHz internal oscillator instead.

Another thing to watch out for is the lowest possible baudrates when running at 16 or 20 MHz. At 16 MHz the lowest baud rate is 1200 baud. When running at 20 MHz the lowest is 2400 baud. This is caused by the way the internal baud rate generator works. If you need lower baud rates you'll either have to reduce the main clock speed or use the software serial library instead.


## BOD option
Brownout detection or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brownout setting. Below is a table that shows the available BOD options:

| BOD threshold                  |
|--------------------------------|
| 4.3 V                          |
| 4.0 V                          |
| 3.7 V                          |
| 3.3 V                          |
| 2.9 V                          |
| **2.6 V** (default option)     |
| 2.1 V                          |
| 1.8 V                          |
| Disabled                       |


## Reset pin
None of the megaAVR-0 microcontrollers needs the reset line to be reprogrammed over the UPDI interface. This means that the reset pin can be used as a GPIO pin instead! There's no need for a high voltage programmer to turn that pin into a reset pin again either. If you have a development board you can instead use the reset button as a general-purpose button for your project. Note that the reset pin cannot be usd as a GPIO when using a bootloader.


## Printf support
Unlike the official Arduino core, MegaCoreX has printf support out of the box. If you're not familiar with printf you should probably [read this first](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). It's added to the Print class and will work with all libraries that inherit Print. Printf is a standard C function that lets you format text much easier than using Arduino's built-in print and println. Note that this implementation of printf will NOT print floats or doubles. This is a limitation of the avr-libc printf implementation on AVR microcontrollers, and nothing I can easily fix.

If you're using a serial port, simply use `Serial.printf("Milliseconds since start: %ld\n", millis());`. Other libraries that inherit the Print class (and thus supports printf) are SoftwareSerial and the LiquidCrystal LCD library.


## Fast IO
For timing critical applications the standard `digitalRead()` and `digitalWrite()` functions may be too slow. To solve this, MegaCoreX also includes some improved variants that compile down to a single instruction.
Call `digitalReadFast(myPin)` or `digitalWriteFast(mypin, state)` to use these. Note that in order to gain any speed improvements, the pin number has to be a constant.


## Pin macros
Note that you don't have to use the digital pin numbers to refer to the pins. You can also use some predefined macros that map "Arduino pins" to the port and port number.
Note that all my Arduino cores have these macros if you prefer to use these rather than the default Arduino pin number.

```c++
// Use PIN_PA0 macro to refer to pin PA0 (Arduino pin 0)
digitalWrite(PIN_PA0, HIGH);

// Results in the exact same compiled code
digitalWrite(0, HIGH);
```


## Pinout
This core provides several different Arduino pin mappings based on your current hardware
- **48 pin standard**: This pinout is much closer to the actual hardware than the Uno WiFi pinout. It will not be compatible with shields or anything like that, but it's much cleaner and elegant from a hardware point of view. The only pin swap done by default is the PWM output pins. This is done to prevent them from "colliding" with other peripherals. Note that this pinout is only available on ATmega3209/ATmega4809.
- **40 pin standard**: This pinout is more or less identical to the 48 pin variant, but with a reduced pin number. Note that this pinout is only available on ATmega4809.
- **32 pin standard**: This is the pinout for the 32 pin version of the ATmega3208/4808. Again, it will not be compatible with shields or anything like that, but it's clean and elegant from a hardware point of view. The only pin swap done by default is the PWM output pins. This is done to prevent them from "colliding" with other peripherals.
- **28 pin standard**: This is the pinout for the 28 pin version of the ATmega3208/4808. It will not be compatible with shields or anything like that, but it's still clean and elegant from a hardware point of view. Only pin swap done by default is the PWM output pins. This is done to prevent them from "colliding" with other peripherals.
- **Uno WiFi**: This pinout is 100% compatible with the Arduino Uno WiFi Rev2 hardware. If you have code that's written for the Uno WiFi Rev2 it will work without any modifications if you choose this pinout. Note that this pinout does pin swapping on serial interfaces and PWM pins by default, and some peripherals are renamed to match the original 328P Uno hardware better. Note that this pinout is only available on ATmega3209/ATmega4809.
- **Nano Every**: This pinout is 100% compatible with the Arduino Nano Every. If you have code that's written for the Nano Every it will work without any modifications if you choose this pinout. Note that this pinout does pin swapping on serial interfaces and PWM pins by default, and some peripherals are renamed to match the original 328P Uno hardware better. This pinout is only available when ATmega4809 is selected.

Please have a look at the pins_arduino.h files for detailed info.<br/> <br/>
<b>Click to enlarge:</b>

| **MegaCoreX ATmega809/1609/3209/4809 pinout**                                                                                                                                 | **MegaCoreX ATmega808/1608/3208/4808 pinout**                                                                                                                                                                                        |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|<img src="https://i.imgur.com/3PUBB6H.jpg" width="350"><br/><img src="https://i.imgur.com/QbOOOTd.png" width="350"><br/><img src="https://i.imgur.com/Hp21SXJ.jpg" width="350">|<img src="https://i.imgur.com/2YlmE8p.png" width="350"><br/><br/><br/><br/><img src="https://i.imgur.com/zXyWvi1.png" width="350"><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>|


## Hardware features
Here's some hardware specific features that differ from the older AVR families.

### Interrupt pins
Unlike older AVRs the megaAVR-0 microcontrollers have fully featured interrupts on every pin.
Supported states are *RISING*, *FALLING*, *CHANGE*, *HIGH* and *LOW*. This means there's no need to use the `digitalPinToInterrupt` macro. Simply call attachInterrupt like this:

```c
attachInterrupt(myPin, myInterruptFunction, RISING);
```

### PWM output
PWM output, `analogWrite()`, is available for the following pins:

| Pinout            | Number of PWM pins | Available PWM pins                 |
|-------------------|--------------------|------------------------------------|
| *28 pin standard* | 8                  | 2, 3, 12, 13, 14, 15, 16, 17       |
| *32 pin standard* | 8                  | 2, 3, 12, 13, 14, 15, 16, 17       |
| *40 pin standard* | 8                  | 8, 9, 10, 11, 12, 13, 30, 31       |
| *48 pin standard* | 9                  | 13, 14, 15, 16, 17, 18, 19, 38, 39 |
| *Uno WiFi*        | 6                  | 3, 5, 6, 9, 10, 27                 |
| *Nano Every*      | 5                  | 3, 5, 6, 9, 10                     |

The repeat frequency for the pulses on all PWM outputs can be changed with the new function `analogWriteFrequency(kHz)`, where
`kHz` values of 1 (default), 4, 8, 16, 32 and 64 are supported. Note that these values are very approximate. The best effort within the constraints of the hardware will be made to match the request.

Note also that tone() will use TCB1, so the corresponding PWM output is not available if it is used.

### Analog read resolution
The default analog read resolution for these chips is 10 bit, which gives you values between 0 - 1023. If you need less resolution you can turn it down to 8 bits instead, which gives you values between 0 - 255.
Simply call `analogReadResolution` like this:
```c
analogReadResolution(8); // Set resolution to 8 bits
```

### Configurable Custom Logic (CCL)
The megaAVR-0 microcontrollers are equipped with four independent configurable logic blocks that can be used to improve speed and performance. The CCL pins are marked on all pinout diagrams in a dark blue/grey color. The logic blocks can be used independently from each other, connected together or generate an interrupt to the CPU. I've made a [light weight, high-level library](https://github.com/MCUdude/MegaCoreX/tree/master/megaavr/libraries/Logic) for easy integration with the CCL hardware.

### Analog Comparator (AC)
The megaAVR-0 microcontrollers are equipped with an analog comparator. It compares the voltage levels on two inputs and gives a digital output based on this comparison. The megAVR chip has four positive AC pins and three negative. There's also a configurable internal voltage reference that can be used on the negative comparator pin instead of an external voltage.
Try out the [Comparator library](https://github.com/MCUdude/MegaCoreX/tree/master/megaavr/libraries/Comparator) for more information, library reference and examples.

### Alternative pins
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


## How to install
#### Boards Manager Installation
* Open Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**:
    ```
    https://mcudude.github.io/MegaCoreX/package_MCUdude_MegaCoreX_index.json
    ```
* Separate the URLs using a comma ( **,** ) if you have more than one URL
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **MegaCoreX** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation
Click on the "Download ZIP" button. Extract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE and a new category in the boards menu called "MightyCoreX" will show up.


## Minimal setup
Here are some simple schematics that show a minimal setup. The straight 6-pin header may in the future be used for serial uploads without having to use a UPDI programmer. As of today, we're still waiting for a stable version of Optiboot.
<b>Click to enlarge:</b> <br/>

| 48-pin *ATmega809/1609/3209/4809*                     | 40-pin *ATmega4809*                                   | 32-pin *ATmega808/1608/3208/4808*                     |
|-------------------------------------------------------|-------------------------------------------------------|-------------------------------------------------------|
|<img src="https://i.imgur.com/xNgxbzX.png" width="270">|<img src="https://i.imgur.com/WnjFIEG.png" width="270">|<img src="https://i.imgur.com/yoGETML.png" width="270">|

## Getting your hardware working
### Arduino Uno WiFi Rev2
[The Arduino Uno WiFi Rev2](https://store.arduino.cc/arduino-uno-wifi-rev2) is one of the few megaAVR-0 based boards that's officially supported by Arduino. It uses an ATmega4809 and the recommended pinout is *Uno WiFi*. Printing to the serial monitor on your PC is done by initializing `Serial.begin(baud)`. You'll also have to choose **Atmel mEDBG (ATmega32u4)** as your programmer to upload code. Uno WiFi Rev2 does not support a bootloader, so select *No bootloader* in the tools menu. For more information about this board please see the product page and its schematic.

Click to enlarge:
<img src="https://i.imgur.com/UzDYb9f.png" width="400">

### Arduino Nano Every
[The Arduino Nano Every](https://store.arduino.cc/arduino-nano-every) is one of the few megaAVR-0 based boards that's officially supported by Arduino. It uses an ATmega4809 and the *only* supported pinout is *Nano Every*. Printing to the serial monitor on your PC is done by initializing `Serial.begin(baud)`. The Nano Every does not support a bootloader, so select *No bootloader* in the tools menu. Burning bootloader or upload using programmer will not work either. However, all fuses are set every time you upload our program. For more information about this board please see the product page and its schematic.

Click to enlarge:
<img src="https://i.imgur.com/KyRef6p.png" width="400">

### Curiosity Nano
[The Curiosity Nano](https://www.microchip.com/developmenttools/ProductDetails/DM320115) uses an ATmega4809 but has a different pinout than the Uno Wifi Rev2. The recommended pinout for this board is *48 pin standard*. The on-board LED is connected t pin PF5 (digital pin 39). Note that UART3 is connected to the nEDBG chip (often referred to as the debug serial port). This means you'll have to use `Serial3.begin(baud)` to print to the serial monitor. You'll also have to choose **Atmel nEDBG (ATSAMD21E18)** as your programmer to upload code. For more information about this board please refer to the user guide and its schematic.

Click to enlarge:
<img src="https://i.imgur.com/bmdfCFS.jpg" width="350">

### AVR-IOT WG
[The AVR-IOT WG](https://www.microchip.com/developmenttools/ProductDetails/AC164160) uses the ATmega4808 in a 32 pin package. *32 pin standard* is the correct pinout for this board. Note that UART2 is connected to the nEDBG chip (often referred to as the debug serial port). This means you'll have to use `Serial2.begin(baud)` to print to the serial monitor. You'll also have to choose **Atmel nEDBG (ATSAMD21E18)** as your programmer to upload code. For more information about this board please refer to the user guide and its schematic.

Click to enlarge:
<img src="https://i.imgur.com/IwHHZHx.png" width="350">

### ATmega4809 Xplained Pro
[The ATmega4809 Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/atmega4809-xpro) uses an ATmega4809. The recommended pinout for this board is *48 pin standard*. Note that the UART1 is connected to the EDBG chip (often referred to as the debug serial port). This means you'll have to use `Serial1.begin(baud)` to print to the serial monitor. You'll also have to choose **Atmel EDBG (AT32UC3A4256)** as your programmer to upload code. For more information about this board please refer to the user guide and its schematic.

Click to enlarge:
<img src="https://i.imgur.com/6G5FELO.jpg" width="400">
