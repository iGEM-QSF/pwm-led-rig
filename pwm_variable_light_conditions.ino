/*************************************************** 
  LED-rig programmer for Aalto-Helsinki Bioworks
  
  We heveloped a LED-rig to shine light in a controlled way on our bacteria.
  
  This program just sets the led intensities to right ones.
  Based on Arduinon Nano v3 and Adafruit 16-channel PWM shield.
  
  http://www.adafruit.com/products/815
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
//0 - 4096
uint16_t arvot[] = {
    10,24,56,132,
    311,734,1734,4095,
    10,24,56,132,
    311,734,1734,4095}; // VTT varioskan - oskari day values
uint16_t arvot_pois[] = { //pois paalta arvot
    1,1,1,1,
    1,1,1,1,
    10,24,56,132,
    311,734,1734,4095};
//uint16_t arvot[] = {1,1,10,10,40,40,120,120,290,290,650,650,1582,1582,4095,4095}; // 1st measurement
//uint16_t arvot[] = {0,1,3,6,10,20,40,75,120,190,290,450,650,1024,1582,2048,4096}; // almost linear increase over all leds 
void setup() {
  pwm.begin();
  pwm.setPWMFreq(1600);  // Use maximum PWM freq.
    
  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!. This is not especially important in our case, because we are not using the i2c actively. Just in Setup
  //Set intensity
  leds_set(1);
}
void set_led_val(uint8_t ledpin, uint16_t val){
  pwm.setPWM(ledpin, 0, (uint16_t)ceil(val) ); //tämä
  
}
void leds_set(uint8_t set){
    for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) {
      uint16_t val = pow(10, (set*(log10(arvot[pwmnum]) - log10(arvot_pois[pwmnum]))/30 + log10(arvot_pois[pwmnum])));
      //pwm.setPWM(pwmnum, 0, (uint16_t)ceil(val) );
      set_led_val(pwmnum, val);
    }
}

void loop() {
    for (uint8_t indexer=0; indexer < 30; indexer++) {
      leds_set(indexer);
      delay(1000); // Increase intensity step length
    } 
    for (uint8_t indexer=30; indexer > 0; indexer--) {
      leds_set(indexer);
      delay(1000); // Decrease intensity step length
    } 
}
