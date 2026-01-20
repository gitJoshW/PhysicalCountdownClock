# Physical Countdown Clock

Wanted to have a visual display for the family to see how long until our next vacation. Leveraged a combination of ChatGPT and online tutorials, especially quite a few from https://randomnerdtutorials.com/ to get this working. I had to modify one of the .h files that I downloaded (User_Setup.h [in TFT_eSPI folder] from Random Nerd Tutorials - on line 142, I changed "#define TFT_BL   21" to "#define TFT_BL   23") to allow for the right pin access between all the parts.

<img width="729" height="968" alt="image" src="https://github.com/user-attachments/assets/d67fd0ac-2847-4468-87c2-2105d9f7ad7c" />

## Parts: 
* ESP32-DevKitC-32E from Espressif
* Hosyond 2.4 Inches TFT LCD Touch Screen Shield Display Module 320x240 SPI Serial ILI9341 with Touch Pen Compatible with Arduino R3/Mega2560 Development Board
* DS3231 AT24C32 IIC RTC Module Clock Timer Memory Module Board 
* Breadboard - get everything working first

The RTC is to ensure the time is maintained when it isn't connected to power

## Next Steps:
### Hardware
* Convert from breadboard to perfboard so it will fit into a smaller enclosure
* Buy or make enclosure
* Add an on/off switch
* Consider the combined ESP32 & TouchScreen for a slimmer overall profile (the combined ones I've found don't seem to give you full pin access to the ESP32, so not sure how to wire the RTC in)

### Software
* ~Add additional background images that rotate every so often~
  * Rotates on click
  * To Do: Upload at least 3 relevant images
   * For the images I'm currently attempting, 3 files takes more memory than the ESP has. Would have to determine out how to use the SD card slot to leverage.    
* Better font
* Leverage the touchscreen interface to allow a user to set a new event or set the current time (currently the only way to reset the current time would be to reconnect it to the computer and recompile the program)
* Consider using battery power instead of needing to be plugged in?

## Misc Notes
* To convert a current image you have to the array needed by the .h files, you can leverage https://lvgl.io/tools/imageconverter and select ARGB8888 from the dropdown
