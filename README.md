# Lampe RGB

## Presentation

This lamp project is a demonstrator dedicated to highlight Mobile-Lab technological ressources. It allows to interact with its colors by moving the hand. How does it works ?
 1. the user record 3 gestures, each one corresponding to a color component of the light (red, green or blue);
 2. then he moves is hand reproducing those gestures, this way he can regulate the proportion of RGB colors in the light and create any kind of colors;
 3. the user can record any kind of gesture, let's try different patterns!

## Content
Here you will find:
* **1_Movuino_FirmwareOSC/Arduino** this folder contains the firmware for the Movuino. You can edit and use it with the Arduino software;
* **2_CybRGB_ArduinoFirmware** this folder contains the firmware of the lamp. You can also edit it using the Arduino software;
* **CybRGB.maxpat** this file is used as interface to control the lamp.

## Installation
  
### Movuino (1_Movuino_FirmwareOSC/)
* Download and install the Arduino software: https://www.arduino.cc/en/Main/Software
* Download and install the XXX driver: www.xxxx.com/download
* Inside Arduino
  * Install the card ESP8266 following those instructions: https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon
  * Choose card (Tools/Board): Adafruit HUZZAH ESP8266
  * Copy the content of the Arduino folder into your own Arduino folder (Macintosh and Windows: Documents/Arduino). It includes the libraries you need, but you can also install them by yourself. In the Arduino software go to "Sketch/Include Library/Manage Libraries...", here seek and install:  
    * I2Cdev
    * OSC
    * MPU6050
      * for this one you need to make a correction in the library file. Go to Arduino/libraries/MPU6050/ and edit the file "MPU6050.h" (open it in NotePad, SublimeText, NotePad++ or anykind of text editor).
        * line 58, replace the line: `#define MPU6050_DEFAULT_ADDRESS MPU6050_ADDRESS_AD0_LOW`
        * **by:** `#define MPU6050_DEFAULT_ADDRESS MPU6050_ADDRESS_AD0_HIGH`
  * Follow instructions inside the code (ip, rooter, password, port...)
     * `const char * ssid = "my_box_name";` set the name of your wifi network
     * `const char * pass = "my_password";` type the password of the network
     * `const char * hostIP = "192.168.1.35";` set the ip address of **YOUR COMPUTER** which is also connected to the same Wifi network and on which you will use the Max file
     * `const unsigned int port = 7400;` (optional) here you can set the port on which the data are sent. If you don't use other ports or if you have no idea of what I'm talking about you can let 7400.
     * `const unsigned int localPort = 3011;` (optional) here you can set the port on which Movuino can receive OSC message. Idem, better to let it at 3011.
 * Go to Tools/Board, select "Adafruit HUZZAH ESP8266" with:
      * CPU Frequency: 80 MHz
      * Flash Size: 4M (3M SPIFFS)
      * Upload Speed: 115200
      * Port: the one corresponding to the Movuino
  * Upload firmware and check on the Arduino monitor window if everything is good!
  * You can shut down (partially) and turn on the Movuino by pressing the button during 1 second.
  * **You can also send message to the Movuino, also using OSC.**
  
### Movuino desktop application (2_MovuinoDesktop_OSC/)
#### MAX/MSP
Once Movuino is launch and properly connected, you don't have anything to do more than open the Max file `MovuinoOSC_to MaxMSP.maxpat`

#### PureData
Same than Max/MSP with file `MovuinoOSC_to_PureData.pd`

#### Python
##### Installation needed
* Python 2.7
* Python libraries:
  * Numpy: easiest way with command line `sudo pip install numpy`
    * This library allows better data manipulation, especially using matrix and vectors
  * pyOSC
    * Dl link: https://pypi.python.org/pypi/pyOSC
    * Reference: https://wiki.labomedia.org/index.php/Envoyer_et_recevoir_de_l%27OSC_en_python#Reception_d.27un_message_avec_un_serveur
Go into the Main.py file and `main()` function of each script to see how to interact with the code.  

##### Note
* the pyOSC library returns an error when you close the server thread (`self.s.close()`). This error is not really a problem since 
the thread is actually closed once called. If you know how to handle it please tell me cause I don't know when I will check that.

#### Processing
* Install Processing: https://processing.org/download/
* Install oscP5 libraries: into Processing go to Sketch/Include Library/Manage Libraries.. seek and install "oscP5"
* Enjoy your life like never before
