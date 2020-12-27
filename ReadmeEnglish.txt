Version 60 of the programs as of 30/11/2020

The first two programs

01 Master Program

02 Slave Program

They're for the Arduino environment

The program called

04 VSC PIO projects

It is for use with the Visual Studio Code program plus the Platform-IO plug-in

In this repository, I will publish the modifications made to the programs to control an ROV, started the programs with the Arduino IDE,
and with two Arduino Mega 2560 boards, but in view of the size and complication of the codes, I am now using Visual Studio Code, with Platfor IO,
and possibly have to change boards for two ESP32, given the problems that arise with the debugging of the codes.
As it rightly puts in the repository title, these programs will evolve and change, as fence progresses in debugging the codes as of the two programs.
The programs right now, compile with the Arduino IDE, but do not operate as well as they should, have some problems,
that is why I put in the title of the programs, "they do not work yet", I hope to be able to solve all the problems shortly.
I will keep you informed of the changes, a greeting to everyone.

The original version taken as a starting point is as follows
_______ ORIGINAL SETTINGS _____________

ROVPS2Control_Slavev8.ino
Hamish Trolove - 30 March 2016
www.techmonkeybusiness.com

Data sent from the master is raw configurations for the ESC control.

This sketch is designed for an Arduino Nano with a single serial port.
I'm using it on a Mega 2560, and it works

Pin assignments are;
D13 - RED LED pin.
D12 - Headlight Control
D11 - Bridge Pin
D8 - ESC Vertical Left
D7 - ESC Vertical Right
D6 - Left Horizontal ESC
D5 - Esc Horizontal Right
D4 - Camera Pitch Servo (overridden in The E-Turn Code1)
D3 - Video trigger (overridden in the EA codeplaza1)
D2 - Photo trigger (overridden in the E-seater code1)
For the transmission of the video advisor1 you will use a Raspberry Pi 3 plus, a USB camera, and the VCL Media Player program

A7 - Connecting the Voltage Divider
A6 - TMP36 temperature sensor output pin (this sensor is changed to obsolete, DHT22 sensors are used)

I2c bus GND pins on MS5803-14BA and BMP180 pins Nano GND Pins Vcc on MS5803-14BA and BMP180 pin sensors Nano 3.3V pins
SDA on MS5803-14BA and BMP180 pin Sensors Nano A4 pins SCL on MS5803-14BA and BMP180 Nano A5 pin sensors
These sensors are changed to obsolete, DHT22 sensors and the MPU6050 gyroscope are used
5V - Supply to temperature sensor TMP36. (This sensor is changed to obsolete, DHT22 sensors are used)
Serial communications connection: modified by Asesorplaza1, on 26/03/2020, to separate the data sent between Arduinos,
from the data to be sent to the Serial Monitor

Serial connection:

Pin 19 Arduino Control (TX) to Pin 18 Arduino ROV (RX)
Pin 18 Arduino Control (RX) to Pin 19 Arduino ROV (TX)
Connect the GND in both

Note that ESC will already have been scheduled at this point in the project.

Internal voltage, heading, depth and internal temperature data are sent through the serial link back to the master
For display on a 16x2 LCD screen.
The 16x2 LCD screen will be replaced by a basic 5" Nextion display

The header is of an HMC5883L digital compass (address i2c 0x1E)
And the depth of an MS5803-14BA high pressure sensor (i2c 0x76 direction)
(This sensor is changed to obsolete, MPU 6050 gyroscope is used)

_____- END OF ORIGINAL CONFIGURATION ___________

Modified by advisorplaza1 on the different dates indicated
The first tests and code changes were initiated in 2,016, due to the number of modifications
As of now 30/01/2020, the dates and changes are put in the project description
To make it easier to find errors in the different code changes

30/01/2020 all camera and LCD control lines have already been discussed
I add 2 DHT22 and so will be the 3 that I need
I've deleted several lines of control from the camera that won't be used

01/02/2020 I add the gyroscope controls provided by Dea de www.cambatronics.com

02/02/2020 I add the order to read only 1 time X second the DHT22, trick by José Luis de
www.cambatronics.com and delete the lines corresponding to the control of the video camera, not used by advisorplaza1,
in this modification of the original Project

04/02/2020 I modify the reading lines of the sensors, because so far I only print in Serial Monitor the text, not the data

06/02/2020 code is debugged a bit, and the code header is modified

08/02/2020 corrects the reading error on the sensors, and corrects the writing of the Serial Monitor

12/02/2020 in order to add any code you have to follow specific programming rules
The structure of the code is modified following these programming orders, according to the information obtained and saved
In the folder 01_UNIR_2_CODIGOS

https://forum.arduino.cc/index.php?topic=242641.0

Several blocks are created in the void loop, for the operation of each of the sensors, eliminating the delay(), and using millis()

13/02/2020 DS18B20 temperature sensor is included, assisted by www.cambatronics.com

16/02/2020 The E18-D80NK infrared distance sensor is added, error-free and I can adapt a code to read the pressure sensor SKU237545

08/03/2020 a relay is connected on pin 12 of the Arduino Slave, to turn on the external light bulbs, you don't need to change the Master's code

26/03/2020 The MPU6050 library is included to control the gyroscope
Fixed sending data, separating data from the Serial Monitor, and data to be sent to the Arduino Maestro, initiating two serial ports with commands

Serial.begin(57600); USB Series Port

Serial1.begin(57600); Serial port on pins 18 and 19

ETin.begin(details(rxdata), &Serial1); Data reception begins via Serial, on pins 18 and 19

ETout.begin(details(txdata), &Serial1); Start sending data through Serial, on pins 18 and 19

