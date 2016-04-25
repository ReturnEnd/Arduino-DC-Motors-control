#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class Motor {
  private:
    const char *name;
    boolean running;
    unsigned long endTime;
    Adafruit_DCMotor *myMotor;
  
  public:
    Motor( const char *_name, Adafruit_DCMotor *_myMotor){
      name =_name;
      running = false;
      endTime = 0;
      myMotor = _myMotor;
    }
    void Start(const unsigned long _duration) {
      myMotor->setSpeed(255);
      myMotor->run(FORWARD);
        
      running = true;
      endTime = millis() + _duration; 
    }
    void Update(){
      const unsigned long curMillis = millis();
      if (running && (curMillis > endTime)){
        myMotor->setSpeed(0);
        myMotor->run(RELEASE);
        running = false;
      }
    }
};

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
const unsigned char motorCount = 4;
Motor motors[] = {
    Motor("Motor 1", AFMS.getMotor(1)),
    Motor("Motor 2", AFMS.getMotor(2)),
    Motor("Motor 3", AFMS.getMotor(3)),
    Motor("Motor 4", AFMS.getMotor(4))
};

/*
void setup() {
  Serial.begin(9600);
  AFMS.begin();
  // Tests/debug
  motors[0].Start( 5000 );
}

void loop() {
  Serial.println("running");
  for (unsigned char i = 0; i < motorCount; i++){
    motors[i].Update();
  }
}
*/


