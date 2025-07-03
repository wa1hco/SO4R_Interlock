# SO4R_Interlock
The interlock manages up to 4 radios for a contesting scenario
Baseline capability for one SSB/CW radio plus 3 WSJTX radios.
Antenna separation is sufficient to allow reception when other radio is transmitting
SSB/CW radio has an amplifier and rotatable antenna
Each of three WSJTx instances have radio, amplifier, and antenna (generally fixed)
WSJTX operator monitors list of available stations and may click ENABLE transmission
Each of 4 radio have a priority with SSB/CW being highest
SSB/CW operation can continue while WSJTX is making contacts while staying within the rules

When a high priority tranmitter needs to interrupt a lower priority tranmission, 
the interlock gates the PTT/RTS/DTR line to the lower priority radio.  This keeps the radio's
built in sequencer operating to protect the amplifier, preamp, and relays.

The interlock has one ssb/cw port that receives the TX signal from the radio.  The operator
generates the TX signal from PTT, VOX, or CW so the interlock does not need to provice TX
to the SSB/CW radio.

The interlock includes a USB serial port to provide the TX signal.  The microcontroller then
gates the TX signal based on higher priority TX signal

Operator uses ssb/cw radio for contacts and has highest priority for transmitting
An operator also monitors the received callsigns from up to three WSJTX instances. Separately 
from the Interlock, WSJTX callsigns are received, compared with the log and turned into a 
color coded list of callsigns and grids.  On selecting a station from the list, the corresponding
WSJTX is enabled for transmit

Interface from Interlock to Radio
The SSB/CW radio only has an input to interlock for TX
The three WSJTX radios have an output from interlock for Tx and an input 

SO4R Interlock
- SSB/CW radio with operator
- added radios for FT8
Radio Interface
- PTT, bidirectional
- Tx inhibit
Operation
- watch for PTT asserted from all radios
- On PTT, assert Tx inhibit to all lower priority ports
- priority determined by port number on interlock

