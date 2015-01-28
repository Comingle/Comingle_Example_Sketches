import processing.serial.*;

import oscP5.*;
import netP5.*;

import processing.net.*;

/* OpenProcessing Tweak of *@*http://www.openprocessing.org/sketch/163811*@* */
/* !do not delete the line above, required for linking your tweak if you upload again */
/*
//Comingle Modifying
 * Muse FFT brainwave visualiser
 * Written in Processing 2.2.1
 * by Sarah Bennett (sarahb@cse.unsw.edu.au)
 * 2014-10-01
 * 
 * How to run:
 * 1) Run muse-io, with the dsp output set, specifying a UDP port
 * eg: ./muse-io --device 00:06:66:69:4F:8B --50hz --dsp --osc "osc.udp://localhost:5000"
 //this one
 muse-io  --60hz --dsp --osc "osc.udp://localhost:5000" --preset 10 //preset doesn't work
 * where --device is your Muse's mac address
 *
 * 2) Run this script with Processing
 * 
 * 3) Enjoy :)
 */

 
/*
FEATURES TO ADD:
 
* live EEG data (in another tab?)
* logging to file
* scrolling the screen, not going over the page
*/
 
 
// set up the OSC stuff
OscP5 oscP5;
NetAddress myRemoteLocation;
 
// Number of data channels
int numChannels = 4;
 
// Some globals: current X position where we're drawing data; width of the lines we're drawing
int currentPosition = 0;
int drawWidth = 1;
 
// The names of the waves, in any order
String waves[] = {
  "alpha_relative", "beta_relative", "gamma_relative", "delta_relative", "theta_relative"
};
int numBuckets = waves.length;
 
// Store the current data as it comes in. lastPos contains the n-1th data point, and values contains the nth.
float lastPos[][] = new float[numBuckets][numChannels];
float values[][] = new float[numBuckets][numChannels];

//Serial stuff
 Serial port; 
 
   int power=100;

 
// Set up the program
void setup() {
  // Specify the screen size
  size(1000, 800);
 
  // Set up the OSC stuff
  oscP5 = new OscP5(this, 5000);
  myRemoteLocation = new NetAddress("127.0.0.1", 5000);
 
  // Set the background color of the screen
  background(0);
 
  // Specify that we're in HSB color mode
  colorMode(HSB);
  
    //Communication
   // List all the available serial ports in the output pane. 
 // You will need to choose the port that the Arduino board is 
 // connected to from this list. The first port in the list is 
 // port #0 and the third port in the list is port #2. 
 //println(Serial.list()); 
   // Open the port that the Arduino board is connected to (in this case #0) 
 // Make sure to open the port at the same speed Arduino is using (9600bps) 
 port = new Serial(this, Serial.list()[0], 9600); 
  
}
 
// This function gets called every time any OSC message comes in.
// Within the function, we can check if a given message matches the one we're after, and react accordingly.
// This is in contrast to other OSC interfaces, which set up handlers for each type of message that can come in.
// I'm not sure whether this is possible to do in Processing with the current libraries.
void oscEvent(OscMessage theOscMessage) {

  // For each type of wave [alpha, beta, ...]
  for (int curWave = 0; curWave < waves.length; curWave++) {

                        println(theOscMessage.addrPattern());

    // If the wave matches the DSP data for that wave
  // test
   if (theOscMessage.checkAddrPattern("/muse/elements/" + waves[curWave]) == true) {
  //       if (theOscMessage.checkAddrPattern("/muse/elements/" + "blink") == true) {

      // Make sure that we have the type tag right: ffff means four floats, which is what we'll get when the Muse is set to preset 10.
                    println("woring?");

      if (theOscMessage.checkTypetag("ffff")) {
        // For each of the channels of data (4, in preset 10)
        for (int i=0; i<numChannels; i++) {
          // Store the current data point in the array
          values[curWave][i] = theOscMessage.get(i).floatValue();
        }
      }
    }
  }
}
 
// This is where we actually draw the graphics onto the screen
// This function takes the data from the global array, and draws each of the data points on the screen,
// wrapping around as the screen gets filled.
// Each wave is drawn in a different color, and it also displays the names of the waves with their current values [scaled from 0-1 to 0-100], for each channel.
void draw() {
  // Set the fill color to black, and turn off strokes
  fill(0);
  noStroke();
  // Draw a rectangle to cover the background in black, before overwriting the wave data
  rect(currentPosition, 0, drawWidth*5, height);
 
  // The top and bottom position of where we're going to draw
  float top, bottom;
 
  // For each channel:
  for (int curChannel = 0; curChannel < numChannels; curChannel++) {
    
    // Specify the boundaries of where we're drawing
    top = map(curChannel, 0, numChannels, height, 30);
    bottom = map(curChannel+1, 0, numChannels, height, 30);
    
    // Draw a rectangle to clear where the text about each waveform is going to be
    fill(0);
    noStroke();
    rect(0, bottom-30, width, 30);
 
    // For each of the buckets / wave types:
    for (int i=0; i<numBuckets; i++) {
 
      
      // Specify the color for this wavetype
      int c = color(255/7.0*i, 255, 255);
      
      // Create the text, talking about the waveform with its values
      fill(c);
      textAlign(TOP, LEFT);
      text(waves[i] + "(" + str(int(values[i][curChannel]*100)) + ")", 15+i*100, bottom-15);
      
      // Draw the line of the waveform
      stroke(c);
      line(currentPosition, map(lastPos[i][curChannel], 0, 1, top-30, bottom), currentPosition+drawWidth, map(values[i][curChannel], 0, 1, top-30, bottom));
      
      // Update where we came from, for drawing the next line
      lastPos[i][curChannel] = values[i][curChannel];
      
      if(i==2){ //for the gamma wave
        power=int(values[i][curChannel]*1000);
      }
    }
  }
   
   port.write(power); 
  
  // Update the current x position across the page, and wrap around when we hit the end
  currentPosition+=drawWidth;
  currentPosition %= width;
}
