// SO4R Interlock control program
// Function
//   Multiple radios interoperating on the same band
//   Baseline, one SSB/CW radio, up to 3 WSJTX radios
//   WSJTX radios listen on 3 wide spaced antenna, separte directions
//   3 radios can hear when 1 radio transmitting
//   Only one radio can transmit at a time
//   SSb/CW operation has priority and can instantlly inhibit WSJTX TX
//   WSJTX radios listen in 3 directions
//   WSJTX sends stations heard to combined list for review by SSB/CW op
//   Interlock detects SSB/CW Tx by reading KEY line from radio
//   Interlock detects WSJTX Tx by reading RTS line from USB interface

// Interlock ensures 
//   only one signal transmitted at a time
//   Stay within ARRL VHF contest rules
//   Sequencing to prevent hot switching
// Transmitting radio is routed through a single amplifier

// Interlock hardware description
//   4 USB serial ports that support CAT and RTS
//   4 Radio control ports that support PTT, KEY, CAT, Spare
//   4 relay control ports for transfer relays and dual 4:1 Mux (for amplifier)

// Interlock software description
//   Read RTS (Tx requests) and KEY {radio Tx'ing}
//   Compute Priority, 0 Rx (no Tx), 1 SSB/CW, 2, 3, 4 WSJTX
//   if RTS or KEY, assert PTT and Relay to highest priority radio

#include <HardwareConfig.h>

void setup() {
  
  ConfigPins(); // configure the I/O pins
 
  // all Tx off
  digitalWrite(   PTT1PIN, false);  // Radio 1 PTT, generally not used
  digitalWrite(   PTT2PIN, false);  // Radio 2 PTT
  digitalWrite(   PTT3PIN, false);  // Radio 3 PTT
  digitalWrite(   PTT4PIN, false);  // Radio 4 PTT

  // all relays off
  digitalWrite(   RLY1PIN, false);  // Priority 1 Relays, SSB/CW radio
  digitalWrite(   RLY2PIN, false);  // Priority 2 Relays, WSJTX radio
  digitalWrite(   RLY3PIN, false);  // Priority 3 Relays, WSJTX radio
  digitalWrite(   RLY4PIN, false);  // Priority 4 Relays, WSJTX radio

  // all LEDs on RJ45 off
  digitalWrite( RIGGRN1PIN, false);
  digitalWrite(RIGYEL1PIN, false);
  digitalWrite( RIGGRN2PIN, false);
  digitalWrite(RIGYEL2PIN, false);
  digitalWrite( RIGGRN3PIN, false);
  digitalWrite(RIGYEL3PIN, false);
  digitalWrite( RIGGRN4PIN, false);
  digitalWrite(RIGYEL4PIN, false);

  // CTS\ from MCU to USB chip not asserted
  digitalWrite(  CTS2nPIN, true);
  digitalWrite(  CTS3nPIN, true);
  digitalWrite(  CTS4nPIN, true);
}

// Inputs
//   RTS\ from USB, when WSJTX wants to transmit
//   KEY\ from radio, when radio keyed by PTT or manually
// Outputs
//   PTT to radio, when needing to transmit and highest priority
//   RLYn to relays, when controlling which radio uses amplifier
//   TX LED, on RJ45 connector for each radio interface, indicates TX and has amplifier
//   INH LED, on RJ45 connector for each radio interface, indicates wants to TX but not highest priority
// Operation
//   Read RTS and KEY IO and save to variables for speed
//   Compute the Priority from all Tx requests
//   Assert PTT to radio if RTS asserted and highest priority
//   Assert RLY to relays if KEY asserted and highest priority
//   Assert TX led to radio interface if KEY and highest priority 
//   Assert Inhibit LED to radio interface if KEY asserted and not highest priority

// Explicit sequencing operation not need in Interlock
//   Rx to Tx
//     On assertion of PTT, KEY output from radio asserted immediately
//     Radio delays RF output to allow relays connected to KEY to operate
//     Interlock picks up PTT or KEY and immediately asserts relays
//     Relays controlled by Interlock are no different from conventional amplifier
//     Radio delays RF, so no sequencing steps needed for Rx to Tx
//   Tx to Rx
//     On release of PTT, RF generation stops immediately
//     RF passing through 2.5 KHz filters is delayed less than 1 msec
//     KEY released immediately
//     Interlock releases relays immediately
//     Relays hold for few msec, so not hot switched on release of PTT

