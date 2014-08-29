/*
	DRIVES THE COOL LED RIG WOO!
	
	Screen consists of 6*5 dots with 4*4 visible at once
	"letter"		decides which letter is drawn
	"x"			position of letter on screen. 5 is middle. 0 and 7 make the letter go out of screen
	"y"			position of letter on screen. 4 is middle. 0 and 8 make the letter go out of screen
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint8_t letters[5][5] = {	//[lettrs][rows]
	{
	0b110011,
	0b110011,
	0b001100,
	0b110011,
	0b110011
	},
	{
	0b011110,
	0b001100,
	0b001100,
	0b001100,
	0b011110
	},
	{	
	0b001100,
	0b010000,
	0b010110,
	0b010010,
	0b001110
	},
	{	
	0b011110,
	0b010000,
	0b011100,
	0b010000,
	0b011110
	},
	{	
	0b010010,
	0b011110,
	0b010010,
	0b010010,
	0b010010
	}};
//--// VARIABLES ----------------------------//
float x = 5.0; //5 middle
float y = 9; //4 middle
float xs =- 0.3;
float ys = -0.3;
unsigned long next_frame = 0;
unsigned long next_letter = 0;
uint8_t letter = 0;
//--// FUNCTIONS ----------------------------//
void led(uint8_t c, uint8_t state) {
	//onko ledi näkyvillä
	if (c < 23 &&  (c%6) < 4){
		c = c - (c>5)*2 - (c>11)*2 - (c>17)*2;
		switch (state){
			case 0:
				pwm.setPWM(c, 0, 0 );
				//Serial.print(0);
				break;
			default:
				pwm.setPWM(c, 0, 1024 );
				//Serial.print(1);
		}
	}else{
		//Serial.print("x");
	}
}
void render_frame() {
	//RENDER
	for (uint8_t cc=0; cc < 30; cc++) {
		if (cc % 6 == 0)
			Serial.print("\n");
		//if ((letters[0][(uint8_t)floor(c / 6)] >> (c%6)) & 1){
		int8_t c = cc -3*6 + 6*(int8_t)floor(y);
		uint8_t val = 0;
		if (c>=0 && 4-(int8_t)floor((c) / 6) >= 0 && (c%6-4+((int8_t)floor(x)))>=0)//x aisoissa, y aisoissa, x aisoissa
			val = (((letters[letter][4-(int8_t)floor((c) / 6)])>>((c%6-4+((int8_t)floor(x))))) & 1 );
		else
			val = 0;
		//Serial.print(".");
		//Serial.print(((c%6-4+((int8_t)floor(x)))));
		//uint8_t val = (((letters[0][(uint8_t)floor(c / 4)])>>(5-c%4)) & 1 ); toimx 4
		led(cc, val);
	}
	//Serial.print("\n\n");
}
//--// SETUP ------------------------------//
void setup() {
	Serial.begin(9600);
	Serial.println("16 channel PWM test!");

	pwm.begin();
	pwm.setPWMFreq(1600);  // This is the maximum PWM frequency

	// save I2C bitrate
	uint8_t twbrbackup = TWBR;
	// must be changed after calling Wire.begin() (inside pwm.begin())
	TWBR = 12; // upgrade to 400KHz communication between arduino and shield

	Serial.println("All ok!");
}
//--// LOOP ------------------------------//
void loop() {
	//--TIMING
	unsigned long time = millis();
	
	if (time > next_frame){
		next_frame = time+50;
		render_frame();
		//x += xs;
		//x==4 e mitten 8 ute 0 ute
		y += ys;
		if (y<0){
			y = 8;
			letter++;
			if (letter>4)
				letter = 0;
		}
	}
	//y = cos(time / 250)+4;
	//x = sin(time / 250)*1.5+5.5;
	
}

