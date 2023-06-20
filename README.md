this repository is provide vibration detector using esp32, mpu9250, sw420, piezoelectric

# ESP32-U
Using ESP32-U Board with 38 pin that used to read button select mode, read button enter mode, read sensor sw-420, read sensor piezoelectric, read sensor module vibration, read GPS module NEO 6m, output to OLED 0.96 inch

# Pinout
ESP32-PIN |    SENSOR    |    PIN    |    VCC    |
--------- |  ---------   | --------- |-----------|
13        | SW420        |DIGITAL OUT|   5V      |
16        | GPS NEO 6M   |     TX    |   3.3V    |
17        | GPS NEO 6M   |     RX    |   3.3V    |
18        | BTN ENTER    |    OUT    |   5V      |
19        | BTN ENTER    |    OUT    |   5V      |
21        | OLED         |    SDA    |   3.3V    |
22        | OLED         |    SCL    |   3.3V    |
21        | MPU9250      |    SDA    |   3.3V    |
22        | MPU9250      |    SCL    |   3.3V    |
23        | PIEZOE       |    OUT    |   ----    |
32        | VIB MODULE   | ANALOG OUT|   5V      |
33        | VIB MODULE   |DIGITAL OUT|   5V      |

# Board
![Alt text](https://github.com/cisea-dev/vibration-detector/blob/main/BOARD.png "Optional title")
![](https://github.com/cisea-dev/vibration-detector/blob/main/BOARD-2.png)

# Schematic

