
#include "HardwareConfig.h"
#include <Arduino.h>

void ConfigPins() {
  // USB interface configuratio
  pinMode(RTS1nPIN, INPUT);
  pinMode(RTS2nPIN, INPUT);
  pinMode(RTS3nPIN, INPUT);
  pinMode(RTS4nPIN, INPUT);

  pinMode(CTS2nPIN, OUTPUT);
  pinMode(CTS3nPIN, OUTPUT);
  pinMode(CTS4nPIN, OUTPUT);

  // RJ34 radio interface jack signals
  pinMode(KEY1nPIN,   INPUT_PULLUP); 
  pinMode(KEY2nPIN,   INPUT_PULLUP); 
  pinMode(KEY3nPIN,   INPUT_PULLUP); 
  pinMode(KEY4nPIN,   INPUT_PULLUP); 

  pinMode(PTT1PIN,    OUTPUT);
  pinMode(PTT2PIN,    OUTPUT);
  pinMode(PTT3PIN,    OUTPUT);
  pinMode(PTT4PIN,    OUTPUT);

  //pinMode(SPR1PIN,    INPUT_PULLUP);
  //pinMode(SPR2PIN,    INPUT_PULLUP);
  //pinMode(SPR3PIN,    INPUT_PULLUP);
  //pinMode(SPR4PIN,    INPUT_PULLUP);

  // RJ45 radio interface jack LEDs
  pinMode(RIGGRN1PIN,  OUTPUT);
  pinMode(RIGGRN2PIN,  OUTPUT);
  pinMode(RIGGRN3PIN,  OUTPUT);
  pinMode(RIGGRN4PIN,  OUTPUT);
 
  pinMode(RIGYEL1PIN, OUTPUT);
  pinMode(RIGYEL2PIN, OUTPUT);
  pinMode(RIGYEL3PIN, OUTPUT);
  pinMode(RIGYEL4PIN, OUTPUT);

  // RJ45 relay interface jack signals
  pinMode(RLY1PIN, OUTPUT);
  pinMode(RLY2PIN, OUTPUT);
  pinMode(RLY3PIN, OUTPUT);
  pinMode(RLY4PIN, OUTPUT);

  // RJ45 relay interface jack LEDs 
  pinMode(RLYGRNPIN, OUTPUT);
  pinMode(RLYYELPIN, OUTPUT);
}
