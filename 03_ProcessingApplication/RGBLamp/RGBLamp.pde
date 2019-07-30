/*
 * This project is part of the Movuino demo tutorial from: http://www.movuino.com/
 * Page of the project: http://www.movuino.com/index.php/portfolio/rgb-lamp/
 * Github: https://github.com/hssnadr/RGB-Lamp-Demonstrator
 */

import processing.serial.*;     // library to communicate with Arduino through serial (USB port)
import geomerative.*;           // library for text manipulation and point extraction

// Serial to RGBLamp
Serial arduinoRGBLamp ;
String oldSerialData = "";

// Color swatch
color red = color(255, 0, 0);
color green = color(0, 255, 0);
color blue = color(0, 0, 255);
color primaryColors[] = {red, green, blue};
// Color progression
float[] colorValues = {0.0f, 0.0f, 0.0f}; // {red, green, blue}

// Shape
RShape shape;                   // holds the base shape created from the text
RPoint[][] allPaths;            // holds the extracted points
int nShapes;                    // number of characters in the sentence printed

// Movuino data
float euclGyr = 0.0f;
float oldEuclGyr = 0.0f;

//--------------------------------------------------------
//                         SETUP
//--------------------------------------------------------
void setup() {
  // set application window
  size(700, 500);

  // Set serial communication with the RGB Lamp 
  println(Serial.list());
  if (Serial.list().length > 0) {
    String portName = Serial.list()[0];
    arduinoRGBLamp = new Serial(this, portName, 38400);
  }

  // initialize the Geomerative library
  RG.init(this);
  shape = RG.loadShape("RGB_BaseShapes.svg");
  nShapes = shape.countChildren();

  RCommand.setSegmentator(RCommand.UNIFORMLENGTH); // use a uniform distance between points
  RCommand.setSegmentLength(10); // set segmentLength between points
  // extract paths and points from the base shape using the above Segmentator settings
  allPaths = shape.getPointsInPaths();

  callMovuino("127.0.0.1", 3000, 3001); // do not change values if using the Movuino interface

  // Reset lamp display
  delay(10);
  resetColorProgress();
}

//--------------------------------------------------------
//                       MAIN LOOP
//--------------------------------------------------------
void draw() {
  // TRACKING DATA
  int curShapeIndex_ = constrain(movuino.xmmGestId-1, 0, nShapes);
  float curProgShape_ = movuino.xmmGestProg;
  setColorProgess(curShapeIndex_, curProgShape_);                // set color progression based on incoming tracking data

  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  // BACKGROUND COLOR
  /* background color is generated from the current gesture tracking progress */
  color background_ = color(255*colorValues[0], 255*colorValues[1], 255*colorValues[2]);
  background(background_);

  //----------------------------------
  //----------------------------------
  // BASE CHARACTERS
  /* graphic purpose only */
  shape.setFill(false);
  shape.setStroke(true);
  shape.setStrokeCap("round");
  shape.setStrokeJoin("round");

  // Base 1
  shape.setStrokeWeight(40);
  shape.setStroke(color(255));
  RG.shape(shape);

  // Base 2
  shape.setStrokeWeight(21);
  shape.setStroke(10);
  RG.shape(shape);

  //----------------------------------
  //----------------------------------
  // CURRENT PROGRESS DISPLAY
  // Draw shapes
  beginShape(LINES);
  for (int i=0; i< nShapes; i++) {
    // Get path
    RPoint[] singlePath_ = allPaths[i];
    float progShape_ = colorValues[i];

    // Trace path
    if (curProgShape_ > 0.0f) {
      for (int j=1; j < progShape_ * singlePath_.length; j++) {
        color pCol_ = primaryColors[i];
        stroke(pCol_);
        strokeWeight(7);

        RPoint p = singlePath_[j-1];  // start point
        vertex(p.x, p.y);
        RPoint n = singlePath_[j];    // end point
        vertex(n.x, n.y);
      }
    }
  }
  endShape();

  // Current position
  fill(primaryColors[curShapeIndex_]);
  noStroke();
  RPoint[] singlePath_ = allPaths[curShapeIndex_];
  int progShape_ = int(colorValues[curShapeIndex_] * (singlePath_.length - 1));
  RPoint p = singlePath_[progShape_];
  float dD_ = 2 * cos(millis()/200.0f) + 19; // animat cursor
  ellipse(p.x, p.y, dD_, dD_);

  //----------------------------------
  //----------------------------------
  // ERASER
  euclGyr = sqrt(pow(movuino.gx, 2) + pow(movuino.gy, 2) + pow(movuino.gz, 2)); 
  if (euclGyr - oldEuclGyr > 0.4f) {
    resetColorProgress();
  }
  oldEuclGyr = euclGyr ;
}

//--------------------------------------------------------
//                     FUNCTIONS
//--------------------------------------------------------

void setColorProgess(int shapeIndex_, float prog_) {
  shapeIndex_ = constrain(shapeIndex_, 0, nShapes);
  prog_ = constrain(prog_, 0f, 1f);

  if (prog_ - colorValues[shapeIndex_] > 0f) {
    if (prog_ - colorValues[shapeIndex_] < 0.3f) {
      colorValues[shapeIndex_] = prog_ ;          // update value if conditions satisfied

      sendToSerial(shapeIndex_) ;                 // send to serial
    }
  }
}

void resetColorProgress() {
  for (int i=0; i<nShapes; i++) {
    colorValues[i] = 0.0f;
    sendToSerial(i) ;
  }
  delay(10);
}

void sendToSerial(int shapeIndex_) {
  shapeIndex_ = constrain(shapeIndex_, 0, nShapes);

  String data_ = "";
  switch(shapeIndex_) {
  case 0:
    data_ += 'r';
    break;
  case 1:
    data_ += 'g';
    break;
  case 2:
    data_ += 'b';
    break;
  default:
    break;
  }

  if (data_ != "") {
    int progInt_ = int(255 * colorValues[shapeIndex_]);
    progInt_ = constrain(progInt_, 0, 255);

    data_ += str(progInt_);  // data
    data_ += '_';            // end data character
    data_ = data_.trim();    // remove space or any parasite characters   

    if (!oldSerialData.equals(data_)) {
      // Send data
      if (arduinoRGBLamp != null) {
        arduinoRGBLamp.write(data_);
      }
      println("Send to serial:", data_);

      // reset oldSerialData
      oldSerialData = "";
      oldSerialData += data_;
    }
  }
}
