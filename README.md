
# Blink LED on ATMega328P

An implementation of the Arduino's Blink example using raw C AVR programming without any extra libraries and Arduino IDE.

![avr-led](https://github.com/frolovilya/avr-led/assets/271293/1bc8b3fa-d4a5-445d-996e-ee60f5a0bbb8)

An equivalent of the following code:

```c
void setup() 
{
    pinMode(13, OUTPUT);
}

void loop() 
{
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
```

## Install Requried Tools

```sh
brew install cmake

brew tap osx-cross/avr
brew install avr-gcc

brew install avrdude
```

## Build & Deploy

The project is using CMake to perform all build and deployment activities. By default it's configured to use another Arduino as ISP for flashing.

```sh
mkdir build
cd build

# the following arguments are default 
# and could be omitted, if they match your environment
cmake ../ -DMCU=atmega328p \
    -DPORT=/dev/cu.usbmodem14201 \
    -DPROGRAMMER=stk500v1 \
    -DBAUD_RATE=19200

# build a .hex
make

# install programm
make flash
```

## Change Oscillator Settings
You may want to use a built-in Internal 8MHz Oscillator to use MCU off Arduino board. Also `delay()` function calculations are based on the internal oscillator values.

```sh
cd build

# change fuse bits to use an Internal 8MHz Oscillator without pre-scaling
make use-internal-oscillator
```
