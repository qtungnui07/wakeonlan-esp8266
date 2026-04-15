## Installation & Setup


https://github.com/user-attachments/assets/f473091c-4947-4ede-9f12-f1582e8a29d7


To upload this code to your ESP8266, please follow these instructions:

1. **Software Requirement**: Download and install the [Arduino IDE](https://www.arduino.cc/en/software/).
![Arduino IDE](/assets/img/firefox_Zflg5k6l2e.png)
2. **Board Support**: Open Arduino IDE, go to `File > Preferences`, and add the following URL to **Additional Boards Manager URLs**:  
   `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
![Arduino IDE](/assets/img/image1.png)
3. **Install Board**: Go to `Tools > Board > Boards Manager`, search for **esp8266**, and click **Install**.
![Arduino IDE](/assets/img/image2.png)
4. **Install Libraries**: Open the Library Manager (`Ctrl + Shift + I`) and install:
   * **Esp8266-Pinger** (by AlessioLenci)
   * **WakeOnLan** (by a7md0)
![Arduino IDE](/assets/img/image.png)
5. **Preparation**: Copy all code from `main.cpp` and paste it into a new sketch in the Arduino IDE.

> [!WARNING]
> **Important:** Don't forget to update the code with your own network credentials and PC information before flashing!

Update these lines in your code:

```cpp
const char* ssid = "ten wifi";           // Replace with your WiFi Name
const char* password = "pass wifi";       // Replace with your WiFi Password
const char* pcIP = "ip pc";               // Your PC's local IP (e.g., 192.168.1.50)
const char* pcMac = "mac cua LAN/wifi";   // Your PC's MAC address (e.g., AA:BB:CC:DD:EE:FF)
```
6. **Configuration**:
   * Select your board: `Tools > Board > NodeMCU 1.0 (ESP-12E Module)`.
   * Select the correct **Port** for your ESP8266. 
   * (If it doesnt show up, please install the **CH340 driver**).
![Arduino IDE](/assets/img/image3.png)
7. **Flash**: Click **Verify** and then **Upload**.
8. **Monitor & Test**:
   * Once complete, replug the device or open the **Serial Monitor**.
   * Set the **baud rate** to **115200**.
   * Press the **RESET** button on your ESP8266 once to get the IP address displayed on the monitor.

**Enjoy!**
