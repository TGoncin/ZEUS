<div align="center">
  <img width="300" alt="ZEUS Logo" src="https://github.com/user-attachments/assets/YOUR_ZEUS_LOGO_HERE" />
</div>

<br>
<br>

<div align="center">
  <h1>ZEUS — Soil Moisture Retention System</h1>
  <p><em>A fully automated, microcontroller-operated, soil moisture monitored irrigation system</em></p>
</div>

<br>

<div align="center">
  <h3>README Quick Links</h3>
  <br>
  <p>
    <a href="#project-overview">Project Overview</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#hardware">Hardware</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#software">Software</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#operating-modes">Operating Modes</a>
    <br>
    <a href="#fsm-diagrams">FSM Diagrams</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#pin-mapping">Pin Mapping</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#risk-assessment">Risk Assessment</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#setup">Setup & Installation</a>
    <br>
    <a href="#user-controls">User Controls</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#datasheets">Datasheets</a> &nbsp;&nbsp;•&nbsp;&nbsp;
    <a href="#legal">Legal Disclosure</a>
  </p>
</div>

<br>
<br>

---

<br>

> ⚡ **SAFETY WARNING**
>
> **120VAC mains voltage is lethal.** The AC ground and neutral lines must **NEVER** be connected to the breadboard or STM32 DC ground.
> All AC wiring and the relay module must be secured inside a fully insulated, waterproof, non-conductive enclosure to prevent electrocution and short circuits.

<br>
<br>

---

<br>
<br>

<h2 align="center" id="project-overview">Project Overview</h2>
<br>

ZEUS is a fully automated, microcontroller-operated irrigation system that monitors soil moisture and activates a water pump during configurable evening windows — protecting plants from heat stress and leaf burn caused by improper or inconsistent manual watering.

<br>

The system continuously samples soil moisture throughout the day but only permits watering during a safe evening window, combining sensor intelligence with hardware-level safety mechanisms including an Independent Watchdog Timer, flood protection caps, and fail-safe relay initialization.

<br>
<br>

<h3 align="left">Author</h3>
<div align="center">
  <table align="center">
    <tr>
      <th align="left"><strong>Name</strong></th>
      <th align="left"><strong>Student ID</strong></th>
      <th align="left"><strong>Email</strong></th>
      <th align="left"><strong>Date</strong></th>
    </tr>
    <tr>
      <td align="center">Tom Goncin</td>
      <td align="center">2004 12666</td>
      <td align="center">tgj616@uregina.ca</td>
      <td align="center">April 9, 2026</td>
    </tr>
  </table>
</div>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="hardware">Hardware</h2>
<br>
<p align="center">All physical components integrated within the ZEUS system</p>

<br>

<div align="center">
  <table width="85%">
    <tr>
      <th align="center">Component</th>
      <th align="center">Part</th>
      <th align="center">Role in ZEUS</th>
    </tr>
    <tr>
      <td align="center"><strong>Microcontroller</strong></td>
      <td align="center">STM32F103RB (Nucleo-64)</td>
      <td align="center">Central CPU — bare-metal C firmware, ADC, GPIO, I2C</td>
    </tr>
    <tr>
      <td align="center"><strong>Soil Moisture Sensor</strong></td>
      <td align="center">SparkFun Analog Sensor</td>
      <td align="center">Measures volumetric water content via analog voltage</td>
    </tr>
    <tr>
      <td align="center"><strong>Power Relay</strong></td>
      <td align="center">Cubic Single-Pole 10A / Omron G5LE</td>
      <td align="center">Isolates high-voltage AC load; gates 24VAC transformer</td>
    </tr>
    <tr>
      <td align="center"><strong>LCD Display</strong></td>
      <td align="center">2004A I²C LCD (PCF8574 backpack)</td>
      <td align="center">Real-time status, ADC readings, and mode display</td>
    </tr>
    <tr>
      <td align="center"><strong>Transformer</strong></td>
      <td align="center">HeathZenith 24VAC Step-Down</td>
      <td align="center">Steps 120VAC → 24VAC to drive Rain Bird solenoid</td>
    </tr>
    <tr>
      <td align="center"><strong>Irrigation Valve</strong></td>
      <td align="center">Rain Bird ¾″ Inline Valve</td>
      <td align="center">Final actuator — solenoid opens valve to allow water flow</td>
    </tr>
    <tr>
      <td align="center"><strong>Enclosure</strong></td>
      <td align="center">NANUK Hard Case (IP67)</td>
      <td align="center">Fully waterproof & dustproof housing for outdoor use</td>
    </tr>
  </table>
