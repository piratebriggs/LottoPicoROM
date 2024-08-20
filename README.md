# My Fork of the PicoROM project



## Hardware
The PicoROM is based around the Raspberry Pi [RP2040](https://www.raspberrypi.com/products/rp2040/) microcontroller on a custom PCB.

It has access to all 29 PIO pins and has the following pin mapping:
|pins|func|
|-|-|
|0-17|Addr|
|18|LED|
|19|Buf OE|
|20|OE|
|21|CE|
|22-29|Data|

I'm futzing around with a Pi Pico on a breakboard which only has access to 26 PIO pins plus I've got slightly different design goals:
- The RP2040 should provide 4k of boot rom on reset. This should be enough to load a larger OS (CP/M etc.) from a CH376
- After boot, the RP2040 ROM should not be present on the Z80 bus and instead passthrough the CE signal to a SRAM chip that is wired in parallel.

My Pinout is something like:

|pins|func|
|-|-|
|0-9|Addr (Only need 0-8)|
|10-17|Data|
|18-21|Bank Sel|
|22|IO_WR_|
|25|LED|
|26|OE_ (RD_)|              
|27|CE_ (MEMREQ_)|
|28|ROM EN (Active High)|


*Note: OE, CE & ROM EN must be on contiguous pins*

## Firmware
The firmware is written in C/C++ using the [Pico C SDK](https://www.raspberrypi.com/documentation/pico-sdk/). The firmware is responsible for the ROM emulation, managing communication with the host PC and facilitating communication between the host PC and the target device.

The RP2040 has 264KByte of static RAM and 256KBytes of that are used to store the ROM data. The external flash is not fast enough for these purposes. It is used for store the firmware itself, config settings and a copy of the ROM image that gets loaded at startup. The ROM emulation itself is achieved using a combination core1 and the PIO state machines. A small assembly loop running on core1 interprets the address lines, reads the data from memory and presents it on the data pins. Core1 is given high priority bus access, so it can always read and write in a single cycle. The PIO is used to interpret the chip and output enable signals.

The `firmware/` directory contains the firmware source code.

## Host Software
Software on a host PC is used to upload ROM data to the PicoROM. The `picorom` command line tool has the ability to list the PicoROMs currently connected, give them unique names and upload new data to them. It is common for data to be split across multiple ROMs, especially in 16-bit systems. So giving a PicoROM names like `cpu_high` or `sprite1` allows you to have multiple PicoROMs connected at once without any confusion about where you are sending the data.

There is also a Python module called `pypicorom` which provides all the same functionality as the command line tool. It also supports `read` and `write` methods for communicating with the software that is accessing the ROM data.

The host PC software is written in Rust and is in the `host/` directory.

## Two-way communication
I personally find it useful to build test software that supports some kind of command system for doing things on the system I am experimenting with. This allows me to write scripts in a high level language, like python, that can read/write memory, trigger other hardware on the system, etc.

To support this the firmware allows a specified region of ROM memory to be used to both send and receive a byte stream to/from the host PC. The software on the target system can read from a known address to get the latest byte from the host, and it can *read* from one of 256 other addresses to send a byte to the host PC. Through this system about 5Kbytes/sec can be sent and received.

