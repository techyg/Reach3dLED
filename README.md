"# Reach3dLED" 

This is a project for adding a 24 LED NeoPixel for Reach3d printers.

This is currently a Work in Progress! 

General architectural approach:
* Arduino Trinket communicates over a Serial port to the RAMPS 1.4 board to identify temperature.
* Based on the temperature, the NeoPixel will light up. Cold = blue, Hot= red.
* When idle, and while printing the NeoPixel can also be set to colors. Colors can be changed in the code.

Instructions:
1. Connect an Arduino (ideally a Trinket) to your TX/RX pins on your RAMPS 1.4 board.  The RX/TX pins on your Trinket should be connected this way (Trinket to RAMPS):  RX -> TX,  TX -> RX.  If you don't print with a USB, you can connect to the Aux1 pins (top right 3 pins in the first block- lableled -,s,s).  If you print with a USB, you will need to free up some pins in the X/Y/Z end stop section. More info will be provided on this later.

2. Change any variables as needed in the main code / definitions (such as timeouts)

3. Connect the NeoPixel to your trinket, noting which pin you are using.

4. Compile the code in Arduino studio to your Trinket. 




