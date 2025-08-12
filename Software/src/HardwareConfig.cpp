
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

  // RJ45 radio interface jack signals
  // KEY is low true, MCU internal pullup, protected with 3,6V zener
  pinMode(KEY1nPIN,  INPUT_PULLUP); 
  pinMode(KEY2nPIN,  INPUT_PULLUP); 
  pinMode(KEY3nPIN,  INPUT_PULLUP); 
  pinMode(KEY4nPIN,  INPUT_PULLUP); 

  pinMode(PTT1PIN,   OUTPUT);
  pinMode(PTT2PIN,   OUTPUT);
  pinMode(PTT3PIN,   OUTPUT);
  pinMode(PTT4PIN,   OUTPUT);

  // SPR is undefined, MCU internal pullup, no protection
  pinMode(SPR1PIN,   INPUT_PULLUP);
  pinMode(SPR2PIN,   INPUT_PULLUP);
  pinMode(SPR3PIN,   INPUT_PULLUP);
  pinMode(SPR4PIN,   INPUT_PULLUP);

  // RJ45 radio interface jack LEDs
  // LEDs are high true
  pinMode(RIG1GRNPIN, OUTPUT); // Rig Green, transmitting
  pinMode(RIG2GRNPIN, OUTPUT);
  pinMode(RIG3GRNPIN, OUTPUT);
  pinMode(RIG4GRNPIN, OUTPUT);
 
  pinMode(RIG1YELPIN, OUTPUT); // RIG Yellow, inhibited
  pinMode(RIG2YELPIN, OUTPUT);
  pinMode(RIG3YELPIN, OUTPUT);
  pinMode(RIG4YELPIN, OUTPUT);

  // RJ45 relay interface jack LEDs 
  pinMode(RLYGRNPIN,  OUTPUT); // Green, something transmitting
  pinMode(RLYYELPIN,  OUTPUT); // RIGYELlow, something inhibited

  // RJ45 relay interface jack signals
  // RLY are high true, buffered with BTS5200 relay driver
  pinMode(RLY1PIN,   OUTPUT);
  pinMode(RLY2PIN,   OUTPUT);
  pinMode(RLY3PIN,   OUTPUT);
  pinMode(RLY4PIN,   OUTPUT);

  // BTS5200 relay driver
  pinMode(DSEL0PIN,  OUTPUT);
  pinMode(DSEL1PIN,  OUTPUT);
  pinMode(DENPIN,    OUTPUT);
  pinMode(ISPIN,     INPUT);
}