</div>

<br>

> **Note on Sensor Corrosion Protection:** To prevent galvanic corrosion of the soil sensor probes, ZEUS only supplies power to the sensor for brief 10–20ms intervals during an active reading, then immediately cuts power via GPIO pin PB0.

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="software">Software Configuration</h2>
<br>

<h3 align="left">Development Environment</h3>

<div align="center">
  <table width="75%">
    <tr>
      <th align="center">Unit</th>
      <th align="center">Specification</th>
    </tr>
    <tr>
      <td align="center"><strong>IDE</strong></td>
      <td align="center">Keil MDK-ARM uVision6 (with inherited uVision5 tools)</td>
    </tr>
    <tr>
      <td align="center"><strong>Compiler</strong></td>
      <td align="center">ARM Compiler 5 (armcc) — bare-metal C; No HAL, RTOS, or CubeMX</td>
    </tr>
    <tr>
      <td align="center"><strong>Device Pack</strong></td>
      <td align="center">Keil.STM32F1xx_DFP — STM32F103RB device definition</td>
    </tr>
    <tr>
      <td align="center"><strong>Target Board</strong></td>
      <td align="center">STM32F103RB Nucleo-64</td>
    </tr>
    <tr>
      <td align="center"><strong>Language Standard</strong></td>
      <td align="center">C99</td>
    </tr>
    <tr>
      <td align="center"><strong>Tested On</strong></td>
      <td align="center">Windows 11 Pro</td>
    </tr>
  </table>
</div>

<br>
<br>

<h3 align="left">Project File Structure</h3>
<br>

```
ZEUS/
├── src/                          ← Source files
│   ├── main.c                    Central control loop, state machine, time tracking, relay decisions
│   ├── soilSensor.c              ADC1 init, switched-power sensor read
│   ├── lcd.c                     High-level LCD functions, I2C 4-bit nibble protocol
│   ├── timer.c                   TIM2 (us/ms delay), TIM3 (1s hardware tick), MCO output
│   ├── watchDogTimer.c           IWDG init (prescaler 256, reload 4095) and feed
│   ├── delay.c                   delay_us() and delay_ms() built on TIM2
│   ├── i2c.c                     Bare-metal I2C1 driver, register-level (PB6/PB7)
│   ├── relay.c                   I2C relay driver (addr 0x18), Relay_On() / Relay_Off()
│   └── buttons.c                 GPIO init, active-LOW priority read logic
│
└── Lib/                          ← Header files (all but main.c)
    ├── soilSensor.h
    ├── lcd.h
    ├── timer.h
    ├── watchDogTimer.h
    ├── delay.h
    ├── i2c.h
    ├── relay.h
    └── buttons.h
```

<br>
<br>

<h3 align="left">System Requirements</h3>
<br>

