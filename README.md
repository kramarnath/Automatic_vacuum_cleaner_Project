# Automatic_vacuum_cleaner_Project
Final year project : Automatic Vacuum Cleaner using Arduino Uno and sensors.

An autonomous vacuum cleaning robot built using **Arduino UNO**, **ultrasonic sensors**, **IR floor detection**, and an **L298N motor driver**.  
The robot detects obstacles, avoids edges, and navigates the floor automatically.

---

## 🚀 Features
- Autonomous forward movement
- Obstacle detection using 3 ultrasonic sensors (Left, Front, Right)
- Floor-edge detection using IR sensor (prevents falling from stairs)
- Smart turning based on sensor logic
- Memory flag to avoid forward-backward loop
- Uses L298N motor driver to control two DC motors

---

## 🧰 Components Used
- Arduino UNO  
- Ultrasonic Sensors (HC-SR04) × 3  
- IR Floor/Cliff Detection Sensor × 1  
- L298N Motor Driver  
- DC Motors × 2  
- Chassis + Wheels  
- Battery Pack  
- Jumper Wires  

---

## ⚙️ Working Principle
### 1. **Ultrasonic Sensors**
- Measure distance in front, left, and right.
- Safe distance is set to **15 cm**.
- Robot turns left or right when an obstacle is detected.

### 2. **IR Floor Sensor**
- Detects whether the robot is on solid floor.
- If the floor is missing (edge detected), robot reverses and then turns.

### 3. **Motor Control**
Based on sensor readings:
- **Forward** when no obstacle and floor is present.
- **Right Turn** if left obstacle is detected.
- **Left Turn** when right/front obstacle is detected.
- **Reverse** when floor is missing.

A memory variable (`a`) prevents the robot from getting stuck in a loop when reversing near edges.
## 🔧 Arduino Pin Configuration

### **Ultrasonic Sensors**
| Sensor | Trigger Pin | Echo Pin |
|--------|-------------|----------|
| Left   | 3           | 5        |
| Front  | 6           | 9        |
| Right  | 10          | 11       |

### **IR Floor Sensor**
`IR Pin → 2`

### **Motor Driver (L298N)**
| Function | Arduino Pin |
|----------|-------------|
| Motor1 IN1 | 4 |
| Motor1 IN2 | 7 |
| Motor2 IN1 | 8 |
| Motor2 IN2 | 12 |

---

## 📁 Project Structure
