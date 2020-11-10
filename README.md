# VUW_PID_BalanceBeam
Adapted from the [ElectroNoobs Tutorial](https://electronoobs.io/tutorial/11#)

## Notes
- Pin 9 (digital) connects to the Servo Control Line
- The Servo needs a 5V supply that can supply at least 1A, the grounds of the Arduino and the Servo PSU need to be connected so that it's all on the ame reference.
- Pin A0 is the IR distance Sensor Output.
- The IR Sensor can be powered off of the Arduino
- This is a platformio project, however, you can upload this with the Arduino IDE by removing the include for the Arduino.h Library and copying the code to a .ino file


[Modified 3D Files](https://cad.onshape.com/documents/e4b49ecee3bc079e29df194a/w/7da06fe0d6db1b56125684e6/e/53c5f5ab1010ae0403f38be8)
