#include "stepMotor.hpp"  // ln -s ../includes/stepMotor.hpp stepMotor.hpp
#include "realTimeClock.hpp"  // ln -s ../includes/realTimeClock.hpp realTimeClock.hpp

const int stepPin = 3;
const int dirPin = 4;
Motor::StepMotor m1(stepPin, dirPin);
Clock::RealTimeClock clock;

#define RELAY_LED_DAY	7
#define RELAY_LED_PHOTO	5
#define RELAY_PHOTO		6

#define DELAY_PHOTO		200

#define START_DAY_HOUR	8
#define END_DAY_HOUR	20

int32_t timeLastPhoto = -5000;

void enableLed(bool enable) {
	if (enable)
		digitalWrite(RELAY_LED_PHOTO, LOW);
	else
		digitalWrite(RELAY_LED_PHOTO, HIGH);
}

void takePicture() {
	Serial.println("take picture");
	setDay(false);
	enableLed(true);
	delay(1000);
	digitalWrite(RELAY_PHOTO, LOW);
	delay(DELAY_PHOTO);
	digitalWrite(RELAY_PHOTO, HIGH);
	delay(DELAY_PHOTO);
	digitalWrite(RELAY_PHOTO, LOW);
	delay(DELAY_PHOTO);
	digitalWrite(RELAY_PHOTO, HIGH);
	delay(3000);
	enableLed(false);
	timeLastPhoto = millis();
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
	pinMode(RELAY_PHOTO, OUTPUT);
    // clock.setTime(0, 12, 20, // seconds, minutes, hour
    //               2, // day of week
    //               10, // day of month
    //               2, // month
    //               2020);  // year
	digitalWrite(RELAY_PHOTO, HIGH);
	enableLed(false);
	setDay(false);
}

void loop() {
    clock.displayTime();

    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    clock.getTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

	// pictures every minutes
	if (millis() - timeLastPhoto > 10000) {
		takePicture();
	}

	// set day / night cycle
    // if (hour >= START_DAY_HOUR && hour <= END_DAY_HOUR) {
        setDay(true);
    // }
	// else {
    //     setDay(false);
	// }

    // m1.setSpeed(80);
    // m1.runStep(Motor::FORWARD, 20);
    // delay(300);

    // m1.setSpeed(10);
    // m1.runStep(Motor::BACKWARD, 600);
    delay(500);
}