// SO4R Interlock control program
// Function
//   Multiple radios interoperating on the same band
//   Initially, one SSB/CW radio, 3 WSJTX radios
//   WSTTX radios listen on 3 wide spaced antenna
//   SSB/CW operation does not interfere with WSJTX
//   SSb/CW operation has priority and can instantlly inhibit WSJTX TX
//   SSB/CW perator monitors stations heard list from all WSJTX
//   Interlock ensures 
//      only one signal transmitted at a time
//      Stay with contest rules
//      Sequencing to prevent hot switching
//   Single transmitting radio is routed through a single amplifier

// Hardware description
// 4 USB serial ports that receive RTS from computer
// 4 Radio control ports that support 
// Control of 4 transfer relays, dual 4:1 selectors
//   Connect radio to antenna on Rx, amplifier on Tx

// Interface to radio
//   PTT to radio
//   KEY from radio (indicates transmit)
//   Spare input or output (microprocessor logic levels)
//   3 CAT interfaces

// Control relays with signals that select transfer, amp input, amp output


#include <Arduino.h>
#include "HardwareConfig.h"

// put function declarations here:

short Priority;
short PrevPriority;

void setup() {
  // put your setup code here, to run once:

  Priority     = 0;     // 0 - Rx, 1 to 4 Tx
  PrevPriority = 0; 
  
  InitPins();
}

void loop() {
  // Inputs
  //   RTS from USB, when WSJTX wants to transmit
  //   KEY from radio, when radio keyed manually
  // Outputs
  //   PTT to radio, when needing to transmit and highest priority
  // Operation
  //   Read RTS and KET to detect radios needing to transmit
  //   Find highest priority radio needing to transmit
  //     Assert corresponding transfer relay and amplifier selectors
  //     Assert PTT to radio
  // if lower priority radio tries to transmit

  Priority = 0;
  // Read the current state of Tx requests
  if (digitalRead(RTS1nPIN) or !digitalRead(KEY1nPIN)) { // Radio 1 needs to transmit
    Priority = 1;
  } 

  if (digitalRead(RTS2nPIN) or !digitalRead(KEY2nPIN)) { // Radio 1 needs to transmit
    Priority = 2;
  } 

  if (digitalRead(RTS3nPIN) or !digitalRead(KEY3nPIN)) { // Radio 1 needs to transmit
    Priority = 3;
  } 

  if (digitalRead(RTS4nPIN) or !digitalRead(KEY4nPIN)) { // Radio 1 needs to transmit
    Priority = 4;
  } 

  // Detect if there is a state change
  // Cases
  //   from Rx to Tx at any priority
  //   from Tx to Tx at higher priority
  //   from Tx to Rx
  //   lower priority Tx tries to start transmit and gets inhibited

  // Sequencing operation at radios
  //   Rx to Tx
  //     On assertion of PTT, KEY output from radio asserted immediately
  //     Radio delays RF output to allow relays connected to KEY to operate
  //   Tx to Rx
  //     On release of PTT, RF generation stops immediately
  //     RF passing through 2.5 KHz filters is delayed less than 1 msec
  //     KEY released immediately
  //     Relays hold for few msec, so not hot switched on release of PTT

  // Sequencing operation of Interlock
  //   Rx to Tx 
  //     MCU runs in tight loop testing PTT and KEY signals for start of TX
  //     Interlock sees new transmit signal in less than 20 usec
  //     Interlock asserts transfer relay and 4:1 mux immediately
  //     Relays controlled by Interlock are no different from conventional amplifier
  //     Radio delays RF, so no sequencing steps needed for Rx to Tx
  //   Tx to Rx
  //     Interlock sees RTS or KEY drop
  //     RF will drop with 1 msec
  //     Interlock immediately drops transfer and 4:1 mux relays
  //   Tx to higher Priority Tx
  //     Interlock sees start of high priority Tx
  //     For lower priority radio
  //       Immediately drop PTT, radio stops RF within 1 msec
  //       Immediately drop transfer relay
  //       Immediately drop both 4:1 selectors around amplifier
  //       RF is gone before relays have a chance to release
  //     For the higher priority radio
  //       Immediately assert PTT
  //       Immediately assert transfer relay
  //       Immediately assert both 4:1 selectors around amplifier
  //       Radio delays start of RF for 15 msec or more, giving time for relays to close
  //       

  if (Priority != PrevPriority) { //if priority changed

  }

  PrevPriority = Priority;

}

// put function definitions here:
