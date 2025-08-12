#ifndef HardwareConfig_h
#define HardwareConfig_h
// Hardware configuration from the V1 schematic
#include <Arduino.h> // get the pin names

// AVR32DB48, Hardware Pin Definitions, lower case means secondary pin location
//-----|--------|----------|------|-------|--------|-------|-----|--------|--------|
// Pin | Name   | Function | Free | Power | Serial | ADC   | DAC |  SPI   |  TWI   |
//-----|--------|----------|------|-------|--------|-------|-----|--------|--------|
//  1  | PA5    | RIG4GRN  |      |       | 0,rxd  |       |     |        |        |
//  2  | PA6    | RTS4\    |      |       | 0,xck  |       |     | 0,MOSI |        |
//  3  | PA7    | CTS4\    |      |       | 0,xdir |       |     | 0,MISO |        |
//  4  | PB0    | RTS3\    |      |       | 3,TXD  |       |     | 0,SCK  |        |
//  5  | PB1    | CTS3\    |      |       | 3,RXD  |       |     | 0,SS\  |        |
//  6  | PB2    | CTS2\    |      |       | 3,XCK  |       |     |        | 1,sda  |
//  7  | PB3    | RTS2\    |      |       | 3,XDIR |       |     |        | 1,scl  |
//  8  | PB4    | RTS1\    |      |       | 3,txd  |       |     |        |        |
//  9  | PB5    | DEN      |      |       | 3,rxd  |       |     |        |        |
// 10  | PC0    | DSEL0    |      |       | 1,TXD  |       |     |        |        |
// 11  | PC1    | DSEL1    |      |       | 1,RXD  |       |     |        |        |
// 12  | PC2    | RLYYEL   |      |       | 1,XCK  |       |     |        | 0,sda  |
//-----|--------|----------|------|-------|--------|-------|-----|--------|--------|
// 13  | PC3    | RLY1     |      |       | 1,XDIR |       |     |        | 0,scl  |
// 14  | VDDIO2 |          |      | 5V    |        |       |     |        |        |
// 15  | GND    |          |      | GND   |        |       |     |        |        |
// 16  | PC4    | RLY2     |      |       | 1,txd  |       |     |        |        |
// 17  | PC5    | RLY3     |      |       | 1,rxd  |       |     |        |        |
// 18  | PC6    | RLY4     |      |       | 1,xck  |       |     |        | 0,sda  |
// 19  | PC7    | RLYGRN   |      |       | 1,xdir |       |     |        | 0,sda  |
// 20  | PD0    | RIG1YEL  |      |       |        | AIN0  |     |        |        |
// 21  | PD1    | SPR1     |      |       |        | AIN1  |     |        |        |
// 22  | PD2    | KEY1\M   |      |       |        | AIN2  |     |        |        |
// 23  | PD3    | PTT1     |      |       |        | AIN3  |     |        |        |
// 24  | PD4    | RIG1GRN  |      |       |        | AIN4  |     |        |        |
//-----|--------|----------|------|--=----|--------|-------|-----|--------|--------|
// 25  | PD5    | RIG2YEL  |      |       |        | AIN5  |     |        |        |
// 26  | PD6    | SPR2     |      |       |        | AIN6  | OUT |        |        |
// 27  | PD7    | KEY2\M   |      |       |        | AIN7  |     |        |        |
// 28  | AVDD   |          |      | 5V    |        |       |     |        |        |
// 29  | AGND   |          |      | GND   |        |       |     |        |        |
// 30  | PE0    | PTT2     |      |       | 4,TXD  | AIN8  |     | 0,mosi |        |
// 31  | PE1    | IS       |      |       | 4,RXD  | AIN9  |     | 0,miso |        |
// 32  | PE2    | RIG2GRN  |      |       | 4,XCK  | AIN10 |     | 0,sck  |        |
// 33  | PE3    | RIG3YEL  |      |       | 4,XDIR | AIN11 |     | 0,ss\  |        |
// 34  | PF0    | SPR3     |      |       | 2,TXD  |       |     |        |        |
// 35  | PF1    | KEY3\M   |      |       | 2,RXD  |       |     |        |        |
// 36  | PF2    | PTT3     |      |       | 2,XCK  |       |     |        | 1,SDA  |
//-----|--------|----------|------|-------|--------|-------|-----|--------|--------|
// 37  | PF3    |          | PF3  |       | 2,XDIR |       |     |        | 1,SCL  |
// 38  | PF4    | RIG3GRN  |      |       | 2,txd  |       |     |        |        |
// 39  | PF5    | RIG4YEL  |      |       | 2,rxd  |       |     |        |        |
// 40  | PF6    | RESET    |      | RESET |        |       |     |        |        |
// 41  | UPDI   | UPDI     |      | UPDI  |        |       |     |        |        |
// 42  | VDD    | 5V       |      | 5V    |        |       |     |        |        |
// 43  | GND    | GND      |      | GND   |        |       |     |        |        |
// 44  | PA0    | TXD_M    |      |       | 0,TXD  |       |     |        |        |
// 45  | PA1    | RXD_M    |      |       | 0,RXD  |       |     |        |        |
// 46  | PA2    | SPR4     |      |       | 0,XCK  |       |     |        | 0,SDA  |
// 47  | PA3    | KEY4\M   |      |       | 0,XDIR |       |     |        | 0,SCL  |
// 48  | PA4    | PTT4     |      |       | 0,txd  |       |     |        |        |
//-----|--------|----------|------|-------|--------|-------|-----|--------|--------|


