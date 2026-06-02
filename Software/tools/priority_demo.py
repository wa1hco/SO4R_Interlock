#!/usr/bin/env python3
"""Demonstrate SO4R Interlock priority preemption across two ports.

Priority order is KEY1 > RTS2 > RTS3 > RTS4. This drives RTS on a
lower-priority port, then asserts a higher-priority port on top, then
releases in reverse, so you can watch a port get preempted and recover.

Usage:
    priority_demo.py <low_prio_port> <high_prio_port> [dwell_s]

Example (port 3 preempted by port 2):
    priority_demo.py /dev/ttyUSB4 /dev/ttyUSB3 4
"""
import sys
import time
import serial

low = sys.argv[1]
high = sys.argv[2]
dwell = float(sys.argv[3]) if len(sys.argv) > 3 else 4.0

a = serial.Serial(low, 9600, timeout=0)
b = serial.Serial(high, 9600, timeout=0)
try:
    a.rts = b.rts = False
    time.sleep(0.5)

    print(f"1) assert LOW-prio  {low}: expect its GREEN on (holds amp)")
    a.rts = True
    time.sleep(dwell)

    print(f"2) assert HIGH-prio {high} on top: expect HIGH green, LOW -> YELLOW (blocked), RLY yellow on")
    b.rts = True
    time.sleep(dwell)

    print(f"3) release HIGH {high}: expect LOW returns to GREEN, HIGH off, RLY yellow off")
    b.rts = False
    time.sleep(dwell)

    print(f"4) release LOW {low}: expect all off")
    a.rts = False
    time.sleep(1.0)
    print("done.")
finally:
    try:
        a.rts = b.rts = False
    finally:
        a.close()
        b.close()