<div align="center">
  <table width="95%">
    <tr>
      <th align="center">ID</th>
      <th align="center">Requirement</th>
      <th align="center">Notes</th>
      <th align="center">Status</th>
    </tr>
    <tr>
      <td align="center"><strong>R1</strong></td>
      <td align="left">System samples soil moisture ADC at 16:00 and 18:00 daily</td>
      <td align="left">ADC1 CH0 — PA0 — 12-bit (0–4095)</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R2</strong></td>
      <td align="left">System powers soil sensor only during a 10–20ms reading window</td>
      <td align="left">PB0 GPIO controls sensor VCC; prevents galvanic corrosion</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R3</strong></td>
      <td align="left">System compares ADC reading against DRY_THRESHOLD and WET_THRESHOLD</td>
      <td align="left">Calibrated: 2300 & 3000 respectively. Hysteresis zone defined in main.c</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R4</strong></td>
      <td align="left">System activates relay in the evening window (20:30–20:59) only if watering flag is set</td>
      <td align="left">Relay I2C addr 0x18 (can be 0x30 if resistors soldered). Relay_On() / Relay_Off()</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R5</strong></td>
      <td align="left">System pump runtime capped at 300s (flood protection)</td>
      <td align="left">pump_run_time counter in main loop, hardcoded limit</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R6</strong></td>
      <td align="left">System resets all daily flags at 21:00:00</td>
      <td align="left">watering_required_tonight = false; pump_run_time = 0</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R7</strong></td>
      <td align="left">System tracks real-world time without accumulated drift</td>
      <td align="left">TIM3 hardware timer — 1 Hz tick, 72MHz / 7200 / 10000</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R8</strong></td>
      <td align="left">System displays real-time status on 20×4 I2C LCD across 4 modes</td>
      <td align="left">I2C addr 0x27, PCF8574 backpack, 4-bit mode</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R9</strong></td>
      <td align="left">System reads 4 GPIO buttons with priority logic BTN4 > BTN3 > BTN2 > BTN1</td>
      <td align="left">PB12–PB15. Active LOW, using internal pull-ups via ODR</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R10</strong></td>
      <td align="left">System recovers from software freeze via IWDG hardware watchdog</td>
      <td align="left">256 prescaler, 4095 reload → ~26.2s timeout</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R11</strong></td>
      <td align="left">System de-energizes relay on power-up (fail-safe OFF)</td>
      <td align="left">Relay_Init() sends 0x00 before main loop</td>
      <td align="center">✅ Pass</td>
    </tr>
    <tr>
      <td align="center"><strong>R12</strong></td>
      <td align="left">System supports 4 operating modes selectable by hardware buttons</td>
      <td align="left">Mode 1: Normal | Mode 2: VOID Time | Mode 3: Force ON | Mode 4: Force OFF</td>
      <td align="center">✅ Pass</td>
    </tr>
  </table>
</div>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="operating-modes">Operating Modes</h2>
<br>

<div align="center">
  <table width="90%">
    <tr>
      <th align="center">Mode</th>
      <th align="center">Name</th>
      <th align="center">Button</th>
      <th align="center">Behaviour</th>
      <th align="center">LCD Output</th>
    </tr>
    <tr>
      <td align="center"><strong>1</strong></td>
      <td align="center">Normal</td>
      <td align="center">BTN1 / Default</td>
      <td align="left">Full schedule + soil sensor logic. Relay fires at 20:30 only if soil was flagged dry at 16:00 or 18:00. Shuts off after 300s.</td>
      <td align="center"><code>"NORMAL MODE: Regular Operation"</code></td>
    </tr>
    <tr>
      <td align="center"><strong>2</strong></td>
      <td align="center">Day/Night VOID</td>
      <td align="center">BTN2</td>
      <td align="left">Ignores 24-hour clock entirely. Polls soil sensor in real-time. Relay triggers immediately when ADC drops below dry threshold. Raw ADC visible for calibration.</td>
      <td align="center"><code>"MODE: Day/Night VOID"</code> + raw ADC</td>
    </tr>
    <tr>
      <td align="center"><strong>3</strong></td>
      <td align="center">Manual / Force ON</td>
      <td align="center">BTN3</td>
      <td align="left">Overrides all sensor data and scheduling. Relay permanently energized — waters continuously until mode is changed.</td>
      <td align="center"><code>"MANUAL MODE: All Config VOID Watering..."</code></td>
    </tr>
    <tr>
      <td align="center"><strong>4</strong></td>
      <td align="center">Emergency / Force OFF</td>
      <td align="center">BTN4 ⚠️ Highest Priority</td>
      <td align="left">Safety override. Relay permanently de-energized regardless of all conditions. Acts as a software fuse — stays in this state until BTN1 is re-engaged.</td>
      <td align="center"><code>"SYSTEM DISABLED: FORCED OFF"</code></td>
    </tr>
  </table>
</div>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="fsm-diagrams">Finite State Machine Diagrams</h2>
<br>

<h3 align="left">7.1 — Button Priority FSM</h3>
<p>The exact priority chain evaluated every main loop iteration from <code>Buttons_Get_ACTIVE_Mode()</code>. Physical GPIO uses active-LOW logic with pull-up resistors enabled via ODR.</p>

<br>

<!-- Replace with your actual image once uploaded to GitHub -->
<p align="center">
  <img width="700" alt="Button FSM Diagram" src="https://github.com/user-attachments/assets/YOUR_BTN_FSM_IMAGE_HERE" />
</p>

<br>
<br>

