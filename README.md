# Arduino-Bluetooth-Tank
Arduino handmade wooden tank controlled via bluetooth

The tank can drive straight, left, right, and reverse.
The turret can turn left and right while the barrel can angle up and down as well as "shoot" which makes a noise and lights an LED within the barrel. 
Headlights automatically turn on during low light levels and red taillights remain on always. 

A 9 volt battery powers the arduino while a 12 volt battery powers the main metal geared driving servos to ensure maximum performance. An HC-06 bluetooth module is used in order to connect via bluetooth to the phone or other bluetooth devices. This works in tandem with the app "USBRControl". An Arduino UNO is used as the primary board and the library <Servo.h> is used. 

The 5 pound wooden tank is based off of the US M4A3E2 "Jumbo" Sherman tank. 
