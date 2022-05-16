
## Arduinative : A native Arduino core to use your PC as an Arduino Board
An Arduino core to add PC Environment Support in Arduino IDE. This core enables you to build and run Arduino sketches in Native Environment from Arduino IDE. This core was built to compile and run unit tests for arduino in Linux environment. 

## Features

- [x] Compile & Run Arduino Sketches in PC
- [x] Supports millis()
- [x] Supports TinyGSM library over USB-FTDI
- [x] Use FTDI as Arduino Serial Interface
- [ ] Implement LibMPSSE-I2C to use FTDI as I2C device
- [ ] Use flow control to use DTR/RTS as GPIO

## Dependencies
C++ Boost library is required to use FTDI as Serial. Use the following command to install Boost library.
```bash
sudo apt-get update
sudo apt-get install libboost-all-dev
```

## Install Arduinative
Download the repository from <a href="https://github.com/shadlyd15/Arduinative/archive/master.zip"> here </a> or clone using the command below
```bash
git clone https://github.com/shadlyd15/Arduinative.git
```
Now, just simply create a folder named "hardware" in your arduino sketchbook folder. Copy the Arduino directory here.

Now select Arduinative from **Tools > Board > Arduinative**
Select FTDI serial port if you want to use Serial.
