pwm-led-rig
===========

The sources for our led-rig automation

We made a device to perform our experiments. Our led-rig can shine light on microtiter plates.
We have 16 indiviually controllable LED:s.

Using Arduino nano v3 and Adafruit 16-channel PWM shield.

Woop!

Files
* pwm_led_intensity.ino, sets lab measurement intensities
* pwm_text.ino, scrolls cool text on rig :D
* pwm_demo.ino, shows some coll effects

Setting up with arduino
-----------------------

#You need
* A usb-miniusb cable
* comnputer

#Uploading the new code
* Download and install the arduino IDE at http://arduino.cc/en/Main/Software, the normal version is ok. Windows 8 has some trouble understanding the drivers, but I managed to get it works so i hope you do too.

Okay the drivers are always difficult ot install... Nano drivers(OSX) http://forum.arduino.cc/index.php?PHPSESSID=p1uj253ubdk5vulvn65rfp0fh2&topic=123573.msg938667#msg938667
and troubleshooting
http://forum.arduino.cc/index.php?topic=198539.0
* Install Adafruit PWM library. followng these links: https://learn.adafruit.com/adafruit-16-channel-pwm-slash-servo-shield/using-the-adafruit-library
* Plug in the arduino _while holding down the power button_
* Check that the arduino is connected (can be done by opening arduino IDE and clicking "tools">"serial port". If there is a non-grayed out option then it's conencted properly
* Select "tools">"board">"Arduino Nano w/ Atmega328
* Open up the pwm_led_intensity.ino script
* Modify desired values
* Upload. Compiling first takes place. Wait...
* Arduino blinks....aaand leds turn on.
