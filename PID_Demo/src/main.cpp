/* PID balance code with ping pong ball and distance sensor sharp 2y0a21
 *  by ELECTRONOOBS: https://www.youtube.com/channel/UCjiVhIvGmRZixSzupD0sS9Q
 *  Tutorial: http://electronoobs.com/eng_arduino_tut100.php
 *  Code: http://electronoobs.com/eng_arduino_tut100_code1.php
 *  Scheamtic: http://electronoobs.com/eng_arduino_tut100_sch1.php 
 *  3D parts: http://electronoobs.com/eng_arduino_tut100_stl1.php   
 */
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>



///////////////////////Inputs/outputs///////////////////////
Servo myservo;  // create servo object to control a servo, later attatched to D9
///////////////////////////////////////////////////////

// Constants
#define N 100 // Number of times to sample the ADC
#define SERVO_PIN 9
#define CENTER_ANGLE 55
#define ANALOG_IN A0
#define SETPOINT 13  //Should be the distance from sensor to the middle of the bar in mm
#define PERIOD 50 // 50 ms
#define THRESHOLD 3 // Upper and Lower error bounds

////////////////////////Variables///////////////////////
int Read = 0;
float distance = 0.0;
float elapsedTime, time, timePrev;        //Variables for time control
float distance_previous_error, distance_error;
///////////////////////////////////////////////////////


///////////////////PID constants///////////////////////
#define KP 4
#define KI 0.005
#define KD 750.0
float PID_p, PID_i, PID_d, PID_total;
///////////////////////////////////////////////////////


float get_dist(int n) {
	long sum=0;
	for(int i=0;i<n;i++) {
		sum=sum+analogRead(ANALOG_IN);
	}
	float adc=sum/n;
	float dist = pow(adc/1974.0, -1.18203309693);  // https://docs.google.com/spreadsheets/d/1C5yJy5woSW8JCRuhDKoSJcURs4rShaWbnmI1sjc99jw/edit?usp=sharing
	//float volts = analogRead(adc)*0.0048828125;  // value from sensor * (5/1024)
	//float volts = sum*0.003222656;  // value from sensor * (3.3/1024) EXTERNAL analog refference

	// float dist = 17569.7 * pow(adc, -1.2062);
	//float distance_cm = 13*pow(volts, -1); 
	return(dist);
}


void setup() {
	//analogReference(EXTERNAL);
	Serial.begin(115200);  
	myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
	myservo.write(CENTER_ANGLE); //Put the servo at angle 55, so the balance is in the middle
	pinMode(ANALOG_IN,INPUT);  
	time = millis();
}

void loop() {
	// Serial.println(get_dist(N));
	// delay(PERIOD);
		// else {
		// 	PID_i = 0;
		// }
	if (millis() > time+PERIOD)	{
		time = millis();    
		distance = get_dist(N);   
		Serial.println(distance);
		distance_error = SETPOINT - distance;   
		PID_p = KP * distance_error;
		PID_d = KD*((distance_error - distance_previous_error)/PERIOD);
		
		// if(-THRESHOLD < distance_error && distance_error < THRESHOLD) {
			PID_i = PID_i + (KI * distance_error);
		// }
		// else {
		// 	PID_i = 0;
		// }
	
		PID_total = PID_p + PID_i + PID_d;  
		PID_total = map(PID_total, -150, 150, 0, 150);
		PID_total = max(20, min(160, PID_total)); 
		// Serial.print("PID_total");
		// Serial.println(PID_total);
		myservo.write(120-PID_total);  
		distance_previous_error = distance_error;
	}
}


