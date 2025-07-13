
#include "HardwareConfig.h"
#include <Arduino.h>

void InitPins() {
  // USB interface configuration
  pinMode(RTS1nPIN, INPUT_PULLUP);
  pinMode(CTS1nPIN, OUTPUT);
  pinMode(RTS1nPIN, INPUT_PULLUP);
  pinMode(CTS2nPIN, OUTPUT);
  pinMode(RTS3nPIN, INPUT_PULLUP);
  pinMode(CTS3nPIN, OUTPUT);
  pinMode(RTS4nPIN, INPUT_PULLUP);
  pinMode(CTS4nPIN, OUTPUT);

  // Radio interface configuration
  pinMode(PTT1PIN,    OUTPUT);
  pinMode(KEY1nPIN,   INPUT_PULLUP); 
  //pinMode(SPR1PIN,    INPUT_PULLUP);
  pinMode(TX1LEDPIN,  OUTPUT);
  pinMode(INH1LEDPIN, OUTPUT);

  pinMode(PTT2PIN,    OUTPUT);
  pinMode(KEY2nPIN,   INPUT_PULLUP); 
  //pinMode(SPR2PIN,    INPUT_PULLUP);
  pinMode(TX2LEDPIN,  OUTPUT);
  pinMode(INH2LEDPIN, OUTPUT);

  pinMode(PTT3PIN,    OUTPUT);
  pinMode(KEY3nPIN,   INPUT_PULLUP); 
  //pinMode(SPR3PIN,    INPUT_PULLUP);
  pinMode(TX3LEDPIN,  OUTPUT);
  pinMode(INH3LEDPIN, OUTPUT);

  pinMode(PTT4PIN,    OUTPUT);
  pinMode(KEY4nPIN,   INPUT_PULLUP); 
  //pinMode(SPR4PIN,    INPUT_PULLUP);
  pinMode(TX4LEDPIN,  OUTPUT);
  pinMode(INH4LEDPIN, OUTPUT);

// Define connection to relays
#define TX0PIN      PIN_PC2    // 12   output, high true
#define RLY1PIN     PIN_PC3    // 13   output, high true
#define RLY2PIN     PIN_PC4    // 16   output, high true
#define RLY3PIN     PIN_PC5    // 17   output, high true
#define RLY4PIN     PIN_PC6    // 18   output, high true
#define TX1PIN      PIN_PC7    // 19   output, high true

pinMode(TX0PIN, OUTPUT);
pinMode(TX1PIN, OUTPUT);
pinMode(RLY1PIN, OUTPUT);
pinMode(RLY2PIN, OUTPUT);
pinMode(RLY3PIN, OUTPUT);
pinMode(RLY4PIN, OUTPUT);
}