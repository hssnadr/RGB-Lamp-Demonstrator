void getSerialMsg() {
  // CHECK SERIAL AND UPDATE msgAdr & msgMsg
  //----------------------------------------

  //First thing is to check if some messages have been sent
  if (Serial.available() > 0) {
    msgAdr = (char)Serial.read(); // The first incoming byte correspond to the address message, it's supposed to be a char

    index = 0;
    do
    {
      buffer[index] = Serial.read();// get a byte from the serial port
      if (buffer[index] != -1) {
        index++; // -1 if no byte is present
      }
    } while (buffer[index - 1] != 95); //keep collecting bytes until '_' is received

    msgVal = atoi(buffer);       // interpret buffer string as an integer and get the value corresponding to the address
    updateValues(); // this function is placed here for the example but it's up to you
    
  }
}

void updateValues() {
// COMMENT SERIAL PRINTS WHILE COMMUNICATING WITH MAX MSP
//  Serial.print("Message address: ");
//  Serial.print(msgAdr);
//  Serial.println("");
//  Serial.print("Message value: ");
//  Serial.print(msgVal);
//  Serial.println("");

  // the address is used to route the message value
  switch (msgAdr) {
    case 'r':
      stopAutoLoop();
      r = constrain(msgVal, 0, 255);
      isNewColor = true;
      break;
    case 'g':
      stopAutoLoop();
      g = constrain(msgVal, 0, 255);
      isNewColor = true;
      break;
    case 'b':
      stopAutoLoop();
      b = constrain(msgVal, 0, 255);
      isNewColor = true;
      break;
    default:
      Serial.println("No matching address");
      break;
  }

// COMMENT SERIAL PRINTS WHILE COMMUNICATING WITH MAX MSP
//  Serial.print("RGB: ");
//  Serial.print("\t");
//  Serial.print(r);
//  Serial.print("\t");
//  Serial.print(g);
//  Serial.print("\t");
//  Serial.print(b);
//  Serial.println("");
//  Serial.println(strip.Color(r, g, b));
//  Serial.println("----------------------------");
}