<h3 align="left">7.2 — Complete System FSM</h3>
<p>Full runtime state machine. Dashed lines represent loop-back to the next main loop iteration.</p>

<br>

<!-- Replace with your actual image once uploaded to GitHub -->
<p align="center">
  <img width="700" alt="Complete ZEUS FSM Diagram" src="https://github.com/user-attachments/assets/YOUR_FULL_FSM_IMAGE_HERE" />
</p>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="pin-mapping">Pin Mapping</h2>
<br>
<p align="center">All DC ground lines are common. AC ground and neutral are <strong>never</strong> shared with the DC breadboard.</p>

<br>

<div align="center">
  <table width="95%">
    <tr>
      <th align="center">STM32 Pin</th>
      <th align="center">Connected To</th>
      <th align="center">Function</th>
    </tr>
    <tr><td align="center"><code>PA0</code></td><td align="center">Soil Sensor — SIG</td><td align="left">ADC1 CH0 — analog moisture reading (0V–3.0V)</td></tr>
    <tr><td align="center"><code>PB0</code></td><td align="center">Soil Sensor — VCC</td><td align="left">GPIO power switch — enables sensor for 10–20ms read window only</td></tr>
    <tr><td align="center"><code>PA6 (SDA)</code></td><td align="center">LCD SDA / Relay SDA</td><td align="left">I2C1 data line — shared bus for display and relay</td></tr>
    <tr><td align="center"><code>PA7 (SCL)</code></td><td align="center">LCD SCL / Relay SCL</td><td align="left">I2C1 clock line — shared bus for display and relay</td></tr>
    <tr><td align="center"><code>PB12</code></td><td align="center">BTN 1</td><td align="left">Mode 1 — Normal Operation (active LOW)</td></tr>
    <tr><td align="center"><code>PB13</code></td><td align="center">BTN 2</td><td align="left">Mode 2 — Day/Night VOID (active LOW)</td></tr>
    <tr><td align="center"><code>PB14</code></td><td align="center">BTN 3</td><td align="left">Mode 3 — Force ON (active LOW)</td></tr>
    <tr><td align="center"><code>PB15</code></td><td align="center">BTN 4</td><td align="left">Mode 4 — Emergency Force OFF (active LOW, highest priority)</td></tr>
    <tr><td align="center"><code>VCC 3.3V</code></td><td align="center">Relay VCC</td><td align="left">3.3VDC power supply to relay module</td></tr>
    <tr><td align="center"><code>VCC 5V</code></td><td align="center">Soil Sensor VCC</td><td align="left">5VDC supply (gated via PB0)</td></tr>
    <tr><td align="center"><code>GND</code></td><td align="center">All DC components</td><td align="left">Common DC ground — LCD, relay, sensor, buttons</td></tr>
    <tr><td align="center">Relay COM → NC</td><td align="center">24VAC Transformer (Hot wire only)</td><td align="left">AC Hot wire passes through relay to gate transformer power to solenoid</td></tr>
    <tr><td align="center">Transformer LOAD</td><td align="center">Rain Bird Solenoid</td><td align="left">24VAC activates solenoid to open inline irrigation valve</td></tr>
  </table>
</div>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="risk-assessment">Risk Assessment & Mitigation</h2>
<br>

<div align="center">
  <table width="90%">
    <tr>
      <th align="center">Task</th>
      <th align="center">Hazard</th>
      <th align="center">Mitigation Strategy</th>
    </tr>
    <tr>
      <td align="center"><strong>Outdoor Operation</strong></td>
      <td align="left">Water & electricity contact (rain, condensation, moisture). Shorting. Equipment damage.</td>
      <td align="left">IP67 NANUK hard case. Mounted vertically on wall inside a pressure-treated wooden box. Machined cable exit holes.</td>
    </tr>
    <tr>
      <td align="center"><strong>AC Wiring</strong></td>
      <td align="left">Electric shock. AC short circuit. 120VAC is potentially lethal. Blown breakers. Electrical fire.</td>
      <td align="left">All wires disconnected prior to any splicing. Only the AC Hot (Live) wire is routed through the relay's COM and NO terminals. AC Neutral and Ground remain continuous and untouched.</td>
    </tr>
    <tr>
      <td align="center"><strong>DC Microcontroller</strong></td>
      <td align="left">Equipment failure from shorting DC power to GND, or 5V into a 3.3V pin (destroys STM32).</td>
      <td align="left">AC wiring physically isolated from DC breadboard and STM32 ground at all times. Triple-checked pinouts against schematic before powering on.</td>
    </tr>
    <tr>
      <td align="center"><strong>Soil Sensor Corrosion</strong></td>
      <td align="left">Galvanic corrosion — continuous power to probes in damp soil causes rapid probe degradation.</td>
      <td align="left">Switched-power design via PB0. Sensor only powered for 10–20ms per reading, then immediately cut LOW.</td>
    </tr>
    <tr>
      <td align="center"><strong>Automated Watering</strong></td>
      <td align="left">Software glitch causing over-watering or flooding.</td>
      <td align="left">300s MAX runtime hardcoded in <code>main.c</code>. IWDG watchdog timer (~26.2s timeout) forces relay open if firmware freezes.</td>
    </tr>
  </table>
