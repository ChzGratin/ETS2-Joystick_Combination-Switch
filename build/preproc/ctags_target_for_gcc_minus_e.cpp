# 1 "c:\\Users\\JounghyeonPark\\Documents\\JounghyeonPark\\DEV\\GitHub\\Arduino\\ETS2 Joystick_Combination Switch\\CombinationSwitch.ino"
//Arduino Joystick Library by MHeironimus
//https://github.com/MHeironimus/ArduinoJoystickLibrary
# 4 "c:\\Users\\JounghyeonPark\\Documents\\JounghyeonPark\\DEV\\GitHub\\Arduino\\ETS2 Joystick_Combination Switch\\CombinationSwitch.ino" 2

//========Pin Number & State========
//Light
//[0]: Turn Signal (LEFT)
//[1]: Turn Signal (RIGHT)
//[2]: Tail Light
//[3]: Head Light
//[4]: High Beam
//[5]: Fog Light

//Wiper
//[6]: Front - LOW
//[7]: Front - HIGH
//[8]: Front - Wash
//[9]: Rear - ON
//[10]: Rear - Wash

const int PinCount = 11;
const int arrPinNumber[PinCount] = {2, 3, 4, 5, 6, 7,
                                 8, 9, 10, 11, 12};
const int arrPinMode[PinCount] = {0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
                               0x0, 0x0, 0x0, 0x2, 0x2};
int arrPrevPinState[PinCount];
int arrCurrPinState[PinCount];
//==================================

//========Button Map========
//Only for ETS2
const int ButtonCount = 10;

const int BTN_LeftTurnIndicator = 0;
const int BTN_RightTurnIndicator = 1;
const int BTN_LightModes = 2;
const int BTN_HighBeamHeadlights = 3;
const int BTN_Beacon = 4;
const int BTN_Wipers = 5;
const int BTN_WipersBack = 6;

const int BTN_Unused_FrontWash = 7;
const int BTN_Unused_RearON = 8;
const int BTN_Unused_RearWash = 9;
//==========================

//Joystick Library
Joystick_ Joystick(0x03,0x05,
  ButtonCount, 0, // Button Count, Hat Switch Count
  false, false, false, // X and Y, but no Z Axis
  false, false, false, // No Rx, Ry, or Rz
  false, false, // No rudder or throttle
  false, false, false); // No accelerator, brake, or steering

void setup() {
  // Initialize Pins
  for(int i=0; i<PinCount; i++)
  {
    pinMode(arrPinNumber[i], arrPinMode[i]);
    arrPrevPinState[i] = 0x0;
    arrCurrPinState[i] = 0x0;
  }

  // Initialize Joystick Library
  Joystick.begin();
}

//Turn Signal Movement
//Use i, j as indices.
//i = arrCurrPinState[0] - arrPrevPinState[0] + 1;
//j = arrCurrPinState[1] - arrPrevPinState[1] + 1;
//arrTurnSignalMove[i][j]
const int goLeft = -1;
const int stay = 0;
const int goRight = 1;
const int arrTurnSignalMove[3][3] = {{ stay, goLeft, goRight},
                                     {goRight, stay, goRight},
                                     { goLeft, goLeft, stay}};

//LightModes Step
//Use (i - j + 2) as index.
//i = arrCurrPinState[2]+arrCurrPinState[3];
//j = arrPrevPinState[2]+arrPrevPinState[3];
//BtnPushCnt_LightModes = arrLightModesStep[i - j + 2];
const int arrLightModesStep[5] = {1, 2, 0, 1, 2};

void loop() {
  static int i, j; //temp var

  //button count
  static int BtnPushCnt_LightModes;
  static int BtnPushCnt_Wipers;
  static int BtnPushCnt_WipersBack;

  // Read pin values
  for (i=0; i<PinCount; i++)
  {
    arrPrevPinState[i] = arrCurrPinState[i]; //Record previous pin states
    arrCurrPinState[i] = (digitalRead(arrPinNumber[i]) == 0x1) != (arrPinMode[i] == 0x2); //XOR
  }

  //[4]: High Beam
  //[5]: Fog Light
  //[8]: Front - Wash
  //[9]: Rear - ON
  //[10]: Rear - Wash
  if(arrCurrPinState[4] != arrPrevPinState[4]) { Joystick.pressButton(BTN_HighBeamHeadlights); }
  if(arrCurrPinState[5] != arrPrevPinState[5]) { Joystick.pressButton(BTN_Beacon); }
  if(arrCurrPinState[8] != arrPrevPinState[8]) { Joystick.setButton(BTN_Unused_FrontWash, arrCurrPinState[8]); }
  if(arrCurrPinState[9] != arrPrevPinState[9]) { Joystick.pressButton(BTN_Unused_RearON); }
  if(arrCurrPinState[10] != arrPrevPinState[10]) { Joystick.setButton(BTN_Unused_RearWash, arrCurrPinState[10]); }

  //[0]: Turn Signal (LEFT)
  //[1]: Turn Signal (RIGHT)
  i = arrCurrPinState[0] - arrPrevPinState[0] + 1;
  j = arrCurrPinState[1] - arrPrevPinState[1] + 1;
  switch(arrTurnSignalMove[i][j])
  {
    case goLeft:
    Joystick.pressButton(BTN_LeftTurnIndicator);
    break;
    case goRight:
    Joystick.pressButton(BTN_RightTurnIndicator);
    break;
  }

  //[2]: Tail Light
  //[3]: Head Light
  //{Tail Light, Head Light}
  //Possible States: {0,0} -> {1,0} -> {1,1} -> Repeat
  i = arrCurrPinState[2]+arrCurrPinState[3];
  j = arrPrevPinState[2]+arrPrevPinState[3];
  BtnPushCnt_LightModes = arrLightModesStep[i - j + 2];

  //[6]: Front - LOW
  //[7]: Front - HIGH
  //INT is unused.
  //{LOW, HIGH}
  //Possible States: {0,0} ->-> {1,0} -> {0,1} (BTN_Wipers)
  //                       <-<-       <-       (BTN_WipersBack)
  //(->-> means pressing button twice.)
  i = 2*arrCurrPinState[6] + 3*arrCurrPinState[7];
  j = 2*arrPrevPinState[6] + 3*arrPrevPinState[7];
  BtnPushCnt_Wipers = BtnPushCnt_WipersBack = i - j;
  if(BtnPushCnt_Wipers > 0) { BtnPushCnt_WipersBack = 0; } // ->
  if(BtnPushCnt_WipersBack < 0) { BtnPushCnt_Wipers = 0; } // <-

  while(BtnPushCnt_LightModes > 0 || BtnPushCnt_Wipers > 0 || BtnPushCnt_WipersBack < 0)
  {
    if(BtnPushCnt_LightModes > 0) { Joystick.pressButton(BTN_LightModes); BtnPushCnt_LightModes--;}
    if(BtnPushCnt_Wipers > 0) { Joystick.pressButton(BTN_Wipers); BtnPushCnt_Wipers--; }
    if(BtnPushCnt_WipersBack < 0) { Joystick.pressButton(BTN_WipersBack); BtnPushCnt_WipersBack++; }
    delay(10);

    Joystick.releaseButton(BTN_LightModes);
    Joystick.releaseButton(BTN_Wipers);
    Joystick.releaseButton(BTN_WipersBack);
    delay(10);
  }
  //Wait enough time
  delay(10);

  //Release all gamepad buttons
  for (i=0; i<ButtonCount; i++)
  {
    if(i == BTN_Unused_FrontWash) { continue; }
    if(i == BTN_Unused_RearWash) { continue; }
    Joystick.releaseButton(i); }
}
