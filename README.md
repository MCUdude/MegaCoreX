# MegaCoreX (and TinyCoreX)?

An Arduino core for the new megaAVR series!
ATmega3208, ATmega4808, ATmega3209 and ATmega4809.


# Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Programming](#programming)
* [Supported clock frequencies](#supported-clock-frequencies)
* [BOD option](#bod-option)


## Supported microcontrollers
* ATmega4809
* ATmega4808
* ATmega3209
* ATmega3208

Can't decide what microcontroller to choose? Have a look at the specification table below:

|                        | ATmega4809       | ATmega4808                  | ATmega3209       | ATmega3208                  |
|------------------------|------------------|-----------------------------|------------------|-----------------------------|
| **Flash**              | 48 kB            | 48 kB                       | 32 kB            | 32 kB                       |
| **RAM**                | 6 kB             | 6 kB                        | 4 kB             | 4 kB                        |
| **EEPROM**             | 256 B            | 256 B                       | 256 B            | 256 B                       |
| **Serial ports**       | 4                | 3                           | 4                | 3                           |
| **IO pins**            | 40/41*           | 26/27* <br/> 23†/24††       | 40/41*           | 26/27* <br/> 23†/24††       |
| **Available packages** | TQFP48<br/>QFN48 | TQFP32<br/>QFN32<br/>SSOP28 | TQFP48<br/>QFN48 | TQFP32<br/>QFN32<br/>SSOP28 |

<b>*</b> Physical reset pin is disabled  
<b>†</b> SSOP28 package  
<b>††</b> SSOP28 package and reset disabled


## Programming
Programming must be done with a UPDI compatible programmer, such as the JTAGICE 3 or any of the new EDBG chips that can be found on newer AVR explained and curoisity boards.


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

Note that unlike other AVRs none of these chips are able to drive an external crystal or resonator. If you need an external oscillator it has to be one with a driven clock output.


## BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. Below is a table that shows the available BOD options:

|                                |
|--------------------------------|
| 4.2 V                          |
| 4.0 V                          |
| 3.7 V                          |
| 3.3 V                          |
| 2.9 V                          |
| **2.6 V** (default option)     |
| 2.1 V                          |
| 1.8 V                          |
