
# LED example for AVR microcontrollers

brew tap osx-cross/avr
brew install avr-gcc

brew install avrdude

cd build
cmake ../ -DPORT=/dev/cu.usbmodem14201