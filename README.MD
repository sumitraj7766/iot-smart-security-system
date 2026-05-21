# IoT Smart Security System using NodeMCU

An IoT-based smart security and home automation project built with **NodeMCU ESP8266**, **PIR Motion Sensor**, **IR Object Detection Sensor**, and **Firebase Realtime Database** integration.

## 🎯 Features

✅ **Motion Detection** - PIR sensor detects movement and triggers LED  
✅ **Object Detection** - IR sensor identifies obstacles or intrusions  
✅ **LED Automation** - Automatic LED control based on motion  
✅ **Local Web Dashboard** - Real-time status via NodeMCU IP address  
✅ **Firebase Integration** - Cloud database sync every 2 seconds  
✅ **Automatic Door Lock** - Simulated door open/close based on motion  
✅ **Web-based Monitoring** - View all sensor data from any browser  




## 🔧 Hardware Components

| Component | Quantity | Purpose |
|-----------|----------|---------|
| NodeMCU ESP8266 | 1 | Microcontroller |
| PIR Motion Sensor | 1 | Motion detection |
| IR Sensor Module | 1 | Object detection |
| LED (5mm) | 1 | Visual indicator |
| Resistor (220Ω) | 1 | LED protection |
| Jumper Wires | As needed | Connections |
| Breadboard | 1 | Prototyping |
| USB Cable | 1 | Uploading code |

## 🔌 Circuit Connections

```
┌─────────────────────────────────────────┐
│          NodeMCU ESP8266                │
├─────────────────────────────────────────┤
│                                         │
│  PIR Sensor OUT  ─────► D5              │
│  IR Sensor OUT   ─────► D6              │
│  LED Anode       ─────► D1 (via 220Ω)  │
│  LED Cathode     ─────► GND             │
│                                         │
└─────────────────────────────────────────┘
```

| Component | NodeMCU Pin | Logic |
|-----------|------------|-------|
| PIR Sensor OUT | D5 | HIGH = Motion Detected |
| IR Sensor OUT | D6 | LOW = Object Detected |
| LED + | D1 | HIGH = LED ON |
| GND | GND | Ground reference |

## 📱 How It Works

```
Sensor Input
    ↓
NodeMCU Processing
    ↓
┌─────────────────────────────────────┐
├─ Local Web Dashboard (192.168.x.x)  │
├─ Firebase Realtime Database         │
└─────────────────────────────────────┘
    ↓
Real-time Status Update
```

### Workflow:
1. **PIR detects motion** → LED turns ON → Door OPENS → Firebase updates
2. **No motion detected** → LED turns OFF → Door CLOSES → Firebase updates
3. **IR detects object** → Status shows "Object Detected" → Firebase updates
4. **Updates happen every 2 seconds** via Firebase PUT request

## ⚡ Installation & Setup

### Prerequisites
- Arduino IDE installed
- NodeMCU drivers installed
- Firebase Realtime Database account
- WiFi network access

### Step 1: Install Arduino IDE Libraries
```
1. Open Arduino IDE
2. Go to Sketch → Include Library → Manage Libraries
3. Search and install:
   - ESP8266 by ESP8266 Community
   - (Built-in: WiFi, WebServer, HTTPClient)
```

### Step 2: Configure WiFi & Firebase
Edit `smart_security.ino`:
```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
String firebaseURL = "https://your-firebase-rtdb.firebaseio.com/smart_security.json";
```

### Step 3: Setup Firebase Rules
Go to Firebase Console → Database Rules:
```json
{
  "rules": {
    "smart_security": {
      ".write": true,
      ".read": true
    }
  }
}
```
⚠️ *For production, use proper authentication rules!*

### Step 4: Upload Code
```
1. Connect NodeMCU via USB
2. Select Board: Tools → Board → NodeMCU 1.0
3. Select Port: Tools → Port → COM# (or /dev/ttyUSB0)
4. Upload: Ctrl + U
```

### Step 5: Monitor Serial Output
```
1. Open Serial Monitor: Ctrl + Shift + M
2. Baud Rate: 115200
3. You'll see:
   - WiFi connection status
   - IP Address (http://192.168.x.x)
   - Firebase update responses
```

## 📊 Web Dashboard

Once uploaded, open your browser and visit:
```
http://192.168.x.x
```

The dashboard displays:
- **Motion Status** - Motion Detected / No Motion
- **Object Status** - Object Detected / Clear
- **LED Status** - ON / OFF
- **Door Status** - OPEN / CLOSED

*Auto-refreshes every 2 seconds*

## 📡 Firebase Data Structure

Your data will be stored as:
```json
{
  "smart_security": {
    "motion": "Motion Detected",
    "object": "Clear",
    "led": "ON",
    "door": "OPEN"
  }
}
```

## 🚀 Future Enhancements

- [ ] **Servo Motor** - Automated door lock mechanism
- [ ] **Buzzer Alarm** - Sound alert on motion detection
- [ ] **Push Notifications** - Mobile alerts via Firebase Cloud Messaging
- [ ] **Telegram Bot** - Real-time alerts to Telegram
- [ ] **Mobile App** - Flutter/React Native app for remote monitoring
- [ ] **ESP32-CAM** - Add camera for security footage
- [ ] **MQTT Integration** - Home Assistant compatibility
- [ ] **Cloud Dashboard** - Web-based real-time monitoring
- [ ] **Machine Learning** - Advanced threat detection

## 📸 Project Screenshots

- `images/circuit.jpg` - Circuit diagram and connections
- `images/firebase.png` - Firebase console screenshot
- `images/dashboard.png` - Web dashboard screenshot

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| WiFi not connecting | Check SSID/password, ensure 2.4GHz network |
| Firebase not updating | Verify Firebase URL, check internet connection |
| LED not turning on | Check LED polarity and resistor connection |
| Serial monitor shows garbage | Set Baud Rate to 115200 |
| IP address not visible | Restart NodeMCU and check serial monitor |

## 📝 Pin Configuration Reference

```cpp
#define PIR_PIN D5    // GPIO14 - Motion Sensor
#define IR_PIN D6     // GPIO12 - Object Sensor
#define LED_PIN D1    // GPIO5  - LED Control
```

## 🔐 Security Notes

⚠️ **Important Security Tips:**
1. **Never upload WiFi credentials to GitHub** - Use environment variables or Firebase remote config
2. **Use Firebase rules** - Don't allow public write access in production
3. **Implement authentication** - Add email/password verification
4. **Change default ports** - Consider non-standard ports for production
5. **Use HTTPS** - All Firebase connections are secure

## 📚 References & Resources

- [Arduino IDE Documentation](https://docs.arduino.cc/)
- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
- [Firebase Realtime Database](https://firebase.google.com/docs/database)
- [PIR Sensor Guide](https://www.electronics-tutorials.ws/io/io_5.html)
- [IR Sensor Module Guide](https://lastminuteengineers.com/ir-sensor-arduino-tutorial/)

## 📧 Author

**sumit kumar**  
Email: sk681172112209@gmail.com 
GitHub: [@YourUsername](https://github.com/YourUsername)

## 📄 License

This project is open-source and available under the .

## ⭐ Support

If you found this project helpful, please give it a ⭐ on GitHub!

---

**Last Updated:** May 2026  
**Version:** 1.0.0  
**Status:** Active Development
