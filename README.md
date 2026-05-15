# SO4R_Interlock V2
The interlock manages up to 4 radios for a contesting scenario

Baseline capability for one SSB/CW radio plus 3 WSJTX radios.
Isolation is sufficient to allow reception on three radios when one radio is transmitting.
SSB/CW radio usually has a rotatable antenna. The three WSJTx instances have radio and antenna, usually a fixed direction.  
Amplifier is shared among radios.

WSJTX feeds N1MM, Gridtracker or other program that display a combined list of stations needed from three radios.
Operator clicks on a station in the list and that WSJTX begins the contact.
SSB/CW operator can continue to operate, which interrupts WSJTX transmission.

Each of 4 radios have a priority with SSB/CW being highest.
SSB/CW operation can continue while WSJTX is making contacts while staying within the ARRL VHF contest rules because WSJTX transmission is interrupted when SSB/CW transmits.

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
  * Uses BTS5200-4 driver chip for fault protection and diagnositc capability
* 12V is sourced from a rig interface using a standard coaxial type M connector
* Each output drives dual 4:1 mux boards with added relay for isolation

USB serial interface
* Implemented with FTDI FT230 usb serial chip
* RTS, output, for signaling Transmit, connected to radio PTT
* CTS, input, available, interfaced to MCU, no function assigned
* Serial TxD, RxD, for CAT, optional growth provision
* FT230 USB EEPROM changed to make it easier to find the ports when connected to a computer
  * Manufacturer string is "FTDI WA1HCO"
  * Product string is "FT230X SO4R Port {1-4}"

SSB/CW radio interface
* highest priority radio, Priority = 1
* USB serial TxD, RxD used for MCU programming
* USB serial RTS used for keying radio from N1MM
* KEY signal from Radio used to set priority and control relays

WSJTX radio interface
* Lower priority radios, Priority = 2, 3, or 4
* USB serial implements COM port, control signal RTS used by WSJTX software
* Serial data TxD and RxD converted to CAT bidirectional open collector, growth provision
* RTS signal used for PTT command to radio
* CTS signal routed to MCU but not assigned a function

WSJTX operation
* Operator uses ssb/cw radio for contacts and has highest priority for transmitting.
* 3 WSJTX instances listen on 3 radios in 3 directions.
* Each WSJTX sends it list of callsigns to N1MM or Gridtracker which displays list of stations color coded by log status (needed or duplicate).
* The operator clicks on a callsign in the list to start a WSJTX contact.
* WSJTX indicates need to transmit by asserting RTS on its serial interface

