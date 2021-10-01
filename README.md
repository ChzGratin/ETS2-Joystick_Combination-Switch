# ETS2-Joystick_Combination-Switch
README.md

***

## About
Joystick made of REAL combination switch (lights, wipers)   
Only for ETS2 (Euro Truck Simulator 2)   
Supported Boards: Arduino (Leonardo, Micro)   
   
I used Arduino Joystick Library by MHeironimus. (https://github.com/MHeironimus/ArduinoJoystickLibrary)

***

## Features
An arduino with a real combination switch will work as an almost perfect joystick.
* Turn Signal (LEFT and RIGHT)
* Tail/Head Light
* High Beam
* Fog Light
* Front Wiper (MIST, LOW, HIGH, Wash)
* Rear Wiper (ON, Wash)
   
**Demonstration Video**

[demo vid](https://user-images.githubusercontent.com/70784055/135658332-4d2de169-8913-4880-8d0b-93ab14ea40c6.mp4)

***

## Combination Switch Spec.
All New Morning (2015) + Automatic Headlights   
I used technical information web site of KIA. (https://gsw.kia.com/kmc/login.tiles, 전장회로도->승용->모닝(TA)->2015)   
NOTE) For other combination switches, please refer to the respective product documentations.

***

## Circuit Diagram
### Terminals of Combination Switch
Lights   
* Turn Signal (LEFT)
* Turn Signal (RIGHT)
* Turn Signal Power
* Tail Light
* Head Light
* Tail/Head Light Power
* High Beam
* High Beam Power
* Fog Light x2

Wipers
* PCB Power
* PCB GND
* Front - LOW
* Front - HIGH
* Front - Wash
* Rear - ON
* Rear - Wash
* Rear Power

### Arduino
<img src="img/Circuit Diagram.png" alt="Circuit Diagram"></img>

***

## ETS2 Control Setting (Recommended)
|Function|Primary|Secondary|How to Assign|
|---|---|---|---|
|Start/Stop Engine|Insert|Joy Button 9|Rear Wiper Wash|
|Start/Stop Engine Electricity|Delete|Joy Button 8|Rear Wiper ON|
|Left-Turn Indicator|Q|Joy Button 0|Turn Signal (LEFT)|
|Right-Turn Indicator|E|Joy Button 1|Turn Signal (RIGHT)|
|Hazard Warning|F|Joy Button 7|Front Wiper Wash|
|Lights Modes|L|Joy Button 2|Tail/Head Light|
|High Beam Headlights|K|Joy Button 3|High Beam|
|Beacon|O|Joy Button 4|Fog Light|
|Wipers|]|Joy Button 5|Increase Front Wiper Speed|
|Wipers Back|[|Joy Button 6|Decrease Front Wiper Speed|

***

## Caution!!
The Arduino does ***NOT*** communicate with ETS2.   
So, when you start driving, the ***REAL*** combination switch ***SHOULD*** be matched with ***IN-GAME*** one.