</div>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="setup">Local Setup & Installation</h2>
<br>

To build and flash ZEUS firmware onto an STM32F103RB Nucleo-64:

<br>

<ul style="margin-left: 40px;">
  <li><strong>Clone the repository:</strong><br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>git clone https://github.com/YOUR_USERNAME/ZEUS.git</code>
  </li>

  <br>

  <li><strong>Open the project in Keil MDK-ARM uVision6:</strong><br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Open the <code>.uvprojx</code> file located in the project root.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Ensure the <strong>Keil.STM32F1xx_DFP</strong> device pack is installed for the STM32F103RB target.
  </li>

  <br>

  <li><strong>Build the project:</strong><br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Press <code>F7</code> or navigate to <strong>Project → Build Target</strong>.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Compiled with ARM Compiler 5 (armcc) — no HAL, no RTOS.
  </li>

  <br>

  <li><strong>Flash to the Nucleo-64:</strong><br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Connect the STM32F103RB via USB (ST-Link on-board).<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Press <code>F8</code> or navigate to <strong>Flash → Download</strong> to flash firmware.
  </li>

  <br>

  <li><strong>Power the system:</strong><br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Connect the STM32 USB cable to a 5V USB wall adapter (minimum 5V supply) or external 5V source.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;LCD will illuminate on boot. System defaults to <strong>Mode 1 (Normal Operation)</strong>.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Default firmware time is <code>12:13:00</code> — no RTC hardware; time resets on each power cycle.
  </li>
</ul>

<br>

> **Note:** The IWDG watchdog begins counting immediately on boot. The main loop must feed the watchdog every iteration. If the watchdog is not fed within ~26.2 seconds, a hardware reset will occur automatically.

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="user-controls">User Controls & Normal Operation</h2>
<br>

<h3 align="left">Normal Operation Sequence</h3>

<div align="center">
  <table width="80%">
    <tr>
      <th align="center">Step</th>
      <th align="center">Time</th>
      <th align="center">Operation</th>
    </tr>
    <tr>
      <td align="center">1</td>
      <td align="center">Boot</td>
      <td align="left">All buttons off. System defaults to Mode 1. Relay initialises OFF (0x00).</td>
    </tr>
    <tr>
      <td align="center">2</td>
      <td align="center">16:00 & 18:00</td>
      <td align="left">Soil sensor powered for 20ms. ADC read. If ADC &lt; 2300, watering flag is set.</td>
    </tr>
    <tr>
      <td align="center">3</td>
      <td align="center">20:30</td>
      <td align="left">If watering flag is set, relay energizes and pump begins running.</td>
    </tr>
    <tr>
      <td align="center">4</td>
      <td align="center">20:30 + 300s</td>
      <td align="left">Flood protection triggers. Relay forced OFF. Watering flag cleared.</td>
    </tr>
    <tr>
      <td align="center">5</td>
      <td align="center">21:00:00</td>
      <td align="left">All flags and pump timer reset for the next day's cycle.</td>
    </tr>
    <tr>
      <td align="center">6</td>
      <td align="center">Any time</td>
      <td align="left">Toggle BTN3 (Force ON) to water immediately, BTN4 (Force OFF) to kill the system, or BTN2 (Void Time) for continuous real-time polling.</td>
    </tr>
  </table>
</div>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="datasheets">Device Datasheets</h2>
<br>
<p align="center">All component datasheets can be found in the <strong>Data Sheets</strong> folder of this repository.</p>

