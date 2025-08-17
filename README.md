# SO4R_Interlock V2
The interlock manages up to 4 radios for a contesting scenario

Baseline capability for one SSB/CW radio plus 3 WSJTX radios.
Antenna separation is sufficient to allow reception when other radio is transmitting
SSB/CW radio has an amplifier and rotatable antenna

Each of three WSJTx instances have radio and antenna (generally fixed).  Amplifier is shared among radios
WSJTX feeds N1MM, Gridtracker or other program that display a combined list of stations needed.
Operator clicks on a station in the list and that WSJTX begins the contact.
SSB/CW operator can continue to operate, which interrupts WSJTX transmission.

Each of 4 radio have a priority with SSB/CW being highest
SSB/CW operation can continue while WSJTX is making contacts while staying within the ARRL VHF contest rules

When a higher priority tranmitter needs to interrupt a lower priority tranmission, 
the interlock gates the PTT line to the lower priority radio.  This keeps the radio's
built in sequencer operating to protect the amplifier, preamp, and relays.  
The interlock also controls the RF relays to disconnect the lower priority transmitter 
and connect the highest priority transmitter

Radio Interface
* PTT, output open collector, low true, 60V, 300 mA
* KEY, input, open collector, low true, 5 to 15 V
* CAT, bidirectional, open collector, ttl levels, serial communication
* Spare, direct connection to MCU I/O pin

Relay interface
* Relay output are drive high from nominal 12V source
  * uses BTS5200-4 driver chip for fault protection and diagnositc capability
* 12V is sourced from a rig interface for from coaxial type M connector
* each output drives DPDT transfer relay and one port of 4:1 selector on both amp input and output

USB serial interface
* Implemented with FTDI FT230 usb serial chip
* TxD, RxD, for CAT
* RTS, output, for signaling Transmit
* CTS, input, available, interfaced to MCU, no function assigned
* USB EEPROM changed to make it easier to find the ports
  * Manufacturer is "FTDI WA1HCO"
  * Product is "FT230X SO4R Port {1-4}"

SSB/CW radio interface
* highest priority radio, Priority = 1
* USB serial TxD, RxD used for MCU programming
* USB serial RTS used for keying radio from N1MM
* KEY signal from Radio used to set priority and control relays

WSJTX radio interface
* Lower priority radios, Priority = 2, 3, or 4
* USB serial implements COM port used by WSJTX software
* Serial data TxD and RxD converted to CAT bidirectional open collector
* RTS signal used for Tx command to radio
* CTS signal routed to MCU but not assigned a function

WSJTX operation
* Operator uses ssb/cw radio for contacts and has highest priority for transmitting.
* 3 WSJTX instances listen on 3 radios in 3 directions.
* Each WSJTX sends it list of callsigns to N1MM or Gridtracker which displays list of needed stations.
* The operator clicks on a callsign in the list to start a WSJTX contact.
* WSJTX indicates need to transmit by asserting RTS on its serial interface

