#!/usr/bin/env python3
"""Assert/release RTS on a serial port to exercise the SO4R Interlock LEDs.

The Interlock reads RTS (low-true on the wire; pyserial's rts=True asserts it)
as a WSJT-X transmit request on ports 2-4. Watch the RJ45 LEDs:
  - the port's GREEN should light when it holds priority (amp granted)
  - YELLOW if it is blocked by a higher-priority port

Usage:
    rts_toggle.py /dev/ttyUSBn [on_seconds] [off_seconds] [cycles]

Defaults: 2 s on, 2 s off, 3 cycles. Ctrl-C drops RTS and exits.
"""
import sys
import time
import serial

port = sys.argv[1] if len(sys.argv) > 1 else "/dev/ttyUSB0"
on_s = float(sys.argv[2]) if len(sys.argv) > 2 else 2.0
off_s = float(sys.argv[3]) if len(sys.argv) > 3 else 2.0
cycles = int(sys.argv[4]) if len(sys.argv) > 4 else 3

# Open without disturbing the line more than necessary.
ser = serial.Serial(port, 9600, timeout=0)
try:
    ser.rts = False  # start de-asserted (receive)
    print(f"{port}: RTS released (idle). Starting {cycles} cycles.")
    time.sleep(0.5)
    for i in range(1, cycles + 1):
        ser.rts = True
        print(f"  cycle {i}: RTS ASSERTED  (expect TX request -> LED)  {on_s}s")
        time.sleep(on_s)
        ser.rts = False
        print(f"  cycle {i}: RTS released  (expect idle / LED off)     {off_s}s")
        time.sleep(off_s)
    print("done; RTS left released.")
finally:
    try:
        ser.rts = False
    finally:
        ser.close()