// Timing of Interlock software
//   On every pass through loop() function
//     Read PTT and KEY signals and save to variables
//     Interrupts masked during read to make state of variables as consistent as possible
//     Interlock sees new transmit signal in less than 20 usec (TBD)
//     Interlock asserts transfer relay and 4:1 mux immediately
//   Determine priority from both RTS and KEY signals
//     0 means Rx, 1 for SSB/CW, 2, 3, 4 for WSJTX
//   Copy RTS signal from COM port to PTT, masked by priority
//     If no RTS asserted, PTT released
//     If RTS asserted, but not highest priority, PTT released
//     If RTS asserted and highest priority, corresponding PTT asserted
//   Copy Priority signal from radio to relays
//     if lower priority, set relays to RX
//     if highest priority, set relays to TX
//   Benefits of this algorithm
//     Priority determined from both RTS and KEY
//       Priority goes up immediately when high priority RTS appears
//     RTS can immediately control PTT 
//       RTS assertion at highest priority immediately asserts PTT
//       RTS assertion at highest priority also updates priority
//       RTS release immediately releases PTT
//     KEY signal from radios controls relays (as intended by the radio manufacturers)
//       KEY assertion lags PTT by 8 usec on some ICOM radios
//       KEY release may also lag
//       KEY release may be delayed by slow pullup of open collector design
//       KEY may come from from manual activation of PTT, VOX, CW, Tune, etc.
//       KEY is masked by priority and routed to each relay


void loop() {
  short Priority;
  
  // Read all inputs, convert from low true to high true logic
  // Read as atomically as practicable
  noInterrupts();
  bool RTS1 = !digitalReadFast(RTS1nPIN);  // RTS from serial port asks for Tx
  bool RTS2 = !digitalReadFast(RTS2nPIN);
  bool RTS3 = !digitalReadFast(RTS3nPIN);
  bool RTS4 = !digitalReadFast(RTS4nPIN);  

  bool KEY1 = !digitalReadFast(KEY1nPIN);  // KEY from radio says Tx from RTS or manual
  bool KEY2 = !digitalReadFast(KEY2nPIN);
  bool KEY3 = !digitalReadFast(KEY3nPIN);
  bool KEY4 = !digitalReadFast(KEY4nPIN);
  interrupts();

  // Priority initialized to 0 (Rx)
  // Priority 1 (highest) radio is usually SSB/CW, commanded to Tx by VOX or CW
  // Priority 2, 3, 4 radios are usually WSJTX, commanded to Tx by RTS\
  // Interlock also reads the KEY\ line from the radio to sense Tx

  // Compute Priority based on RTS and KEY inputs
  // Priorities tested from lowest to highest
  // Highest priority sets final value of Priority
  // If no Tx requests, remains at 0 (Rx)
  Priority = 0;                    // Rx mode
  if (RTS4 or KEY4) Priority = 4;  // WSJTX radio
  if (RTS3 or KEY3) Priority = 3;  // WSJTX radio
  if (RTS2 or KEY2) Priority = 2;  // WSJTX radio
  if (RTS1 or KEY1) Priority = 1;  // SSB/CW radio

  // Output signals in order of timing criticality
  // Assert Tx to relay corresponding to priority set from RTS and KEY, others stay Rx
  bool RLY1    = (Priority == 1);
  bool RLY2    = (Priority == 2);
  bool RLY3    = (Priority == 3);
  bool RLY4    = (Priority == 4);
  digitalWrite(RLY1PIN,    RLY1);
  digitalWrite(RLY2PIN,    RLY2);
  digitalWrite(RLY3PIN,    RLY3);
  digitalWrite(RLY4PIN,    RLY4);

  // Asserts Tx on radio with RTS and corresponding to priority, all others stay Rx
  bool PTT1    = RTS1 and (Priority == 1);
  bool PTT2    = RTS2 and (Priority == 2);
  bool PTT3    = RTS3 and (Priority == 3);
  bool PTT4    = RTS4 and (Priority == 4);
  digitalWrite(PTT1PIN,    PTT1);
  digitalWrite(PTT2PIN,    PTT2);
  digitalWrite(PTT3PIN,    PTT3);
  digitalWrite(PTT4PIN,    PTT4);

  // Assert Tx LED to RJ45 LED highest priority radio interface
  bool RIGGRN1  = (Priority == 1);
  bool RIGGRN2  = (Priority == 2);
  bool RIGGRN3  = (Priority == 3);
  bool RIGGRN4  = (Priority == 4);
  digitalWrite(RIGGRN1PIN,  RIGGRN1);
  digitalWrite(RIGGRN2PIN,  RIGGRN2);
  digitalWrite(RIGGRN3PIN,  RIGGRN3);
  digitalWrite(RIGGRN4PIN,  RIGGRN4);

  // Assert Inhibit LED to RJ45 LED if radio want Tx but not highest priority
  bool INH2LED = (RTS2 or KEY2) and (Priority > 0) and (Priority < 2);
  bool INH3LED = (RTS3 or KEY3) and (Priority > 0) and (Priority < 3);
  bool INH4LED = (RTS4 or KEY4) and (Priority > 0) and (Priority < 4);
  digitalWrite(RIGYEL2PIN, INH2LED); 
  digitalWrite(RIGYEL3PIN, INH3LED);
  digitalWrite(RIGYEL4PIN, INH4LED);

} // loop()

// put function definitions here:
