# ESP32 Wi-Fi Sniffer

## Project Title

**Implementation of a Wi-Fi Sniffer Device Driver using ESP32 and ESP-IDF**

## Problem Statement and Introduction

The objective of this project is to develop a simple device driver on the ESP32 microcontroller that can capture and display nearby Wi-Fi packets without connecting to any specific network. By configuring the ESP32 into promiscuous mode, the device can receive all Wi-Fi packets broadcasted in its vicinity. This allows us to extract and present key information such as MAC addresses, signal strength, and SSID (when available), providing insights into the local wireless environment. This project demonstrates device driver development and how operating systems communicate directly with hardware.

## Implementation Steps

1. **Download and Set Up ESP-IDF**  
   Download the ESP-IDF framework and all required tools. Set up the environment by running `./install.sh` and `. ./export.sh` in the ESP-IDF directory.

2. **Project Organization**  
   Create a `wifisniffer` project folder inside the ESP-IDF directory. Add a `main` folder and place `hello_world_main.c` in it.

3. **Configure Build System**  
   Register your source file and dependencies in `main/CMakeLists.txt` with:
   ```cmake
   idf_component_register(SRCS "hello_world_main.c"
                         INCLUDE_DIRS "."
                         REQUIRES esp_wifi esp_event nvs_flash esp_timer)
   ```

4. **Write and Implement Sniffer Code**  
   In `hello_world_main.c`, initialize Wi-Fi in promiscuous mode, register a packet handler to process incoming packets, and print relevant packet information (MAC, RSSI, SSID, etc.) to the console.

5. **Build, Flash, and Monitor**  
   In your project folder, run:
   - `idf.py build` (to compile)
   - `idf.py flash` (to upload to ESP32)
   - `idf.py monitor` (to view the output)

## Packet Processing and Filtering

- The code processes only the necessary information from each packet for clarity.
- Special attention is given to Beacon and Probe Response frames to extract SSID information when available.

## Output and Demonstration

- Packet details are printed to the serial console in a readable format.
- A channel-hopping mechanism is implemented to scan all Wi-Fi channels, increasing coverage and diversity.
- The demonstration shows real-time packet capture as the ESP32 cycles through channels.

