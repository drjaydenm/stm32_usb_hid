# stm32_usb_hid

An attempt at a basic HID keyboard using STM32 micro's

## Setup

### Install the GNU Toolchain for ARM Embedded Processors

The toolchain is required to compile for the STM32 target platform

#### MacOS

``` {.bash}
brew tap osx-cross/arm

brew install arm-gcc-bin

brew install stlink
```

## Building

Run the build

``` {.bash}
make
```

Flash to device

``` {.bash}
make flash
```

Inspect memory layout of image

``` {.bash}
arm-none-eabi-nm main.elf
```

## Debugging

Using GDB - ensure `st-util` is running

``` {.bash}
arm-none-eabi-gdb main.elf

target extended-remote :4242

load

continue

Ctrl^C

info registers

stepi

info registers

quit
```
