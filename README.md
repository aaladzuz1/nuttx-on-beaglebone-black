# Apache NuttX RTOS on BeagleBone Black (WSL/Ubuntu) + Custom Apps

Seminar project for “Software Development for Embedded Systems” (University of Sarajevo, Sept 2024): implementing and running Apache NuttX (RTOS) on the BeagleBone Black platform, and creating custom NuttX applications.

## What this project covers
- Installing and building NuttX in a Linux environment using WSL + Ubuntu.
- Configuring NuttX for BeagleBone Black (`beaglebone-black/nsh`) and compiling `nuttx.bin`.
- Booting NuttX on BeagleBone Black from a FAT32 SD card.
- Serial communication and boot flow using a USB-to-TTL adapter + PuTTY, interrupting U-Boot and loading `nuttx.bin`.
- Building custom user-space NuttX apps:
  - `CustomHello` (prints “Hello, Custom World!!”)
  - `CustomCounter` (two POSIX-thread tasks: one increments a shared counter every 3s, the other prints it every 7s, protected with a mutex + SIGINT handler).

## Hardware / Platform
- BeagleBone Black (ARM Cortex-A8 / AM335x) development board.

## Build steps (summary)
1. Set up WSL (Ubuntu) and install build dependencies (build-essential, kconfig tools, ARM toolchain, etc.).
2. Clone repositories:
   - `apache/nuttx` (kernel/core)
   - `apache/nuttx-apps` (user-space apps)
3. Configure + build:
   - `./tools/configure.sh beaglebone-black/nsh`
   - `make`
4. Copy `nuttx.bin` to a FAT32-formatted SD card (root directory).

## Booting NuttX on BeagleBone Black (summary)
- Connect a USB-to-TTL serial adapter (RX↔TX, TX↔RX, GND↔GND), open PuTTY at 115200 baud, interrupt U-Boot, then load and run:
  - `load mmc 0 0x8a000000 nuttx.bin`
  - `go 0x8a000000`

## Repository structure
- `apps/` – custom NuttX app (`CustomCounter`)
- `docs/` – seminar PDF/report
