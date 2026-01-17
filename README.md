# Physical Countdown Clock

Wanted to have a visual display for the family to see how long until our next vacation. Leveraged a combination of ChatGPT and online tutorials, especially quite a few from https://randomnerdtutorials.com/ to get this working. I had to modify one of the .h files that I downloaded to allow for the right pin access between all the parts.

<img width="729" height="968" alt="image" src="https://github.com/user-attachments/assets/d67fd0ac-2847-4468-87c2-2105d9f7ad7c" />

## Parts: 
* ESP32-DevKitC-32E from Espressif
* Hosyond 2.4 Inches TFT LCD Touch Screen Shield Display Module 320x240 SPI Serial ILI9341 with Touch Pen Compatible with Arduino R3/Mega2560 Development Board
* 2PCS DS3231 AT24C32 IIC RTC Module Clock Timer Memory Module Beats Replace DS1307 I2C RTC Board with Male to Female Jumper Wire Cable
* Breadboard - get everything working first

The RTC is to ensure the time is maintained when it isn't connected to power

## Next Steps:
### Hardware
* Convert from breadboard to perfboard so it will fit into a smaller enclosure
* Buy or make enclosure
* Add an on/off switch
* Consider the combined ESP32 & TouchScreen for a slimmer overall profile (the combined ones I've found don't seem to give you full pin access to the ESP32, so not sure how to wire the RTC in)

### Software
* Add additional background images that rotate every so often
* Better font
* Leverage the touchscreen interface to allow a user to set a new event or set the current time (currently the only way to reset the current time would be to reconnect it to the computer and recompile the program)
* Consider using batter power instead of needing to be plugged in?
