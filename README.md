# MegaCoreX
[![Build Status](https://travis-ci.com/MCUdude/MegaCoreX.svg?branch=master)](https://travis-ci.com/MCUdude/MegaCoreX)

An Arduino core for ATmega4809, ATmega4808, ATmega3209, ATmega3208, ATmega1609, ATmega1608, ATmega809 and ATmega808. This megaAVR-0 chip family offers lots of features and peripherals at an incredible price point. The largest one, the ATmega4809 can be found in products like the Arduino Uno WiFi Rev2 and the Arduino Nano Every. Some of their key features include multiple serial ports, SPI and i2c interfaces, built-in programmable logic, up to 16 analog input pins, and an analog comparator with a built-in programmable voltage reference and hysteresis and much more!

Compared to older AVR families they also have more advanced and accurate internal oscillators which can provide base frequencies of 16 and 20 MHz. These can then be divided down internally to reduce the processor speed and power consumption. This means in most applications an external clock isn't necessary anymore. You can read more about clocks and clock frequencies in the [Supported clock frequencies](#supported-clock-frequencies) section.

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
* [EEPROM retain option](#eeprom-option)
* [Reset pin](#reset-pin)
* [Printf support](#printf-support)
* [Fast IO](#fast-io)
* [Pin macros](#pin-macros)
* [Write to own flash](#write-to-own-flash)
* [Memory-mapped flash](#memory-mapped-flash)
* [Pinout](#pinout)
* [Hardware features](#hardware-features)
  - [PWM output](#pwm-output)
  - [Configurable Custom Logic (CCL)](#configurable-custom-logic-ccl)
  - [Analog Comparator (AC)](#analog-comparator-ac)
  - [Event System (EVSYS)](#event-system-evsys)
  - [Peripheral pin swapping](#peripheral-pin-swapping)
* [How to install](#how-to-install)
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
  - [PlatformIO](#platformio)
* [Minimal setup](#minimal-setup)
* [Getting your hardware working](#getting-your-hardware-working)
  - [Arduino Uno WiFi Rev2](#arduino-uno-wifi-rev2)
  - [Arduino Nano Every](#arduino-nano-every)
  - [Nano 4808](#nano-4808)
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

<b>†</b> 64 bytes of USERROW, accessible from address 256 to 319 using the EEPROM.h library <br/>
<b>&ast;</b> TQFP32/QFN32 package <br/>
<b>&ast;&ast;</b> SSOP28 package <br/>
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


## EEPROM option
If you want the EEPROM to be erased every time you burn the bootloader or upload using a programmer, you can turn off this option. You'll have to connect a UPDI programmer and hit "Burn bootloader" to enable or disable EEPROM retain. Note that when uploading using a bootloader, the EEPROM will always be retained.


## Reset pin
None of the megaAVR-0 microcontrollers needs the reset line to be reprogrammed over the UPDI interface. This means that the reset pin can be used as a GPIO pin instead! There's no need for a high voltage programmer to turn that pin into a reset pin again either. If you have a development board you can instead use the reset button as a general-purpose button for your project. Note that the reset pin cannot be usd as a GPIO when using a bootloader.


## Printf support
Unlike the official Arduino core, MegaCoreX has printf support out of the box. If you're not familiar with printf you should probably [read this first](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). It's added to the Print class and will work with all libraries that inherit Print. Printf is a standard C function that lets you format text much easier than using Arduino's built-in print and println. 

[**See the extended API documentation for more information!**](https://github.com/MCUdude/MegaCoreX/tree/master/Extended-API.md#printf-support)


## Fast IO
For timing critical applications the standard `digitalRead()` and `digitalWrite()` functions may be too slow. To solve this, MegaCoreX also incorporates `digitalReadFast(myPin)` and `digitalWriteFast(mypin, state)` which compiles down to a single instruction.

[**See the extended API documentation for more information!**](https://github.com/MCUdude/MegaCoreX/tree/master/Extended-API.md#fast-io)


## Pin macros
Note that you don't have to use the digital pin numbers to refer to the pins. You can also use some predefined macros that map "Arduino pins" to the port and port number.
Note that all my Arduino cores have these macros if you prefer to use these rather than the default Arduino pin number.

```c++
// Use PIN_PA0 macro to refer to pin PA0 (Arduino pin 0)
digitalWrite(PIN_PA0, HIGH);

// Results in the exact same compiled code
digitalWrite(0, HIGH);
```


## Write to own flash
As an alternative for UPDI, MegaCoreX uses Optiboot Flash, a bootloader that supports flash writing within the running application, thanks to the work of [@majekw](https://github.com/majekw).
This means that content from e.g. a sensor can be stored in the flash memory directly without the need of external memory. Flash memory is much faster than EEPROM, and can handle at least 10 000 write cycles before wear becomes an issue.
For more information on how it works and how you can use this in you own application, check out the [Serial_read_write](https://github.com/MCUdude/MegaCoreX/blob/master/avr/libraries/Optiboot_flasher/examples/Serial_read_write/Serial_read_write.ino) for a simple proof-of-concept demo, and
[Flash_put_get](https://github.com/MCUdude/MegaCoreX/blob/master/avr/libraries/Optiboot_flasher/examples/Flash_put_get/Flash_put_get.ino) + [Flash_iterate](https://github.com/MCUdude/MegaCoreX/blob/master/avr/libraries/Optiboot_flasher/examples/Flash_iterate/Flash_iterate.ino) for useful examples on how you can store strings, structs and variables to flash and retrieve then afterwards.


## Memory-mapped flash
Unlike classic AVRs, the flash memory on these parts is within the same address space as the main memory. This means that functions like `pgm_read_byte()` and `pgm_read_word()` is not needed to read directly from flash. Because of this, the compiler automatically puts any variable declared const into PROGMEM, and accesses it appropriately - you no longer need to explicitly declare them as PROGMEM!
This also includes quoted strings, which means that the string in `Serial.print("Hello World");` won't consume any RAM. This means that the `F()` macro is not needed when working with MegaCoreX.

If you explicitly declare a variable PROGMEM, you must still use the `pgm_read_byte()/pgm_read_word()` functions, just like on "classic" AVRs. Do note that declaring things PROGMEM or using the `F()` macro works fine, but it is slower and consumes more flash than simply declaring something `const` or omitting the `F()` macro.


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

### Configurable Custom Logic (CCL)
The megaAVR-0 microcontrollers are equipped with four independent configurable logic blocks that can be used to improve speed and performance. The CCL pins are marked on all pinout diagrams in a dark blue/grey color. The logic blocks can be used independently from each other, connected together or generate an interrupt to the CPU. I've made a [light weight, high-level library](https://github.com/MCUdude/MegaCoreX/tree/master/megaavr/libraries/Logic) for easy integration with the CCL hardware.

### Analog Comparator (AC)
The megaAVR-0 microcontrollers are equipped with an analog comparator. It compares the voltage levels on two inputs and gives a digital output based on this comparison. The megAVR chip has four positive AC pins and three negative. There's also a configurable internal voltage reference that can be used on the negative comparator pin instead of an external voltage.
Try out the [Comparator library](https://github.com/MCUdude/MegaCoreX/tree/master/megaavr/libraries/Comparator) for more information, library reference and examples.

### Event System (EVSYS)
The Event System (EVSYS) enables direct peripheral-to-peripheral signaling. It allows a change in one peripheral (the event generator) to trigger actions in other peripherals (the event users) through event channels, without using the CPU. It is designed to provide short and predictable response times between peripherals, allowing for autonomous peripheral control and interaction, and also for synchronized timing of actions in several peripheral modules. It is thus a powerful tool for reducing the complexity, size, and execution time of the software. Give the [Event library](https://github.com/MCUdude/MegaCoreX/tree/master/megaavr/libraries/Event) a try! Here you'll find documentation and useful library examples.

### Peripheral pin swapping
The megaAVR-0 microcontrollers support alternative pin assignments for some of their built-in peripherals.<br/>
MegaCoreX currently supports pinswapping the SPI, i2c and UART peripheral pins.

[**See the extended API documentation for more information!**](https://github.com/MCUdude/MegaCoreX/tree/master/Extended-API.md#peripheral-pin-swapping)


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

#### PlatformIO
[PlatformIO](http://platformio.org) is an open source ecosystem for IoT development and supports MegaCoreX.

**See [PlatformIO.md](https://github.com/MCUdude/MegaCoreX/blob/master/PlatformIO.md) for more information.**


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

### Nano 4808
The Nano 4808, also known as the Thinary Nano 4808 a third-party Arduino compatible board with the Nano form factor. It uses an ATmega4808 and the *only* supported pinout is *Nano 4808*. Printing to the serial monitor on your PC is done by initializing `Serial.begin(baud)`. The Nano 4808 does not support a bootloader, so select *No bootloader* in the tools menu. The on-board JTAG2UPDI programmer is known to be difficult to enter programming mode when printing to the serial monitor. If you're having upload issues, connect a dedicated UPDI programmer to the UPDI pin, select it in the programmers menu and upload using the programmer.
Click to enlarge:

<img src="https://i.imgur.com/ykebGW7.png" width="400">

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
