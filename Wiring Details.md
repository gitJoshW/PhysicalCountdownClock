# Wiring Details

## Display to ESP32
* VCC -> 3.3V
* GND -> GND
* CS -> 15
* RESET -> EN
* DC -> 2
* SDI/MOSI -> 13
* SCK -> 14
* LED -> 23
* SDO/MOSI -> 12

*When using touchscreen, also need*
* T_CLK -> 25
* T_CS -> 33
* T_DIN -> 32
* T_DO -> 34
* T_IRQ -> 35

## RTC to ESP32
* GND -> GND
* VCC -> 3.3V
* SDA -> 21
* SCL -> 22
* SQW -> 4