<br>

<div align="center">
  <table width="90%">
    <tr>
      <th align="center">Device</th>
      <th align="center">File</th>
    </tr>
    <tr>
      <td align="left"><strong>I2C LCD</strong></td>
      <td align="left">
        <code>I2C - CN0296D - DATASHEET.pdf</code><br>
        <code>I2C - CN0296D - Related document.pdf</code><br>
        <code>I2C - Slave Address.pdf</code>
      </td>
    </tr>
    <tr>
      <td align="left"><strong>Soil Moisture Sensor</strong></td>
      <td align="left">
        <code>Soil Moisture Sensor - SparkFun.pdf</code><br>
        <code>Soil Moisture Sensor Hookup Guide - SparkFun Learn.pdf</code>
      </td>
    </tr>
    <tr>
      <td align="left"><strong>Water Pump Relay (3V)</strong></td>
      <td align="left">
        <code>3V Relay - STUSB4500 DS_15801.pdf</code><br>
        <code>Relay Datasheet - 3V.pdf</code><br>
        <code>Qwiic Single Relay Hookup Guide - SparkFun Learn.pdf</code>
      </td>
    </tr>
    <tr>
      <td align="left"><strong>24VAC Transformer</strong></td>
      <td align="left"><code>24VAC TRANSFORMER - HeathZenith.pdf</code></td>
    </tr>
    <tr>
      <td align="left"><strong>Rain Bird ¾″ Inline Valve</strong></td>
      <td align="left">
        <code>Rain Bird - Valve Manual.pdf</code><br>
        <code>Rain Bird - Product Brochure.pdf</code><br>
        <code>Rain Bird - Installation Guide.pdf</code>
      </td>
    </tr>
    <tr>
      <td align="left"><strong>STM32F103RB Nucleo-64</strong></td>
      <td align="left">
        <code>STM32F103 - Data Sheet.pdf</code><br>
        <code>STM32F103 - Reference Manual.pdf</code><br>
        <code>STM32F103 - Nucleo-64 - User Manual.pdf</code><br>
        <code>STM32F103 - Nucleo-64 - Schematic.pdf</code><br>
        <code>STM32F103 - Cortex-M3 - Programming Manual.pdf</code><br>
        <code>STM32F103RB - Errata.pdf</code><br>
        <code>STM32F103RB - Pinout.pdf</code><br>
        <code>STM32 - Manual Clock Tree.pdf</code><br>
        <code>F103 Pin Functions.pdf</code>
      </td>
    </tr>
  </table>
</div>

<br>
<br>
<br>

---

<br>
<br>

<h2 align="center" id="legal">Legal Disclosure & Limitation of Liability</h2>
<br>

**ZEUS Irrigation Controller | Open-Source Hardware & Firmware Design**<br>
Copyright © 2026 Tom Goncin. Released freely for educational and personal use.

<br>

This design is provided strictly **"as-is"** without warranties of any kind — expressed, implied, statutory, or otherwise. The author disclaims all implied warranties including merchantability, fitness for a particular purpose, accuracy, completeness, and non-infringement.

<br>

**The author shall not be liable for:** personal injury or death resulting from electrical shock; property damage from improper wiring or short circuits; vegetation or flooding damage from software faults or misconfiguration; or any equipment damage including the microcontroller, sensors, relay, or irrigation valves.

<br>

> ⚡ **HIGH VOLTAGE WARNING:** This design involves 120VAC mains voltage. Any person who constructs, modifies, or operates this design assumes full and sole responsibility for compliance with all applicable electrical codes, safety standards, and local regulations. **The author strongly recommends that all AC wiring be performed or inspected by a licensed electrician.**

<br>

By downloading, building, or deploying this design, you acknowledge that you are solely responsible for verifying suitability, independently verifying all wiring and pinouts, and assuming all risks associated with high-voltage AC power and automated irrigation systems. This design is intended for **personal and educational use only**.

<br>

Redistribution and derivative works are permitted provided this disclaimer is preserved in full. **Commercial use requires prior written consent from the author.**

<br>

*Full legal disclosure is available in the* [`LEGAL.md`](LEGAL.md) *file.*

<br>
<br>

---

<p align="right"><a href="#zeus--soil-moisture-retention-system"><strong>Back to top ↑</strong></a></p>