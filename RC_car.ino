#include <Servo.h>

Servo servo;

//======================define pins===============================
#define motorX 4
#define motorY 5
#define mPwm 3
#define serverPin 10
//======================define pins===============================

//=================Global My variable=============================
int speedFactor = 0;
int turningFactor = 900;
int turningOperator;
int park = 0;
int cForward = 1;
int cBackward = 2;
int moveOperator;
//=================Global My variable=============================

void setup() {
  // put your setup code here, to run once:
  pinMode(motorX, OUTPUT);
  pinMode(motorY, OUTPUT);
  pinMode(mPwm, OUTPUT);
  pinMode(serverPin, OUTPUT);

  Serial.begin(9600);
  servo.attach(serverPin);
  servo.writeMicroseconds(500000);
  turningOperator = map(turningFactor, 0, 1900, 140, 0);
  servo.write(turningOperator);

}

void loop() {
  // put your main code here, to run repeatedly:

  char val;
  if (Serial.available()) {
    val = Serial.read();
    Serial.println(val);

    speedControl(val);
    turningControl(val);
    handleCommand(val);

    turningOperator = map(turningFactor, 0, 1900, 140, 0);

    if (moveOperator == cForward) {
      forward();
    } else if (moveOperator == cBackward) {
      backward();
    } else if (moveOperator == park) {
      cStop();
    }
  }
}

void speedControl(char speedVariable) {

  if (speedVariable == '0') {
    speedFactor = 75;
  } else if (speedVariable == '1') {
    speedFactor = 85;
  } else if (speedVariable == '2') {
    speedFactor = 100;
  } else if (speedVariable == '3') {
    speedFactor = 110;
  } else if (speedVariable == '4') {
    speedFactor = 120;
  } else if (speedVariable == '5') {
    speedFactor = 140;
  } else if (speedVariable == '6') {
    speedFactor = 165;
  } else if (speedVariable == '7') {
    speedFactor = 190;
  } else if (speedVariable == '8') {
    speedFactor = 225;
  } else if (speedVariable == '9') {
    speedFactor = 255;
  }

}

void turningControl(char turningVariable) {

  if (turningVariable == 'A') {
    turningFactor = 0;
  } else if (turningVariable == 'B') {
    turningFactor = 100;
  } else if (turningVariable == 'C') {
    turningFactor = 200;
  } else if (turningVariable == 'E') {
    turningFactor = 300;
  } else if (turningVariable == 'F') {
    turningFactor = 400;
  } else if (turningVariable == 'G') {
    turningFactor = 500;
  } else if (turningVariable == 'H') {
    turningFactor = 600;
  } else if (turningVariable == 'I') {
    turningFactor = 700;
  } else if (turningVariable == 'J') {
    turningFactor = 800;
  } else if (turningVariable == 'K') {
    turningFactor = 900;
  } else if (turningVariable == 'L') {
    turningFactor = 1000;
  } else if (turningVariable == 'M') {
    turningFactor = 1200;
  } else if (turningVariable == 'N') {
    turningFactor = 1300;
  } else if (turningVariable == 'O') {
    turningFactor = 1400;
  } else if (turningVariable == 'Q') {
    turningFactor = 1500;
  } else if (turningVariable == 'S') {
    turningFactor = 1600;
  } else if (turningVariable == 'T') {
    turningFactor = 1700;
  } else if (turningVariable == 'U') {
    turningFactor = 1800;
  } else if (turningVariable == 'V') {
    turningFactor = 1900;
  }

}

void handleCommand(char cmd) {

  if (cmd == 'P') {
    moveOperator = park;
  } else if (cmd == 'D') {
    moveOperator = cForward;
  } else if (cmd == 'R') {
    moveOperator = cBackward;
  }
  //Serial.print("Turnnin turing_operator : ");
  //Serial.println(turing_operator);
}

void forward() {
  digitalWrite(motorX, HIGH);
  digitalWrite(motorY, LOW);
  analogWrite(mPwm, speedFactor);
  servo.write(turningOperator);

  Serial.print("foword ");
  Serial.println(speedFactor);
  Serial.print("turning ");
  Serial.println(turningOperator);
}

void backward() {
  digitalWrite(motorX, LOW);
  digitalWrite(motorY, HIGH);
  analogWrite(mPwm, speedFactor);
  servo.write(turningOperator);

  Serial.print("backword ");
  Serial.println(speedFactor);
  Serial.print("turning ");
  Serial.println(turningOperator);
}

void cStop() {

  digitalWrite(motorX, LOW);
  digitalWrite(motorY, LOW);
  servo.write(turningOperator);
  Serial.println("Stop ");
}
