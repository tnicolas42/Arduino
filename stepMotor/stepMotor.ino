namespace Motor {
  enum Direction {
    FORWARD,
    BACKWARD,
  };

  float mapFloat(long x, long in_min, long in_max, long out_min, long out_max) {
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
  }

  class StepMotor {
    // 2 digital pin
    // using A4988 Driver Module
    public:
      StepMotor(int stepPin, int dirPin) : _stepPin(stepPin), _dirPin(dirPin) {
        pinMode(_stepPin, OUTPUT);
        pinMode(_dirPin, OUTPUT);
        _speed = 500;
      }
      virtual ~StepMotor() {}
  
      void setSpeed(float speed_) {  // btw 0 & 100
        if (speed_ == 0)
          _speed = 0;
        // btw 500 & 32000
        _speed = (int)mapFloat(speed_, 0, 100, 32000, 500);
      }
  
      void runStep(Direction dir, int nbSteps) {  // 200 steps for 360deg
        if (_speed == 0)
          return;
        if (dir == FORWARD) {
          digitalWrite(_dirPin, HIGH);
        }
        else {
          digitalWrite(_dirPin, LOW);
        }
        for (int x = 0; x < nbSteps; x++) {
          digitalWrite(_stepPin,HIGH); 
          delayMicroseconds(_speed); 
          digitalWrite(_stepPin,LOW); 
          delayMicroseconds(_speed); 
        }
      }

      void runDeg(Direction dir, int nbDegrees) {  // 200 steps for 360deg
        runStep(dir, (int)mapFloat(nbDegrees, 0, 360, 0, 200));
      }
  
    private:
      int _stepPin;
      int _dirPin;
      int _speed;
  };
}

// Example /////////////////////////////////////////////////

const int stepPin = 3; 
const int dirPin = 4; 

Motor::StepMotor m1(stepPin, dirPin);

void setup() {
}
void loop() {
  m1.setSpeed(100);
  m1.runStep(Motor::FORWARD, 600);
  delay(1000);

  m1.setSpeed(100);
  m1.runStep(Motor::BACKWARD, 600);
  delay(1000);
}
