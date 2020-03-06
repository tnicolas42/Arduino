#include "stepMotor.hpp"  // ln -s ../includes/stepMotor.hpp stepMotor.hpp
#include "realTimeClock.hpp"  // ln -s ../includes/realTimeClock.hpp realTimeClock.hpp
#include <Servo.h>

const int stepPin = 3;
const int dirPin = 4;
Motor::StepMotor m1(stepPin, dirPin);
Clock::RealTimeClock clock;

Servo servoMotor;

#define RELAY_LED_DAY	7
#define RELAY_LED_PHOTO	5
// #define RELAY_PHOTO		6

// #define PIN_PHOTO		6

// #define DELAY_PHOTO		200

#define SERVO_PHOTO		6

#define START_DAY_HOUR	8
#define END_DAY_HOUR	20

uint32_t timeLastPhoto = 0;
uint32_t timeLastMoveMotor = 0;

void enableLed(bool enable) {
	if (enable)
		digitalWrite(RELAY_LED_PHOTO, LOW);
	else
		digitalWrite(RELAY_LED_PHOTO, HIGH);
}

void takePicture() {
	timeLastPhoto = millis();
	Serial.println("take picture");
	setDay(false);
	enableLed(true);
	delay(7000);
	servoMotor.write(75);
	delay(300);
	servoMotor.write(50);
	delay(300);
	servoMotor.write(75);
	delay(300);
	servoMotor.write(50);
	delay(3000);
	enableLed(false);
}

void setDay(bool isDay) {
	if (isDay)
		digitalWrite(RELAY_LED_DAY, LOW);
	else
		digitalWrite(RELAY_LED_DAY, HIGH);
}

void setup() {
	Serial.begin(9600);
	pinMode(RELAY_LED_DAY, OUTPUT);
	pinMode(RELAY_LED_PHOTO, OUTPUT);
	// pinMode(RELAY_PHOTO, OUTPUT);
	// digitalWrite(PIN_PHOTO, LOW);
	// pinMode(PIN_PHOTO, OUTPUT);
	servoMotor.attach(SERVO_PHOTO);
	servoMotor.write(50);
    // clock.setTime(0, 12, 20, // seconds, minutes, hour
    //               2, // day of week
    //               10, // day of month
    //               2, // month
    //               2020);  // year
	// digitalWrite(RELAY_PHOTO, HIGH);
	enableLed(false);
	setDay(false);
}

void loop() {
    // clock.displayTime();

    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    clock.getTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

	// pictures every X sed
	if (millis() - timeLastPhoto > (uint32_t)40 * (uint32_t)1000) {
		takePicture();
	}

	// set day / night cycle
    if (hour >= START_DAY_HOUR && hour <= END_DAY_HOUR) {
        setDay(true);
    }
	else {
        setDay(false);
	}

	// if (millis() - timeLastMoveMotor > (uint32_t)150 * (uint32_t)1000 * (uint32_t)5) {
	// // if (millis() - timeLastMoveMotor > (uint32_t)432 * (uint32_t)1000 * (uint32_t)5) {
	// 	timeLastMoveMotor = millis();
	// 	m1.setSpeed(80);
	// 	m1.runStep(Motor::FORWARD, 5);
	// }
    delay(500);
}