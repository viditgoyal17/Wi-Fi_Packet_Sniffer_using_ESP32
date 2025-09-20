# ESP32 Wi-Fi Sniffer

## Project Overview
This project implements a simple Wi-Fi **packet sniffer** on the ESP32 using the **ESP-IDF** framework.  
By enabling promiscuous mode, the ESP32 can capture all nearby Wi-Fi packets without joining any specific network. The application extracts and prints useful details such as:

- **MAC Address** of the sender
- **RSSI (signal strength)**
- **SSID** (when available, e.g., in Beacon or Probe Response frames)

This project demonstrates how a device driver interacts with hardware at the operating system level and provides insight into low-level wireless communication.

⚠️ **Disclaimer:** This project is intended only for educational and authorized research purposes. Please follow your local regulations regarding wireless monitoring.

---

## Features
- Runs on any ESP32 development board.
- Captures Wi-Fi packets in promiscuous mode.
- Extracts MAC addresses, RSSI, and SSIDs from packets.
- Implements channel-hopping for wider packet capture.
- Prints packet data in real-time to the serial console.

---

## Repository Structure

```

Wifi\_Sniffer\_Code/
├── CMakeLists.txt        # Root build file
├── sdkconfig.defaults    # Default project configuration
├── main/
│   ├── CMakeLists.txt    # Build file for app sources
│   └── main.c            # Application source code
├── components/           # (Optional) Custom components if needed
└── README.md             # Project documentation

````

---

## Getting Started

### Prerequisites
1. **ESP-IDF Framework**  
   Install ESP-IDF by following the official guide:  
   [ESP-IDF Get Started](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)

2. **Hardware**  
   - ESP32 Development board  
   - USB cable  

---

### Setup Instructions

1. **Clone the repository**

```bash
git clone https://github.com/<your-username>/Wi-Fi_Packet_Sniffer.git
cd Wi-Fi_Packet_Sniffer
````

2. **Set up ESP-IDF environment**

```bash
. $HOME/esp/esp-idf/export.sh
```

3. **Select target**

```bash
idf.py set-target esp32
```

4. **Apply default configuration**

```bash
idf.py defconfig
```

5. **Build the project**

```bash
idf.py build
```

6. **Flash to ESP32**

```bash
idf.py -p /dev/ttyUSB0 flash
```

7. **Monitor output**

```bash
idf.py -p /dev/ttyUSB0 monitor
```

> Replace `/dev/ttyUSB0` with the correct port on your system (e.g., `COM3` on Windows).

---

## Expected Output

Once flashed and running, the ESP32 will print captured Wi-Fi packet information like:

```
Packet captured:
  MAC: 3C:71:BF:AA:22:11
  RSSI: -55 dBm
  SSID: MyWiFiNetwork
```

The output updates continuously as packets are detected. With channel-hopping enabled, you’ll see packets across multiple Wi-Fi channels.

---

## Customization

* Adjust **channel-hopping interval** in `main.c` to control how often channels change.
* Filter packet types (Beacon, Probe Request, etc.) inside the packet handler function.
* Extend code to log packets to storage (e.g., SPIFFS, SD card) instead of just printing.

---

## Troubleshooting

* **Upload failure**

  * Check correct COM port or USB device.
  * Try reducing baud rate in `menuconfig`.

* **No packets seen**

  * Ensure there are Wi-Fi networks nearby.
  * Confirm the ESP32 is in promiscuous mode.
  * Try moving closer to an access point.

---

## License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

---

## Author

Developed by **Vidit Goyal**