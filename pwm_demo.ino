/* not cleaned. but yeah... */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <EEPROM.h>
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
int order[16] = {1,5,14,7,16,3,10,2,12,15,6,13,4,8,11,9};
unsigned long next_time = 0;
unsigned long next_time2 = 0;
uint8_t letter = 0;
uint16_t letters[3][16] = {
  {1,1,1,1, 1,0,0,1, 1,0,0,1, 1,1,1,1},
  {1,0,0,1, 0,1,1,0, 0,1,1,0, 1,0,0,1},
  {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0},
};
uint8_t wormx[3] = {0,1,2};
uint8_t wormy[3] = {0,0,0};
uint8_t wormdir = 0;
uint8_t owormdir = 3;
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  letter = EEPROM.read(0);
  letter++;
  if (letter > 3)
      letter = 0;
  EEPROM.write(0,letter);
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
    
  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 4; // upgrade to 400KHz!
  //letter = 4;
}
boolean okdir(uint8_t dir){
  if (dir == (owormdir + 2)%4)
    return false;
  switch (dir){
        case 0:
          if (wormy[0] == 3) return false;
          break;
        case 1:
          if (wormx[0] == 3) return false;
          break;
        case 2:
          if (wormy[0] == 0) return false;
          break;
        case 3:
          if (wormx[0] == 0) return false;
          break;
      }
      return true;
}
void loop() { 
  unsigned long time = millis();
  if (time > next_time) {
    //letter ++;
    //if (letter > 3)
      //letter = 0;
    next_time = time + 1000;
    if (letter == 3) next_time = time + 5000;
    if (letter != 3) {
      for (uint16_t c=0; c < 16; c++) {
        uint16_t val = 1024 * letters[letter][c];
        pwm.setPWM(15-c, 0, val );
      }
    }
    //VAIHA LETER
    
    
  }
  if (time > next_time2 && letter == 3) {
      
      if (okdir(wormdir) == false || random(0,4) == 1){
          owormdir = wormdir;
          wormdir = random(0,4);
          while (okdir(wormdir) == false){
            wormdir = random(0,4);
          }
          
          //wormx[0] = random(0,5);
          //wormy[0] = random(0,5);
      }  
      next_time2 = time + 100;
      wormx[2] = wormx[1];
      wormx[1] = wormx[0];
      wormy[2] = wormy[1];
      wormy[1] = wormy[0];
      
      //SUUNTA
      switch (wormdir){
        case 0:
          wormy[0]=wormy[0]+1;
          break;
        case 1:
          wormx[0]=wormx[0]+1;
          break;
        case 2:
          wormy[0]=wormy[0]-1;
          break;
        case 3:
          wormx[0]=wormx[0]-1;
          break;
      }
       //CLEAR
    for (uint16_t c=0; c < 16; c++) {
      pwm.setPWM(15-c, 4096, 4096 );
    }
    //RENDER
    for (uint16_t c=0; c < 16; c++) {
      uint8_t col = c % 4;
      uint8_t row = floor(c/4);
      for (uint8_t i=0; i<3; i++){
        if (wormx[i] == col && wormy[i] == row){
          pwm.setPWM(15-c, 0, 1024 );
          break;
        }
      }
    }
  }//timer2 end
 
    
    /*for (uint16_t c=0; c < 16; c++) {
      uint16_t val = 2048-2048*(log(c+1)/2.718);
      //4096-4096*(log(x)/2.718)
      pwm.setPWM(15-c, 2048-val, 2048+val );
    }*/
   
  

  //}
}
