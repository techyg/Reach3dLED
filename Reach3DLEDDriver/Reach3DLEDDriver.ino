#include <Adafruit_NeoPixel.h>

//Change these settings as needed
int CHECK_TIMING = 5000;  //how long to wait between checking temperature (1000 = 1 second)
int NEOPIXEL_SIZE = 24; // the number of pixels on your neo pixel
int NEOPIXEL_PIN = 5; //this is the pin your NeoPixel is connected to

//*****Don't change code below this line unless you know what you're doing ******//

//Global Variables used by sketch
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NEOPIXEL_SIZE, NEOPIXEL_PIN);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);  //for output to Serial Monitor
  Serial1.begin(250000); //connection to RAMPS board. Assumes connected to RX/TX (Serial) pins. 
  ring.begin();
  ring.setBrightness(25);
  ring.show();
}


//Check to see if an string is numeric. 
boolean IsNumeric(String str) {
    for(char i = 0; i < str.length(); i++) {
        if ( !(isDigit(str.charAt(i)) || str.charAt(i) == '.' )) {
            return false;
        }
    }
    return true;
}

//Parses output of GCode to return an integer of the temp on formatted strings from M105. Truncates decimal. Returns 0 if invalid string. 
int parseTemp(String temperatureString)
{
  //Expected format 2: ok T:21.8 /0.0 B:21.7 /0.0 T0:21.8 /0.0 @:0 B@:0
  //Expected format 1: T:210.7 E:0 W:?
  int tloc=0;
  tloc = temperatureString.indexOf("T:"); 
  if (tloc > 0)
  {
      if (IsNumeric(temperatureString.substring(tloc+2, temperatureString.indexOf("."))))
      {  
        return(temperatureString.substring(tloc+2, temperatureString.indexOf(".")).toInt());
      }
  }
  else
  {
    return (0);
  }
  
}


 // Fill the dots one after the other with a color 
 void colorWipe(uint32_t c, uint8_t wait) { 
   for(uint16_t i=0; i<ring.numPixels(); i++) { 
       ring.setPixelColor(i, c); 
       ring.show(); 
       delay(wait); 
   } 
 } 


void SetColors(String output)
{

  int Temp = parseTemp(output);

  Serial.println(Temp);
  
    if (Temp == 0)
    {
      colorWipe(ring.Color(0,0,0), 100); // Black
    }
    else if (Temp > 0 && Temp <= 50)
    {
      colorWipe(ring.Color(0, 0, 64), 100); // Blue
    }
   else if (Temp > 50 && Temp <= 100)
    {
      colorWipe(ring.Color(0, 32, 0), 100); // Light Green
    }
   else if (Temp > 100 && Temp <= 150)
    {
      colorWipe(ring.Color(0, 64, 0), 100); // Full Green
    }
   else if (Temp > 150 && Temp <= 200)
    {
     colorWipe(ring.Color(64, 64, 0), 100); // Yellow
    }
   else if (Temp > 200 && Temp <= 250)
    {
      colorWipe(ring.Color(64, 0, 0), 100); // Red
    }
}

void loop() {

   if (Serial1.availableForWrite()) 
   {                
                delay(CHECK_TIMING);
                String gCode = "M105";
                Serial1.println(gCode);
                Serial.println(gCode);  //Show on debug window
                delay(100); // delay for serial buffer output
   } 

   //This code handles the serial communications received from the RAMPS board
    if (Serial1.available()) {
                String output = Serial1.readString(); 
                Serial.println(output);
                SetColors(output);               
    }
}



