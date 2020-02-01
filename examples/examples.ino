#include "voltmeter.hpp"  // ln -s ../includes/voltmeter.hpp voltmeter.hpp

int voltPin = A0;
Volt::Voltmeter voltmeter(voltPin);

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(voltmeter.getVoltage());
}
