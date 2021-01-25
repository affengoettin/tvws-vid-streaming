# tvws-vid-streaming
Used in conjunction with the appropriate hardware to stream video over TV wavelengths.


Currently streaming video over paired transceivers and saving hex-encoded bytes to a text file for manual reconstruction into a .ts file by the recipient computer. Working on building a simple Django server to which the data can be forwarded and displayed in a browser setting. After that proof-of-concept is completed, I plan to purchase the necessary hardware to increase the bitrate.

Hardware specs:

TX = Computer + Arduino Uno + RobotShop 433MHz transceiver module (UART communication)
RX = 433Mhz transceiver module + ESP32 (UART) + WiFi connection

Notes:
- The Uno is severely limiting the baud rate, but it's all I have available until I'm able to purchase a more efficient USB-UART cable.
