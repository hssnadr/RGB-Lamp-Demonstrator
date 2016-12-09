void HHMM_follower() {
  getSerialMsg(); // update msgAdr & msgMsg

  if (isNewColor) {
    // Reset all leds to 0
    for (int i = 0; i < nPix; i++) {
      strip.setPixelColor(getTrueLedIndex(i), strip.Color(0, 0, 0));
      stripRed[i] = 0;
      stripGreen[i] = 0;
      stripBlue[i] = 0;
    }
    delay(2);

    // RED : fill "R" letter in function of the RGB red value
    for (int i = r0; i < map(r, 0, 255, r0, r1); i++) {
      stripRed[i] = 255;
      stripGreen[i] = 3;
      stripBlue[i] = 3;
      strip.setPixelColor(getTrueLedIndex(i), strip.Color(stripRed[i], stripGreen[i],  stripBlue[i]));
      
    }

    // GREEN : fill "G" letter in function of the RGB green value
    for (int i = g0; i < map(g, 0, 255, g0, g1); i++) {
      stripRed[i] = 40;
      stripGreen[i] = 255;
      stripBlue[i] = 8;
      strip.setPixelColor(getTrueLedIndex(i), strip.Color(stripRed[i], stripGreen[i],  stripBlue[i]));
    }

    // BLUE : fill "B" letter in function of the RGB blue value
    for (int i = b0; i < map(b, 0, 255, b0, b1); i++) {
      stripRed[i] = 25;
      stripGreen[i] = 50;
      stripBlue[i] = 232;
      strip.setPixelColor(getTrueLedIndex(i), strip.Color(stripRed[i], stripGreen[i],  stripBlue[i]));
    }
    strip.show();
    isNewColor = false;
    timer1 = millis();
  }

  if (millis() - timer1 > 500) {
    // Color LED animation
    for (int i = 0; i < nPix; i++) {
      isColorSet = true;

      // RED : update red component of the RGB leds during the animation
      if (stripRed[i] != r) {
        isColorSet = false;
        if (stripRed[i] < r) {
          stripRed[i] = stripRed[i] + 1;
        }
        else {
          stripRed[i] = stripRed[i] - 1;
        }
      }

      // GREEN : update green component of the RGB leds during the animation
      if (stripGreen[i] != g) {
        isColorSet = false;
        if (stripGreen[i] < g) {
          stripGreen[i] = stripGreen[i] + 1;
        }
        else {
          stripGreen[i] = stripGreen[i] - 1;
        }
      }

      // BLUE : update blue component of the RGB leds during the animation
      if (stripBlue[i] != b) {
        isColorSet = false;
        if (stripBlue[i] < b) {
          stripBlue[i] = stripBlue[i] + 1;
        }
        else {
          stripBlue[i] = stripBlue[i] - 1;
        }
      }

      if (!isColorSet) {
        // Update led colors while animation is not over
        strip.setPixelColor(getTrueLedIndex(i), strip.Color(stripRed[i], stripGreen[i], stripBlue[i]));
      }
    }
    delay(15);
    strip.show();
  }
}