// Define connections to USB Serial ports
//      PinName     Port Name  TQFP48  Function
#define RTS1nPIN    PIN_PB4    //  8   input,  low true
#define RTS2nPIN    PIN_PB3    //  7   input,  low true
#define RTS3nPIN    PIN_PB0    //  4   input,  low true
#define RTS4nPIN    PIN_PA6    //  2   input,  low true

//#define CTS1nPIN    PIN_PC0    // 14   output, low true
#define CTS2nPIN    PIN_PB2    //  6   output, low true
#define CTS3nPIN    PIN_PB1    //  5   output, low true
#define CTS4nPIN    PIN_PA7    //  3   output, low true

// Define connections to rigs
//      PinName     Port Name  TQFP48  Function
#define KEY1nPIN    PIN_PD2    // 22   input,  low true,  radio keyed
#define KEY2nPIN    PIN_PD7    // 27 
#define KEY3nPIN    PIN_PF1    // 35
#define KEY4nPIN    PIN_PA3    // 47

#define PTT1PIN     PIN_PD3    // 23   output, high true, key radio
#define PTT2PIN     PIN_PE0    // 30
#define PTT3PIN     PIN_PF2    // 36
#define PTT4PIN     PIN_PA4    // 48

#define SPR1PIN     PIN_PD1    // 21   input/output, TBD function
#define SPR2PIN     PIN_PD6    // 26
#define SPR3PIN     PIN_PF0    // 34
#define SPR4PIN     PIN_PA2    // 46

// Define LEDs on RJ-45 rig interface jack
//      PinName     Port Name  TQFP48  Function
#define RIG1YELPIN  PIN_PD0    // 20   output, high true, radio keyed
#define RIG2YELPIN  PIN_PD5    // 25
#define RIG3YELPIN  PIN_PE3    // 33
#define RIG4YELPIN  PIN_PF5    // 39

#define RIG1GRNPIN  PIN_PD4    // 24   output, high true, radio inhibited
#define RIG2GRNPIN  PIN_PE2    // 32
#define RIG3GRNPIN  PIN_PF4    // 38
#define RIG4GRNPIN  PIN_PA5    //  1

// Define connection to relays
#define RLY1PIN     PIN_PC3    // 13   output, high true
#define RLY2PIN     PIN_PC4    // 16   output, high true
#define RLY3PIN     PIN_PC5    // 17   output, high true
#define RLY4PIN     PIN_PC6    // 18   output, high true

// Define connections to LEDs on RJ-45 relay interface JACK
#define RLYYELPIN   PIN_PC2    // 12   output, high true
#define RLYGRNPIN   PIN_PC7    // 19   output, high true

// Define connections to BTS5200 relay driver
#define DENPIN      PIN_PB5    // Data Enable
#define DSEL0PIN    PIN_PC0    // Data Select
#define DSEL1PIN    PIN_PC1     
#define ISPIN       PIN_PE0    // Analog from BTS5300

// Public function
void ConfigPins();

#endif