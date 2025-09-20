# Wi-Fi Packet Sniffer using ESP32 and FreeRTOS

This project implements a **Wi-Fi packet sniffer** on the **ESP32** microcontroller using the **ESP-IDF framework**.  
It captures Wi-Fi packets in **promiscuous mode**, parses metadata such as RSSI, MAC addresses, SSID, and frame types, and performs **automatic channel hopping** to scan across all 2.4 GHz Wi-Fi channels.  

---

## 🛠️ Requirements

- **ESP32 Development Board** (e.g., ESP32-DevKitC, NodeMCU-ESP32, etc.)
- **USB Cable** to connect ESP32 to PC
- **VS Code** with the following:
  - [ESP-IDF Extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension) installed
  - [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) installed
- **ESP-IDF Toolchain** properly set up on your system
  - [ESP-IDF Setup Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
- Serial Monitor (VS Code, `idf.py monitor`, or any terminal program)

---

## 📂 Project Setup

1. **Clone or create a new ESP-IDF project**:
   ```bash
   idf.py create-project wifi_sniffer
   cd wifi_sniffer
   ```

2. **Replace `main/main.c` with the provided code** (your Wi-Fi sniffer code).

3. **Ensure `CMakeLists.txt` includes required components**:

   ```cmake
   idf_component_register(SRCS "main.c"
                          INCLUDE_DIRS ".")
   ```

4. **Build the project**:

   ```bash
   idf.py build
   ```

---

## 🔌 Flash and Run

1. **Connect your ESP32** board via USB.

2. **Flash the firmware**:

   ```bash
   idf.py -p <PORT> flash
   ```

   Replace `<PORT>` with the actual serial port (e.g., `COM3` on Windows or `/dev/ttyUSB0` on Linux).

3. **Open the Serial Monitor**:

   ```bash
   idf.py -p <PORT> monitor
   ```

   (Press `Ctrl+]` to exit.)

---

## 📡 Expected Output

Once flashed and running, the ESP32 will:

* Enable Wi-Fi in **promiscuous mode**

* Print detected packet details every 1 second:

  * **Channel number**
  * **RSSI (signal strength)**
  * **Packet Type** (Beacon, Probe Request, Probe Response, Data, etc.)
  * **Source and Destination MAC addresses**
  * **SSID** (if available, otherwise `(Hidden)`)

* Automatically **switch channels every 2 seconds**, cycling through channels **1–13**.

Example Output:

```
--- Switching to Channel 6 ---
---------------------------------
Channel: 6
RSSI: -55 dBm
Packet Type: Beacon
Source MAC: 34:45:12:ab:cd:ef
Destination MAC: ff:ff:ff:ff:ff:ff
SSID: MyHomeWiFi
```

---

## ⚠️ Notes

* This code **does not connect** to any Wi-Fi network; it only **listens** to packets in the air.
* Works only in countries where **monitoring Wi-Fi is legal**. Use responsibly.
* SSIDs may appear as **(Hidden)** if the network has disabled broadcasting.
* RSSI values are negative (closer to 0 means stronger signal).

---

## 📚 References

* [ESP-IDF Wi-Fi Sniffer Example](https://github.com/espressif/esp-idf/tree/master/examples/wifi/sniffer)
* [FreeRTOS API Reference](https://www.freertos.org/a00106.html)
* [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)

---

# Author

Devloped by Vidit Goyal

---