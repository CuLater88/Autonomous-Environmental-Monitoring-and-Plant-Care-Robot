# Autonomous-Environmental-Monitoring-and-Plant-Care-Robot
An Arduino-powered autonomous system combining sensors, control logic, mechanical hardware, and automated irrigation to monitor environmental conditions and maintain plant health without operator intervention.

## What It Does

- **Live moisture readout** — soil moisture sensor feeds a rolling average to a 16x2 LCD in real time
- **Auto-watering** — once moisture drops below a set threshold, the pump kicks on automatically
- **Reservoir watchdog** — a mechanical low-water sensor on the jug triggers a buzzer + LCD warning ("WATER JUGG EMPTY") and blocks the pump until refilled
- **Grow-light cycle** — a 60-LED WS2812B strip runs on a fixed 16-hours-on / 8-hours-off schedule to simulate a day/night cycle

## Hardware

| Component | Role |
|---|---|
| Arduino-compatible MCU | Brains of the operation |
| 16x2 LCD (parallel) | Moisture readout + alerts |
| Analog soil moisture sensor | Triggers watering logic |
| WS2812B LED strip (60 LEDs) | Grow lighting |
| Pump + driver | Waters the plant |
| Reservoir level System (w/ 220Ω resistor) | Detects empty water jug |
| Piezo buzzer | Audible low-water alert |
| Potentiometer | LCD brightness/contrast |

## How the Loop Works

1. Check the grow-light schedule — flip the LEDs on/off if it's time.
2. Read + average the moisture sensor.
3. If the soil's dry: check the reservoir sensor.
   - Empty → buzz + flash a warning on the LCD until refilled.
   - Full → turn the pump on until moisture's back in range.
4. Repeat forever.
5. <strong>Flow Diagram</strong><br>
<img width="705" height="1471" alt="Automated Planter Box" src="https://github.com/user-attachments/assets/3ff19dfc-3b40-4b9f-a46f-4cdda31da1d6" /><br>

## Project Images
- Circuit Test <br>
<img width="567" height="1008" alt="20210516_190340" src="https://github.com/user-attachments/assets/6f39b74d-caba-4942-b877-452940e428fb" /><br>

- Frame Assembly <br>
<img width="2016" height="1134" alt="20210516_190331" src="https://github.com/user-attachments/assets/b8a206df-0541-4966-bd78-cdf015d593b8" /><br>

- Completed Design <br>
<img width="567" height="1008" alt="20210215_184248" src="https://github.com/user-attachments/assets/c787fc06-1275-4edc-b369-092aba5c82ec" />


## Known Limitations / Future Ideas

- Grow lights currently run a fixed teal color `(0, 120, 120)` — easy to swap to a red/blue spectrum mix if testing growth-rate differences.
- This version (V2) handles **watering only** — nutrient dosing isn't implemented yet, but the threshold-based logic is already set up to extend toward it.
- The water level dection system is operated via a pully system and a make shift button created using tin foil and copper wire. The connections were not always stable. The future plan is to use a Ultra-Sonic sensor to measure the water level, and deliver the alerts similar to the system shown below.
- <img width="650" height="478" alt="image" src="https://github.com/user-attachments/assets/27959379-ddac-47dc-ab0f-6572f674a30c" /><br>
  <i>Not my image<i>


---
