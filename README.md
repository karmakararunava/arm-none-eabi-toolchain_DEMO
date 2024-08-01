# Simple project to demonstrate the usage of arm-none-eabi toolchain to produce a binary for TM4C129ENCPDT microcontroller.

### Tools used:
    1. arm-none-eabi-gcc         | compiler
    2. arm-none-eabi-as          | assembler
    3. arm-none-eabi-ld          | linker
    4. arm-none-eabi-objcopy     | copy and translate the elf file to binary 
    5. UniFlash                 | used to flash the binary to the microcontroller

### Program:
    Control the D3 and D4 led with USR-SW1 and USR_SW2. D3 glows when USR_SW1 is pressed and D4 glows when USR_SW2 is pressed.

### Board connections:
    - D3       ---> PF4
    - D4       ---> PF0
    - USR-SW1  ---> PJ0
    - USR-SW2  ---> PJ1

Note: pull-up resistor - if button is released, signal is high and low if pressed
