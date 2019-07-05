int indWheel = 0;
int oldIndWheel1 = 0;
int oldIndWheel2 = 0;
boolean isLoading = false;

void WheelAnimation() {
  if (!isLoading) {
    shutDownStrip();
  }

  setPixWheel(indWheel, 1);
  setPixWheel(oldIndWheel1, 4);
  setPixWheel(oldIndWheel2, 8);

  delay(57);
  strip.show();

  oldIndWheel1 = indWheel;
  oldIndWheel2 = oldIndWheel1;

  if (indWheel < nPix - 1) {
    if (indWheel == 2) {

    }
    indWheel++;
  }
  else {
    indWheel = 0;
    isLoading = !isLoading ;
    shutDownStrip();
  }
}


void shutDownStrip() {
  for (int i = 0; i < nPix; i++) {
    strip.setPixelColor(getTrueLedIndex(i), strip.Color(0, 0, 0));
  }
}

void setPixWheel(int i_, int r_) {
  if (i_ < r0) {
    strip.setPixelColor(getTrueLedIndex(i_), strip.Color(255 / r_, 255 / r_, 255 / r_));
  }
  if (i_ >= r0) {
    strip.setPixelColor(getTrueLedIndex(i_), strip.Color(255 / r_, 0, 0));
  }
  if (i_ >= g0) {
    strip.setPixelColor(getTrueLedIndex(i_), strip.Color(0, 255 / r_, 0));
  }
  if (i_ >= b0) {
    strip.setPixelColor(getTrueLedIndex(i_), strip.Color(0, 0, 255 / r_));
  }
  if (i_ > b1) {
    strip.setPixelColor(getTrueLedIndex(i_), strip.Color(255 / r_, 255 / r_, 255 / r_));
  }
}
