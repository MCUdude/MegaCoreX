# PlatformIO

[PlatformIO](https://platformio.org) is an open source ecosystem for embedded development. 
It has a built-in library manager and is Arduino compatible. It supports most operating systems; Windows, MacOS, Linux 32 and 64-bit, ARM and X86. And best of all, MegaCoreX is supported!

* [What is PlatformIO?](http://docs.platformio.org/en/latest/what-is-platformio.html)
* [PlatformIO IDE](https://platformio.org/platformio-ide)
* Getting started with [PlatformIO IDE](https://docs.platformio.org/en/latest/integration/ide/visualstudio.html) or [PlatformIO command line interface](https://docs.platformio.org/en/latest/core/index.html)
* [Advanced functionality](https://docs.platformio.org/en/latest/platforms/atmelmegaavr.html) 
* [Project Examples](https://docs.platformio.org/en/latest/platforms/atmelmegaavr.html#examples)


## MegaCoreX + PlatformIO 
MegaCoreX and PlatformIO goes great together. You can do serial uploads and upload using a dedicated UPDI programmer, but you can also let PlatformIO calulate the fuses and load the correct bootloader file, just like Arduino IDE does!

PlatformIO uses the information provided in platformio.ini to calculate what fuse bits and what bootloader file to load.  
Simply provide enough information and run the following commands:  

```ini
; Only set fuses
pio run -t fuses -e fuses_bootloader
; Set fuses and burn bootloader
pio run -t bootloader -e fuses_bootloader
; (where "fuses_bootloader" can be replace with a different environment to match your build configuration)
```

You can find a platformio.ini template you can use when creating a project for a MegaCoreX compatible device below.  
The most common functionality is available in this template. As you can see, the templated is divided into multiple environments.  

* The default build environment are defined under *[platformio]*.
* All parameters that are common for all environments are defined under *[env]*.
* Use the *[env:Upload_UPDI]* or *[env:Upload_UART]* to upload to your target.
* Use *[env:fuses_bootloader]* to set the fuses or burn the bootloader.

More information on what each line means can be found futher down on this page.


## platformio.ini template

```ini
; PlatformIO template configuration file for MegaCoreX
; https://github.com/MCUdude/MegaCoreX/
;
;   Build options: build flags, source filter
;   Hardware options: oscillator type, BOD, UART number, EEPROM retain
;   Upload options: custom upload port, speed, and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options
; https://github.com/MCUdude/MegaCoreX/blob/master/PlatformIO.md
; https://docs.platformio.org/page/projectconf.html
; https://docs.platformio.org/en/latest/platforms/atmelmegaavr.html

[platformio]
; Default build target
default_envs = Upload_UPDI

; Parameters used for all environments
[env]
platform = atmelmegaavr
framework = arduino

; Chip in use
board = ATmega4809
; Clock frequency in [Hz]
board_build.f_cpu = 16000000L
; Oscillator type (internal or external)
board_hardware.oscillator = internal
; Arduino pinout variant
board_build.variant = 48pin-standard

; Unflag build flags
build_unflags =
; Extra build flags 
build_flags =

; Monitor port is auto detected. Override here
;monitor_port = 
; Serial monitor baud rate
monitor_speed = 9600


; Run the following command to upload with this environment
; pio run -e Upload_UPDI -t upload
[env:Upload_UPDI]
; Upload protocol for UPDI upload
upload_protocol = xplainedmini_updi
upload_flags =


; Run the following command to upload with this environment
; pio run -e Upload_UART -t upload
[env:Upload_UART]
; Upload protocol for serial uploads (using Optiboot)
upload_protocol = arduino
upload_flags =
upload_port = /dev/cu.usbserial*


; run the following command to set fuses
; pio run -e fuses_bootloader -t fuses
; run the following command to set fuses + burn bootloader
; pio run -e fuses_bootloader -t bootloader
[env:fuses_bootloader]
; Upload protocol for used to set fuses/bootloader
upload_protocol = ${env:Upload_UPDI.upload_protocol}
upload_flags =
; Hardware settings
board_hardware.bod = 2.7v
board_hardware.eesave = yes
board_hardware.uart = no_bootloader
board_hardware.rstpin = reset

```


### `board`
PlatformIO requires the `board` parameter to be present.
The table below shows what board name should be used for each target
| Board name    |
|---------------|
| `ATmega4809`  |
| `ATmega4808`  |
| `ATmega3209`  |
| `ATmega3208`  |
| `ATmega1609`  |
| `ATmega1608`  |
| `ATmega809`   |
| `ATmega808`   |


### `board_build.f_cpu`
Specifies the clock frequency in [Hz]. 
Used to determine what oscillator option to choose. A capital *L* has to be added to the end of the frequency number.
Below is a table with supported clocks for MegaCoreX. Defaults to 16 MHz internal if not specified.

| Clock speed | Oscillator | board_build.f_cpu     |
|-------------|------------|-----------------------|
| 20 MHz      | Internal   | `20000000L`           |
| 16 MHz      | Internal   | `16000000L` (default) |
| 10 MHz      | Internal   | `10000000L`           |
| 8 MHz       | Internal   | `8000000L`            |
| 5 MHz       | Internal   | `5000000L`            |
| 4 MHz       | Internal   | `4000000L`            |
| 2 MHz       | Internal   | `2000000L`            |
| 1 MHz       | Internal   | `1000000L`            |
| 16 MHz      | External   | `16000000L`           |
| 12 MHz      | External   | `12000000L`           |
| 8 MHz       | External   | `8000000L`            |
| 4 MHz       | External   | `4000000L`            |
| 1 MHz       | External   | `1000000L`            |


### `board_hardware.oscillator`
Spefices to use the internal or an external oscillator.  

| Oscillator option    |
|----------------------|
| `internal` (default) |
| `external`           |


### `board_hardware.uart`
Specifies the hardware UART port used for serial upload. Use `no_bootloader` if you’re using a dedicated UPDI programmer, i.e not using a bootloader for serial upload.

| Upload serial port option | Description                                    |
|---------------------------|------------------------------------------------|
| `no_bootloader` (default) |                                                |
| `uart0` / `uart0_def`     | Use UART0 default pins                         |
| `uart0_alt`               | Use UART0 alternative pins                     |
| `uart1` / `uart1_def`     | Use UART1 default pins                         |
| `uart1_alt`               | Use UART1 alternative pins                     |
| `uart2` / `uart2_def`     | Use UART2 default pins                         |
| `uart2_alt`               | Use UART2 alternative pins                     |
| `uart3` / `uart3_def`     | Use UART3 default pins (48-pin parts only)     |
| `uart3_alt`               | Use UART3 alternative pins (48-pin parts only) |

### `board_hardware.bod`
Specifies the hardware brown-out detection. Use `disabled` to disable.

| BOD              |
|------------------|
| `4.3v`           |
| `2.6v` (default) |
| `1.8v`           |
| `disabled`       |


### `board_hardware.eesave`
Specifies if the EEPROM memory should be retained when uploading using a programmer. Use `no` to disable.

| EEPROM retain   |
|-----------------|
| `yes` (default) |
| `no`            |


### `board_hardware.rstpin`
Specifies what functionality the reset pin should have. Note that the option `reset` _will_ be selected regardless if you're using a bootloader.

| Reset pin functionality   |
|---------------------------|
| `reset` (default)         |
| `gpio`                    |


### `board_build.variant`
Holds the current pinout in use.  
See [pinout pics](https://github.com/MCUdude/MegaCoreX#pinout) for more info.

| Pinouts 48 pin parts      | Pinouts 40 pin parts              | Pinouts 32 pin parts      | Pinouts 28 pin parts      |
|---------------------------|-----------------------------------|---------------------------|---------------------------|
| `48pin-default` (default) | `40pin-default` (must be defined) | `32pin-default` (default) | `28pin-default` (default) |
| `nano-every`              |                                   |                           |                           |
| `uno-wifi`                |                                   |                           |                           |


### `build_unflags`
This parameter is used to unflag flags automatically set by the PlatformIO build environment.

**Example:**
`build_unflags =-flto -fpermissive`


### `build_flags`
This parameter is used to set compiler flags. This is useful if you want to for instance want to chage the serial RX or TX buffer. Here's a list of the current available core files flags:

| Flag                        | Default size | Description                                               |
|-----------------------------|--------------|-----------------------------------------------------------|
| -lprintf_flt                |              | Lets you print floats with printf (occupies ~1.5 kB)      |
| -Wall -Wextra               |              | Show on all compiler warnings                             |
| -DSERIAL_RX_BUFFER_SIZE=128 | 64 bytes     | Sets the serial RX buffer to 128 bytes                    |
| -DSERIAL_TX_BUFFER_SIZE=128 | 64 bytes     | Sets the serial TX buffer to 128 bytes                    |
| -DTWI_BUFFER_SIZE=64        | 32 bytes     | Sets the TWI (i2c) buffer to 64 bytes                     |
| -DTWI1_BUFFER_SIZE=64       | 32 bytes     | Sets the TWI1 (i2c) buffer to 64 bytes (ATmega324PB only) |

**Example:**
`build_flags = -DSERIAL_RX_BUFFER_SIZE=128 -DSERIAL_TX_BUFFER_SIZE=128`


### `upload_port`
Holds the serial port used for uploading. Only needed if you're uploading using a JTAG2UPDI programmer or with a USB to serial adapter using the Optiboot bootloader. PlatformIO automatically detects the serial port. However, if you want to override this you can uncomment `upload_port`. Use `/dev/[port]` on Unix compatible systems, and use `COMx` on Windows.


### `upload_protocol`
Programmer used for uploading.

| Supported UPDI programmers in Avrdude | Notes                                                                                                            |
|---------------------------------------|------------------------------------------------------------------------------------------------------------------|
| `jtag2updi`                           | Requires upload port                                                                                             |
| `arduino`                             | Used when uploading using the Optiboot bootloader. Requires upload port                                          |
| `xplainedmini_updi`                   | Xplained Mini (mEDBG) and [microUPDI](https://www.tindie.com/products/MCUdude/microupdi-programmer/) programmers |
| `pkobn_updi`                          | On-board Curiosity nano programmer (nEDBG)                                                                       |
| `pickit4_updi`                        | PICkit4 programmer in UPDI mode                                                                                  |
| `snap_updi`                           | MPLAB SNAP programmer in UPDI mode                                                                               |
| `atmelice_updi`                       | Atmel ICE programmer in UPDI mode                                                                                |
| `xplainedpro_updi`                    | Xplained Pro in UPDI mode                                                                                        |
| `powerdebugger_updi`                  | Power Debugger in UPDI mode                                                                                      |


### `upload_flags`
Used to pass extra flags to Avrdude when uploading using a programmer.  
Typical parameters are `-PUSB` and `-v`.  
**Note that every flag has to be on its own line, and they have to be indented with two spaces:**
```ini
upload_flags = 
  -PUSB
  -v
```


### `monitor_port`
PlatformIO detects serial ports automatically. However, if you want to override this you can uncomment `monitor_port`. Use `/dev/[port]` on Unix compatible systems, and use `COMx` on Windows.


### `monitor_speed`
Sets the serial monitor baud rate. Defaults to 9600 if not defined.


## pyupdi
[pyupdi](https://github.com/mraardvark/pyupdi) is a Python-based tool for programming tinyAVR and megaAVR devices with UPDI interface via a standard serial port. It can be installed directly in the PlatformIO virtual environment using the following command:

```
pip install https://github.com/mraardvark/pyupdi/archive/master.zip
```

Once pyupdi is installed it can be used as the uploader via a custom upload_command option:

```ini
[env:pyupdi_upload]
upload_protocol = custom
upload_speed = 115200
upload_port = /some/serial/port
upload_flags =
  -d
  $BOARD_MCU
  -c
  $UPLOAD_PORT
  -b
  $UPLOAD_SPEED
upload_command = pyupdi $UPLOAD_FLAGS -f $SOURCE
```
