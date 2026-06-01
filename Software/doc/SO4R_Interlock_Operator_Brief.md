# SO4R Interlock — Operator Brief

Quick reference for **setting up, debugging, and operating** the SO4R Interlock during a
contest. Two reference sections:

- **[RJ45 LED indicators](#rj45-led-indicators)** — what the front-of-board lights mean.
- **[Radio interface cables](#radio-interface-cables)** — per-cable pinouts.

For the full design rationale see the top-level `README.md` and the design presentation.

---

## How it works

The Interlock enforces **one transmitter at a time** across four radios, with hot-switch
protection, by gating PTT and switching the RF transfer relays.

- **Radio 1 = SSB/CW**, requests transmit with **KEY**; **highest priority**.
- **Radios 2–4 = WSJT-X / digital**, request transmit with **RTS over USB** (the Interlock
  then drives **PTT** to the radio).
- **Priority (highest → lowest): KEY1 ▸ RTS2 ▸ RTS3 ▸ RTS4.** A higher-priority request
  immediately takes the amplifier/relays from a lower one.

Active-low signals are written with a trailing `/` (in the raw KiCad files: `{slash}`).

> **Why it's an interlock, not a sequencer:** when the SSB/CW radio asserts KEY, any WSJT
> PTT is blocked immediately and RF drops in under 1 ms — before the WSJT transfer relay
> mechanically opens — so there is no hot switching.

---

## RJ45 LED indicators

Each RJ45 jack has **two LEDs — green and yellow**. There are **four radio ports**
(RIG1–RIG4, one per radio cable) and **one relay/transfer port** (RLY, the cable to the
relay box).

**At power-on** a **ripple "lamp test"** runs across every LED — yellow then green, relay
port first, then each radio port in turn — then all go dark. Seeing the sweep confirms the
MCU booted and the LEDs work.

### Radio port (RIG1–RIG4)

| LED | Meaning |
|---|---|
| **Both off** | Radio is idle (receiving); no transmit request. |
| **Green** | This radio holds priority and the **amplifier/relays + antenna** — it's the active transmitter. |
| **Yellow** | This radio is **inhibited** — transmitting (or asking to) **without** the amp/relays. |

A radio port shows green *or* yellow, never both.

**Yellow has two causes:**

1. **Blocked / waiting** — the radio asked to transmit (RTS from WSJT-X) but a
   **higher-priority radio currently holds TX**; it waits its turn.
2. **Manual TX** — the operator pressed the **radio's own TX/PTT button** (KEY with no RTS).
   The radio keys itself, but the Interlock refuses the amplifier/relays, so it transmits
   **barefoot into the pass-through antenna**. The "don't do that" indicator.

**Radio 1 (SSB/CW) shows green only** — it's highest priority, so it is never inhibited and
has no yellow.

### Relay / transfer port (RLY)

| LED | Meaning |
|---|---|
| **Green** | At least one radio is transmitting (relays engaged / system in TX). |
| **Yellow** | At least one WSJT radio is currently inhibited (blocked or manually keyed). |

### Quick mental model

- **Green = transmitting with the amplifier** (priority granted).
- **Yellow = transmit denied** — waiting behind a higher-priority radio, or keyed manually
  around the software.

---

## Radio interface cables

Pin tables are extracted from the KiCad netlist (authoritative connectivity), not hand-read
from the schematic.

> Source of truth: the KiCad project in `Hardware/Radio_Interface_Cables/`. Regenerate the
> connectivity with:
> `kicad-cli sch export netlist --format kicadxml Radio_Interface_Cables.kicad_sch`
>
> **Project structure (after sheet cleanup):** `Radio_Interface_Cables.kicad_pro` is one
> hierarchical project. The Root sheet is an **index** holding one sheet symbol per cable;
> each cable lives on its own sub-sheet: `IC-9700`, `IC-9100`, `IC-746PRO`, `K3S`, `K4`.

Each cable adapts **one radio's accessory connectors** to the Interlock over a single
**RJ45** link.

### Standard Interlock RJ45 pinout (all five cables)

The RJ45 (Interlock end) is wired **identically on every cable** — this is the Interlock's
standard radio port. Check these pins first when debugging:

| RJ45 pin | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|
| Signal | 12 V | CAT | GND | **PTT/** | GND | **KEY/** | GND | SPR |

### Cable connector inventory

Every cable runs **radio connectors ⟶ RJ45 ⟶ Interlock**. One RJ45 per cable.

| Cable | Radio-end connectors |
|---|---|
| **IC-9700** | ACC (DIN-8), 6.25 mm plug, 3.5 mm plug |
| **IC-9100** | ACC (DIN-13), 6.25 mm plug + jack, 3.5 mm plug |
| **IC-746PRO** | ACC1 (DIN-8), ACC2 (DIN-7), 6.25 mm plug + jack, 3.5 mm plug |
| **K3S** | ACC (DE15 HD-15), PowerPole, 6.25 mm plug + jack |
| **K4** | ACC (DE15 HD-15), PowerPole, 6.25 mm plug + jack |

### Per-cable pinouts

Full as-wired pinout per cable. "RJ45" = Interlock-end pin (see standard pinout above); "–"
= not on the RJ45. "Radio end" = where the signal lands on the radio side. The 6.25 mm and
3.5 mm audio connectors are 2-conductor (TS): **Tip** carries the signal, **Sleeve** is
grounded.

#### IC-9700  (Icom)

| Signal | RJ45 | Radio end |
|---|---|---|
| 12 V  | 1 | DIN-8 p7 |
| CAT   | 2 | 3.5 mm plug Tip |
| PTT/  | 4 | 6.25 mm plug Tip |
| KEY/  | 6 | DIN-8 p3 |
| SPR   | 8 | DIN-8 p6 |
| MOD   | – | DIN-8 p4 |
| AF/IF | – | DIN-8 p5 |
| ALC   | – | DIN-8 p8 |
| RTTY  | – | DIN-8 p1 |
| GND   | 3, 5, 7 | DIN-8 p2; plug sleeves |

#### IC-9100  (Icom)

| Signal | RJ45 | Radio end |
|---|---|---|
| 12 V   | 1 | DIN-13 p8 |
| CAT    | 2 | 3.5 mm plug Tip |
| PTT/   | 4 | 6.25 mm plug Tip; 6.25 mm jack Tip |
| KEY/   | 6 | *(RJ45 only)* |
| SPR    | 8 | DIN-13 p13 |
| 8 V    | – | DIN-13 p1 |
| AF     | – | DIN-13 p12 |
| MOD    | – | DIN-13 p11 |
| ALC    | – | DIN-13 p6 |
| BAND   | – | DIN-13 p5 |
| HSEND/ | – | DIN-13 p3 |
| VSEND/ | – | DIN-13 p7 |
| RTTY   | – | DIN-13 p10 |
| GND    | 3, 5, 7 | DIN-13 p2; plug/jack sleeves |

*(DIN-13 pins 4 and 9 are no-connect.)*

#### IC-746PRO  (Icom)

| Signal | RJ45 | Radio end |
|---|---|---|
| 12 V   | 1 | ACC1 (DIN-8) p7; ACC2 (DIN-7) p7 |
| CAT    | 2 | 3.5 mm plug Tip |
| PTT/   | 4 | 6.25 mm plug Tip; 6.25 mm jack Tip |
| KEY/   | 6 | *(RJ45 only)* |
| SPR    | 8 | ACC1 (DIN-8) p6 |
| 8 V    | – | ACC2 (DIN-7) p1 |
| AF     | – | ACC1 (DIN-8) p5 |
| MOD    | – | ACC1 (DIN-8) p4 |
| ALC    | – | ACC1 (DIN-8) p8; ACC2 (DIN-7) p5 |
| BAND   | – | ACC2 (DIN-7) p4 |
| HSEND/ | – | ACC1 (DIN-8) p3; ACC2 (DIN-7) p3 |
| VSEND/ | – | ACC2 (DIN-7) p6 |
| RTTY   | – | ACC1 (DIN-8) p1 |
| GND    | 3, 5, 7 | ACC1 p2; ACC2 p2; plug/jack sleeves |

#### K3S  (Elecraft)

| Signal | RJ45 | Radio end |
|---|---|---|
| 12 V    | 1 | *(RJ45 only)* |
| CAT     | 2 | *(RJ45 only)* |
| PTT/    | 4 | DE15 p4; 6.25 mm jack Tip; 6.25 mm plug Tip |
| KEY/    | 6 | DE15 p10 |
| SPR     | 8 | *(RJ45 only)* |
| 13.8 V  | – | PowerPole p1 |
| ALC     | – | DE15 p15 |
| AUXBUS  | – | DE15 p2 |
| BAND0   | – | DE15 p13 |
| BAND1   | – | DE15 p3 |
| BAND2   | – | DE15 p9 |
| BAND3   | – | DE15 p14 |
| DIGOUT0 | – | DE15 p6 |
| DIGOUT1 | – | DE15 p11 |
| K3S_ON  | – | DE15 p7 |
| PWR_ON  | – | DE15 p8 |
| RTTY    | – | DE15 p1 |
| GND     | 3, 5, 7 | DE15 p5, p12; PowerPole p2; plug/jack sleeves |

#### K4  (Elecraft)

| Signal | RJ45 | Radio end |
|---|---|---|
| 12 V    | 1 | PowerPole p1 |
| CAT     | 2 | *(RJ45 only)* |
| PTT/    | 4 | DE15 p4; 6.25 mm jack Tip; 6.25 mm plug Tip |
| KEY/    | 6 | DE15 p10 |
| SPR     | 8 | *(RJ45 only)* |
| ALC     | – | DE15 p15 |
| AUXBUS  | – | DE15 p2 |
| BAND0   | – | DE15 p13 |
| BAND1   | – | DE15 p3 |
| BAND2   | – | DE15 p9 |
| BAND3   | – | DE15 p14 |
| DIGOUT0 | – | DE15 p6 |
| DIGOUT1 | – | DE15 p11 |
| PWR_ON  | – | DE15 p8 |
| RTTY    | – | DE15 p1 |
| **TX_INH** | – | DE15 p7 |
| GND     | 3, 5, 7 | DE15 p5, p12; PowerPole p2; plug/jack sleeves |

### Notes for setup / debug

- **KEY/ and PTT/** are the lines the Interlock acts on — check RJ45 pins 6 and 4 first if
  a radio won't key the amp/relays or won't release.
- **KEY/ to the radio** is wired through only on IC-9700 (DIN-8 p3) and the Elecraft cables
  (DE15 p10). On **IC-9100 / IC-746PRO, KEY/ stops at the RJ45** — those radios are keyed
  via PTT. Worth knowing when tracing a no-key fault.
- **PTT/** is also broken out to the **6.25 mm plug and jack** on every cable (and DE15 p4
  on the Elecrafts) — a footswitch/external-PTT tap in parallel with the Interlock.

### Caveats

- Pinouts reflect the **as-wired netlist** of the current schematic. They describe what the
  cable *does*, which may differ from the radio manual's intended ACC pinout — verify
  suspicious signals.
- Reference designators (`J#`) are intentionally omitted; the tables key on connector type
  and pin, so they survive re-annotation after the sheet cleanup.
