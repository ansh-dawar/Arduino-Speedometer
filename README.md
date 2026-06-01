# Arduino-Speedometer
# ⚡ Arduino Digital Speedometer

A real-time digital speedometer built using **Arduino UNO** that measures the speed of any moving object passing between two IR sensors and instantly displays the result in **km/h** on a 16x2 I2C LCD display — with microsecond precision timing.

> Built as a fully working hardware prototype. Tested by passing a hand/object between the two sensors placed 2cm apart.

---

## 📽️ Demo Video

<!-- Upload your video via GitHub Issues and paste the link below -->
<!--  -->

> 🎥 _Add your demo video here using the GitHub Issues upload trick_

---

## ⚙️ How It Works

1. On startup, LCD displays **"Speed Gun"** for 1 second
2. LCD switches to **"Scanning..."** — system is now ready and waiting
3. Object/hand passes Sensor 1 (IR) → Arduino records `startTime` using `micros()`
4. Same object reaches Sensor 2 (IR) → Arduino records `stopTime` using `micros()`
5. Time difference is calculated in microseconds
6. Speed is computed using the formula:

```
Speed (km/h) = (Distance in meters / Time in seconds) × 3.6
             = (0.02 / (timeDiff / 1000000)) × 3.6
```

7. LCD displays: **"Speed: 2.30 km/h"**
8. After 1 second, LCD resets back to **"Scanning..."** — ready for next reading
9. Invalid readings (too fast or too slow) are filtered and shown as **"Invalid"**

---

## 🖼️ Project Preview

| State | LCD Display | Description |
|-------|------------|-------------|
| Startup | `Speed Gun` | Initialisation message for 1 second |
| Idle / Ready | `Scanning...` | Waiting for object at Sensor 1 |
| Object detected | `Speed:` `2.30 km/h` | Real-time speed displayed |
| Object detected | `Speed:` `2.65 km/h` | Different speed reading |
| Bad reading | `Invalid` | Filtered — object too fast or too slow |
| After reading | `Scanning...` | Reset and ready for next measurement |

---

## 🛠️ Components Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino UNO | 1 | Main microcontroller |
| IR Sensor Module (HW-201) | 2 | Detect object at start and end points |
| 16x2 I2C LCD Display | 1 | Display speed and status in real time |
| Breadboard | 1 | Circuit connections |
| Jumper Wires | Multiple | Wiring |
| USB Cable | 1 | Power and programming |

---

## 🔌 Circuit Connections

```
IR Sensor 1 (Start)   → Arduino Digital Pin 2
IR Sensor 2 (End)     → Arduino Digital Pin 3
LCD SDA               → Arduino A4
LCD SCL               → Arduino A5
VCC (Sensors + LCD)   → 5V
GND                   → GND
```

> Note: This project uses an **I2C LCD** (not a standard parallel LCD).
> The LCD communicates via only 2 wires (SDA + SCL) using the I2C protocol.

---

## 📐 Speed Calculation Logic

The two IR sensors are placed exactly **2 cm (0.02 m)** apart.

When an object passes:
- `startTime` is captured at Sensor 1 using `micros()` (microsecond precision)
- `stopTime` is captured at Sensor 2 using `micros()`
- Time difference `diff = stopTime - startTime` (in microseconds)

```cpp
float speed = (distanceBetweenSensors / (diff / 1000000.0)) * 3.6;
// distanceBetweenSensors = 0.02 metres
// diff / 1000000.0 converts microseconds → seconds
// × 3.6 converts m/s → km/h
```

**Invalid reading filter:**
```cpp
if (diff < 500 || diff > 300000) {
    lcd.print("Invalid");  // Object too fast (<500µs) or too slow (>300000µs)
}
```

---

## 💻 Libraries Required

| Library | Purpose | Install via |
|---------|---------|-------------|
| `Wire.h` | I2C communication | Built-in with Arduino IDE |
| `hd44780.h` | I2C LCD control | Arduino Library Manager |
| `hd44780ioClass/hd44780_I2Cexp.h` | I2C expander support | Part of hd44780 library |

---

## 🚀 How to Run

1. **Clone this repository**
   ```bash
   git clone https://github.com/your-username/arduino-speedometer.git
   ```

2. **Install hd44780 Library**
   - Open Arduino IDE
   - Go to **Tools → Manage Libraries**
   - Search **"hd44780"** by Bill Perry
   - Click **Install**

3. **Open the code**
   - Open `speedometer.ino` in Arduino IDE

4. **Connect the hardware**
   - Follow the circuit connections table above
   - Place the two IR sensors exactly **2 cm apart**

5. **Upload the code**
   - Select board: **Arduino UNO**
   - Select correct COM port
   - Click **Upload**

6. **Test it**
   - Wait for **"Scanning..."** on LCD
   - Pass your hand quickly between the two sensors
   - Speed will display instantly in km/h

---

## ✨ Features

- ✅ Microsecond precision timing using `micros()` for accurate speed measurement
- ✅ Real-time speed display in **km/h** on I2C LCD
- ✅ Startup splash screen — **"Speed Gun"**
- ✅ Idle state display — **"Scanning..."** while waiting
- ✅ Automatic reset after each reading — ready for next measurement
- ✅ **Invalid reading filter** — rejects impossibly fast or slow values
- ✅ I2C LCD interface — minimal wiring (only 2 data wires)
- ✅ Fully working physical prototype

---

## 📁 Project Structure

```
arduino-speedometer/
│
├── speedometer.ino        # Main Arduino code
├── circuit_diagram.png    # Circuit connection diagram
├── demo_video.mp4         # Working demo
└── README.md              # Project documentation
```

---

## 🔮 Future Improvements

- Scale sensor distance to measure real vehicle speeds on roads
- Add overspeed alert using buzzer when speed exceeds a threshold
- Log speed readings to SD card for data analysis
- Wireless speed reporting via Bluetooth or Wi-Fi to mobile app
- Add multiple lanes with separate sensor pairs

---

## 👨‍💻 Author

**Shivansh Dawar**
B.Tech CSE (IoT) — Raj Kumar Goel Institute of Technology, Ghaziabad
📧 anshdawar1506@gmail.com
🔗 [LinkedIn](https://linkedin.com/in/shivansh-dawar)
🐙 [GitHub](https://github.com/ansh-dawar)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