28/03/2020 All instructions on the controller are included, to have all operating buttons (not working)

03/04/2020 The new part of the MPU6050 Gyroscope, showing the 3 axes of inclination, plus the temperature of the Gyroscope, is included.
Also included is the second pressure sensor

05/04/2020 changes the code of the E18D80NK infrared sensor, to a better one

11/04/2020 I correct the code according to the instructions of my friend Atilano Belinchón

13/04/2020 Correct readings and send E18D80NK infrared sensor data

15/04/2020 The steering servo is included to operate it with the R1 and R2 buttons on the controller according to information obtained from the page

https://arduparatodos.blogspot.com/2017/02/controlar-servomotor-con-arduino-varios.html

When you press R1, the servo tilts the shaft where the motor tubes are located, and the ROV must surface, when you press R2,
the shaft tilts in the opposite direction and the ROV must go down gaining depth.

18/04/2020 Changed some "if", to "else if", to give agility to the code, following the deA instructions of www.cambatronics.com

Between 24/03/2020 and 28/04/2020, several code changes are made to improve it and make the controller work,
following Bigbadbob's instructions in the forum posts

http://www.homebuiltrovs.com/rovforum/viewtopic.php?f=18&t=1908

From page 4

28/04/2020 Corrects the spelling of all text that are not orders

03/05/2020 Changing the pin assignments of the PS2 controller, according to The Github code, for the Arduino Mega 2560

https://github.com/Lynxmotion/Arduino-PS2X

The new pin assignments are:

3.3V output to PS2 red PIN
Pin 24 to PS2 yellow PIN + 1k resistance
Pin 23 to orange PIN PS2
Pin 25 to brown PIN PS2 + 1k resistance
Pin 22 to PS2 Blue PIN

Fixed the code so that I get into the Master the state of the spotlights, on/off

04/05/2020 The code is debugged according to Bigbadbob's http://www.homebuiltrov.com

05/05/2020 Macro F is included, in all Serial.prints, to reduce dynamic memory consumption
According to Bigbadbob's advice from https://www.homebuiltrov.com, but it gives me trouble

06/05/2020 The code is debugged for better operation, according to Bigbadbob's tips from http://www.homebuiltrov.com and problems with Macro F follow

07/05/2020 The code is debugged for better operation, according to Bigbadbob's tips from http://www.homebuiltrov.com and problems with Macro F follow

08/05/2020 Macro F issues are fixed on all fixed-text Serial.prints
You can't put the Macro F, the Serial.print data from the sensors
And it is possible to reduce the consumption of dynamic memory and space occupied by the program considerably

09/05/2020 Lines continue to be corrected for code debugging, according to Bigbadbob's tips from http://www.homebuiltrov.com
But problems with PS2 command continue

10/05/2020 I notice an error in the order to turn on the spotlights and correct it. But the controller still doesn't work properly.

11/05/2020 Several button control commands are modified, but the controller still does not function properly

13/05/2020 The control of the motors including the ESC.h library of the RC_ESC_master file is modified, from here,
instead of controlling the ESC as a servo, is controlled as what they are ESC.

16/05/2020 Various changes are made, according to Tsanshon's advice from www.foromodelismonaval.es

02/06/2020, Heeding Tsanshon, I install the Atom program plus the Platform-IO plugin, to debug the programs

06/06/2020, I register in the Platfor-IO forum, looking for solutions, and I am told that Atom is no longer supported,
so I have to uninstall this program, and install Visual Estudio Code, with the Platform-IO add-on

07/06/2020, After getting the programs to work in VSC + PIO, it turns out that I can not continue the work,
because the components of VSC + PIO have not been updated, for Arduino, most of the people who use these programs,
also use other boards, which are the ESP32, with many more possibilities than Arduino, I have already bought some boards of those,
and I am waiting for them to reach me, they are cheaper than Arduino boards.

08/06/2020 after many tests and modifications, I get the programs to compile in VSC + PIO, but I can not get much more,
since there is no library specified for the PS2 controller.

09/06/2020 I get to introduce specific libraries with the help of Maxgerhardt de Platforio forum, according to the publications
of the https://community.platformio.org/t/un-rov-de-agua-dulce-a-sweet-water-rov/14157

11/06/2020, After getting the programs to work in VSC + PIO, it turns out that I can not continue the work,
because the components of VSC + PIO have not been updated, for Arduino, most of the people who use these programs, also use other boards,
which are the ESP32, with many more possibilities than Arduino, I have already bought some boards of those, and I am waiting for them to reach me,
they are cheaper than Arduino boards.

18/07/2020 translate the readme file into English

Between 25/08/2020 and 30/11/2020, several program improvements are made to try to get the controller working properly,
getting it to improve something, but it still doesn't work as fine as it should.
Functions are also implemented
loop_mandoPS2()
{
Work orders
}
In the slave void loop(), to achieve a cleaner and more correct sensor working structure, greatly improving the results of sensor work.

The controller still does not work properly, I am doing a separate program only with the functions of the controller to see if I can make
it work properly and then study how it is implemented in the general code of the ROV.

27/12/2020 Fixed the definition of the millis function, was created by means of
Int intervalDimensions();
Int auxMillis();
The program towards weird things, because the right definition is
Unsigned long intervalDimensions();
Unsigned long auxMillis();
Here he explains it better
https://www.luisllamas.es/multitarea-en-arduino-blink-sin-delay/





The software is provided "as is", without any warranty either express or implied, including commercial warranties.
For private use only NEVER commercial. Under no circumstances is the author responsible for any damages arising from the use of the program.

