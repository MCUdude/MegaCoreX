# MegaCoreX

An Arduino core for the new megaAVR series!

**TODO:**
* Readme
  - Need some good intro text at the beginning
  - Bootloader info


# Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Programming](#programming)
* [Supported clock frequencies](#supported-clock-frequencies)
* [BOD option](#bod-option)
* [Reset pin](#reset-pin)
* [Pinout](#pinout)
* [PWM output](#pwm-output)
* [Configurable Custom Logic (CCL)](#configurable-custom-logic-ccl)
* [Analog Comparator (AC)](#analog-comparator-ac)
* [Alternative pins](#alternative-pins)
* [How to install](#how-to-install)
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
* [Minimal setup](#minimal-setup)
* [Getting your hardware working](#getting-your-hardware-working)
  - [Arduino Uno WiFi Rev2](#arduino-uno-wifi-rev2)
  - [Curiosity Nano](#curiosity-nano)
  - [AVR-IOT-WG](#avr-iot-wg)
  - [4809 Xplained Pro](#atmega4809-xplained-pro)


## Supported microcontrollers

|                        | ATmega4809                 | ATmega4808                  | ATmega3209       | ATmega3208                  | ATmega1609       | ATmega1608                  | ATmega809        | ATmega808                   |
|------------------------|----------------------------|-----------------------------|------------------|-----------------------------|------------------|-----------------------------|------------------|-----------------------------|
| **Flash**              | 48 kB                      | 48 kB                       | 32 kB            | 32 kB                       | 16 kB            | 16 kB                       | 8 kB             | 8 kB                        |
| **RAM**                | 6 kB                       | 6 kB                        | 4 kB             | 4 kB                        | 2 kB             | 2 kB                        | 1 kB             | 1 kB                        |
| **EEPROM**             | 256 B                      | 256 B                       | 256 B            | 256 B                       | 256 B            | 256 B                       | 256 B            | 256 B                       |
| **Serial ports**       | 4                          | 3                           | 4                | 3                           | 4                | 3                           | 4                | 3                           |
| **IO pins**            | 40/41*                     | 26/27* <br/> 23†/24††       | 40/41*           | 26/27* <br/> 23†/24††       | 40/41*           | 26/27* <br/> 23†/24††       | 40/41*           | 26/27* <br/> 23†/24††       |
| **Available packages** | TQFP48<br/>QFN48<br/>DIP40 | TQFP32<br/>QFN32<br/>SSOP28 | TQFP48<br/>QFN48 | TQFP32<br/>QFN32<br/>SSOP28 | TQFP48<br/>QFN48 | TQFP32<br/>QFN32<br/>SSOP28 | TQFP48<br/>QFN48 | TQFP32<br/>QFN32<br/>SSOP28 |

<b>*</b> Physical reset pin is disabled  
<b>†</b> SSOP28 package  
<b>††</b> SSOP28 package and reset disabled


## Programming
Programming must be done with a UPDI compatible programmer, such as the [microUPDI](https://github.com/MCUdude/microUPDI), [JTAG2UPDI](https://github.com/ElTangas/jtag2updi) or an official Atmel/Microchip UPDI compatible programmer.

Unlike the Arduino UNO WiFi Rev2 boards package MegaCoreX does not auto detect the programmer you're using. You'll have to select the correct programmer in the *Programmers*. If you're using an Arduino Uno Wifi Rev2 board, a Curiosity Nano or an Xplained Pro board you'll have to choose mEDBG, nEDBG or EDBG.


## Supported clock frequencies
MegaCoreX lets you choose what clock frequency you want to run your microcontroller at.

| Frequency | Oscillator type     | Other                    |
|-----------|---------------------|--------------------------|
| 20 MHz    | Internal oscillator |                          |
| 16 MHz    | Internal oscillator | **Default option**       |
| 8 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 4 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 2 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 1 MHz     | Internal oscillator | Derived from 16 MHz osc. |
| 20 MHz    | External clock      |                          |
| 16 MHz    | External clock      |                          |
| 12 MHz    | External clock      |                          |
| 8 MHz     | External clock      |                          |
| 1 MHz     | External clock      |                          |

Note that unlike other AVRs none of these chips are able to drive an external crystal or resonator. If you need an external oscillator it has to be one with a driven clock output. 
The microcontroller will freeze if the external clock suddenly drops out. If not present on boot, it will automatically choose the 16 MHz internal oscillator instead.


## BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. Below is a table that shows the available BOD options:

| BOD threshold                  |
|--------------------------------|
| 4.2 V                          |
| 4.0 V                          |
| 3.7 V                          |
| 3.3 V                          |
| 2.9 V                          |
| **2.6 V** (default option)     |
| 2.1 V                          |
| 1.8 V                          |
| Disabled                       |


## Reset pin
None of the megaAVR-0 microcontrollers needs the reset line in order to be reprogrammed over the UPDI interface. This means that the reset pin can be used as a GPIO pin instead! There's no need for a high voltage programmer in order to turn that pin into a reset pin again either. If you have a development board you can instead use the reset button as a general purpose button for your project.


## Pinout
This core provides several different Arduino pin mappings based on your current hardware
- **48 pin standard**: This pinout is much closer to the actual hardware than the Uno WiFi pinout. It will not be compatible with shields or anything like that, but it's much more clean and elegant from a hardware point of view. The only pin swap done by default is the PWM output pins. This is done to prevent them from "colliding" with other peripherals. Note that this pinout is only available on ATmega3209/ATmega4809.
- **32 pin standard**: This is the pinout for the 32 pin version of the ATmega3208/4808. Again, it will not be compatible with shields or anything like that, but it's clean and elegant from a hardware point of view. The only pin swap done by default is the PWM output pins. This is done to prevent them from "colliding" with other peripherals.
- **28 pin standard**: This is the pinout for the 28 pin version of the ATmega3208/4808. Will not be compatible with shields or anything like that, but it's still clean and elegant from a hardware point of view. Only pin swap done by default is the PWM output pins. This is done to prevent them from "colliding" with other peripherals.
- **Uno WiFi**: This pinout is 100% compatible with the Arduino Uno WiFi Rev2 hardware. If you have code that's written for the Uno WiFi Rev2 it will work without any modifications if you choose this pinout. Note that this pinout does pin swapping on serial interfaces and PWM pins by default, and some peripherals are renamed to match the original 328P Uno hardware better. Note that this pinout is only available on ATmega3209/ATmega4809.

Please have a look at the pins_arduino.h files for detailed info.<br/> <br/>
<b>Click to enlarge:</b> 

| **MegaCoreX ATmega809/1609/3209/4809 pinout**                                                                                                                                          | **MegaCoreX ATmega808/1608/3208/4808 pinout**                                                                                                                                                                                |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|<img src="https://i.imgur.com/kmP8rQO.png" width="350"><br/><img src="https://i.imgur.com/Uog2AAn.png" width="350"><br/><img src="https://i.imgur.com/ipF1hxT.jpg" width="350">|<img src="https://i.imgur.com/CpqDbIM.png" width="350"><br/><br/><br/><br/><img src="https://i.imgur.com/OC7Y2EP.png" width="350"><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>|


## PWM output
PWM output, `analogWrite()`, is available for the following pins:

| Pinout            | Number of PWM pins | Available PWM pins                 |
|-------------------|--------------------|------------------------------------|
| *28 pin standard* | 4                  | 8, 9, 10, 11                       |
| *32 pin standard* | 6                  | 8, 9, 10, 11, 24, 25               |
| *48 pin standard* | 9                  | 13, 14, 15, 16, 17, 18, 19, 38, 39 |
| *Uno WiFi*        | 6                  | 3, 5, 6, 9, 10, 27                 |

The repeat frequency for the pulses on all PWM outputs can be changed with the new function `analogWriteFrequency(kHz)`, where
`kHz` values of 1 (default), 4, 8, 16, 32 and 64 are supported. Note that these values are very approximate. A best effort within the constraints of the hardware will be made to match the request.

Note also that tone() will use TCB1, so the corresponding PWM output is not available if it is used.


## Configurable Custom Logic (CCL)
The megaAVR-0 microcontrollers are equipped with four independent configurable logic blocks that can be used to improve speed and performence. The CCL pins are marked on all pinout diagrams in a dark blue/grey color. The logic blocks can be used independently from eachother, connected together or generate interrupt for to the CPU. I've made a [light weight, high level library](https://github.com/MCUdude/MegaCoreX/tree/master/megaavr/libraries/Logic) for easy integraion with the CCL hardware.


## Analog Comparator (AC)
The megaAVR-0 microcontrollers are equipped with an analog comparator. It compares the voltage levels on two inputs and gives a digital output based on this comparison. The megAVR chip has four positive AC pins and three negative. There's also a configurable internal voltage reference that can be used on the negative comparator pin instead of an external voltage.  
Try out the [Comparator library](https://github.com/MCUdude/MegaCoreX/tree/master/megaavr/libraries/Comparator) for more information, library reference and examples.


## Alternative pins
The megaAVR-0 microcontrollers support alternative pin assignments for some of its built in peripherals.
This is specified by invoking the `swap()` or `pins()` method before `begin()` for the associated peripheral.
They will return `true` if that swap or pin combination is supported.
For `Serial` peripherals the method is `pins(tx,rx)`, for `Wire` it's `pins(sda,scl)` and for `SPI` it's `pins(mosi,miso,sck,ss)`.
(Note that this is the same pin sequence as used for the ESP8266 `pins` method, but the opposite of the one SoftwareSerial uses.)

Note that `swap()` and `pins()` does the exact same thing, but `swap()` is MUX swap oriented, while `pins()` is pin oriented.

If you want to use this feature to implement communication with two different external devices connected to different pins using one internal peripheral,
mote that the proper way to switch is first to invoke `end()` to cleanly shut down, then `swap()` or `pins()` to switch assigned pins, and finally `begin()` to cleanly start again.

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
| Serial1    | swap(0)  **or**  pins(12,13)   | swap(1)  **or**  pins(14,15)       |                                    |
| Serial2    | swap(0)  **or**  pins(32,35)   | swap(1)  **or**  pins(38,39)       |                                    |
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

| Peripheral | Default                            | Alternative                  |
|------------|------------------------------------|------------------------------|
| Serial     | swap(0)  **or**  pins(27,26)       | swap(1)  **or**  pins(9,10)  |
| Serial1    | swap(0)  **or**  pins(1,0)         | swap(1)  **or**  pins(32,33) |
| Serial2    | swap(0)  **or**  pins(24,23)       | swap(1)  **or**  pins(2,7)   |
| Wire       | swap(0)  **or**  pins(20,21)       |                              |
| SPI        | swap(0)  **or**  pins(32,33,34,10) |                              |

## How to install
#### Boards Manager Installation
*Not yet implemented*

#### Manual Installation
Click on the "Download ZIP" button. Extract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "MightyCoreX" will show up.


## Minimal setup
Here's some simple schematics that shows a minimal setup. The straight 6-pin header may in the future be used for serial uploads without having to use a UPDI programmer. As of today, we're still waiting for a stable version of Optiboot.
<b>Click to enlarge:</b> <br/>

| 48-pin *ATmega809/1609/3209/4809*                     | 40-pin *ATmega4809*                                   | 32-pin *ATmega808/1608/3208/4808*                     |
|-------------------------------------------------------|-------------------------------------------------------|-------------------------------------------------------|
|<img src="https://i.imgur.com/eGkTBQI.png" width="270">|<img src="https://i.imgur.com/QbUxUV7.png" width="270">|<img src="https://i.imgur.com/PfxoYN1.png" width="270">|

## Getting your hardware working
### Arduino Uno WiFi Rev2
[The Arduino Uno WiFi Rev2](https://store.arduino.cc/usa/arduino-uno-wifi-rev2) is the easiest board out of these to get started with, because it's officially supported by Arduino. It uses an ATmega4809, and recommended pinout is *Uno WiFi*. Printing to the serial monitor on your PC is done by initializing `Serial.begin(baud)`. You'll also have to choose **Atmel mEDBG (ATmega32u4)** as your programmer in order to upload code. For more information about this board please see the product page and its schematic.

Click to enlarge:  
<img src="https://i.imgur.com/IXKlx7a.png" width="400">

### Curiosity Nano
[The Curiosity Nano](https://www.microchip.com/developmenttools/ProductDetails/DM320115) uses an ATmega4809 but has a different pinout than the Uno Wifi Rev2. Recommended pinout for this board is *48 pin standard*. Use the `LED_BUILTIN` macro to control the onboard LED. Note that UART3 is connected to the nEDBG chip (often refered to as the debug serial port). This means you'll have to use `Serial3.begin(baud)` in order to print to the serial monitor. You'll also have to choose **Atmel nEDBG (ATSAMD21E18)** as your programmer in order to upload code. For more information about this board please refer to the userguide and its schematic.

Click to enlarge:  
<img src="https://i.imgur.com/Hapb3xX.jpg" width="350">

### AVR-IOT WG
[The AVR-IOT WG](https://www.microchip.com/developmenttools/ProductDetails/AC164160) uses the ATmega4808 in a 32 pin package. *32 pin standard* is the correct pinout for this board. Use the `LED_BUILTIN` macro to control the onboard LED marked with *WIFI*.  Note that UART2 is connected to the nEDBG chip (often refered to as the debug serial port). This means tou'll have to use `Serial2.begin(baud)` in order to print to the serial monitor. You'll also have to choose **Atmel nEDBG (ATSAMD21E18)** as your programmer in order to upload code. For more information about this board please refer to the userguide and its schematic.

Click to enlarge:  
<img src="https://i.imgur.com/oWqoqLC.png" width="350">

### ATmega4809 Xplained Pro
[The ATmega4809 Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/atmega4809-xpro) uses an ATmega4809. Recommended pinout for this board is *48 pin standard*. Note that the UART1 is connected to the EDBG chip (often refered to as the debug serial port). This means you'll have to use `Serial1.begin(baud)` in order to print to the serial monitor. You'll also have to choose **Atmel EDBG (AT32UC3A4256)** as your programmer in order to upload code. For more information about this board please refer to the userguide and its schematic.

Click to enlarge:  
<img src="https://i.imgur.com/ssZs0dC.jpg" width="400">
