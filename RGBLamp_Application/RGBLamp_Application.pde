/*
 * This example is based on the UsingGeomerative example of the Generative Typography example
 * Here is the link of the original source: https://github.com/AmnonOwed/CAN_GenerativeTypography
 */

import geomerative.*;           // library for text manipulation and point extraction

// Color swatch
color c0 = color(73, 81, 208, 0);
color c1 = color(243, 240, 114, 200);
color c2 = color(125, 222, 227, 100);
color c3 = color(245, 91, 85, 200);

color primaryColors[] = {color(255,0,0), color(0,255,0), color(0,0,255)};

int nShapes;                // number of characters in the sentence printed

float nextPointSpeed = 0.65;    // speed at which the sketch cycles through the points
RShape shape;                   // holds the base shape created from the text
RPoint[][] allPaths;            // holds the extracted points

void setup() {
  size(700, 500);

  // initialize the Geomerative library
  RG.init(this);
  shape = RG.loadShape("RGB_BaseShapes.svg");
  nShapes = shape.countChildren();
  
  RCommand.setSegmentator(RCommand.UNIFORMLENGTH); // use a uniform distance between points
  RCommand.setSegmentLength(10); // set segmentLength between points
  // extract paths and points from the base shape using the above Segmentator settings
  allPaths = shape.getPointsInPaths();

  callMovuino("127.0.0.1", 3000, 3001); // do not change values if using the Movuino interface
}

void draw() {
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  float globalEnergy;   // affect color
  int curGlif = 0;      // select current caracter to draw
  float progGlif = 0;   // define progression of the  (float between 0.0 and 1.0)

  curGlif = constrain(movuino.xmmGestId-1, 0, nShapes);
  progGlif = movuino.xmmGestProg;
  globalEnergy = sqrt(pow(movuino.gx, 2) + pow(movuino.gy, 2) + pow(movuino.gz, 2));
  globalEnergy /= sqrt(3);
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------

  background(255); // reset screen

  // COLOR
  // Compute color based on globalEnergy
  float dc_ = 1.2*globalEnergy; // color variation
  dc_ = constrain(dc_, 0, 1);
  color c_;
  if (dc_ > 0.66) {
    c_ = lerpColor(c1, c3, 3*(dc_-0.66)); // from c3 to c1
  } else {
    if (dc_ > 0.33) {
      c_ = lerpColor(c2, c1, 3*(dc_-0.33)); // from c1 to c2
    } else {
      c_ = lerpColor(c0, c2, 3*dc_); // from c2 to c0
    }
  }

  //----------------------------------
  //----------------------------------
  // BASE CHARACTERS
  for (int i=0; i<nShapes; i++) {
    RPoint[] singlePath_ = allPaths[i];
    color pCol_ = primaryColors[i];
    stroke(pCol_);
    strokeWeight(3);
    
    // Draw shape
    beginShape(LINES);
    for (int j=0; j< singlePath_.length - 1; j++) {
      RPoint p = singlePath_[j];    // start point
      vertex(p.x, p.y);
      RPoint n = singlePath_[j+1];  // end point
      vertex(n.x, n.y);
    }
    endShape();
  }

  //----------------------------------
  //----------------------------------
  // LINES
  // draw thin transparant lines between two points within a path (a letter can have multiple paths)
  // dynamically set the 'opposite' point based on the current frameCount
  int fc = int(frameCount * nextPointSpeed);  
  stroke(c_);
  strokeWeight(10);
  RPoint[] singlePath_ = allPaths[curGlif];
  progGlif = constrain(progGlif, 0, 1);
  
  // Draw shape
  beginShape(LINES);
  for (int i=0; i < progGlif * singlePath_.length; i++) {
    RPoint p = singlePath_[i];                          // start point
    vertex(p.x, p.y);
    
    RPoint n = singlePath_[(fc+i)%singlePath_.length];  // end point
    vertex(n.x, n.y);
    
    color pCol_ = primaryColors[curGlif];
    fill(pCol_);
    noStroke();
    ellipse(p.x, p.y, 10, 10);
  }
  endShape();
}
