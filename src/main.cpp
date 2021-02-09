#include <Arduino.h>

#define LEFT_EYE    1
#define RIGHT_EYE   2
#define MOUTH_INNER 3
#define MOUTH_OUTER 4

#define PUSH 0

void setup() {
  pinMode(PUSH, 			INPUT_PULLUP);

  pinMode(LEFT_EYE, 		OUTPUT);
  pinMode(RIGHT_EYE, 	OUTPUT);
  pinMode(MOUTH_INNER, 	OUTPUT);
  pinMode(MOUTH_OUTER, 	OUTPUT);
  
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

// the loop function runs over and over again forever
void loop() {  
	digitalWrite(LEFT_EYE, LOW);
	digitalWrite(RIGHT_EYE, HIGH);
	digitalWrite(MOUTH_INNER, LOW);
	digitalWrite(MOUTH_OUTER, HIGH);
	delay(500);
	digitalWrite(LEFT_EYE, HIGH);
	digitalWrite(RIGHT_EYE, LOW);
	digitalWrite(MOUTH_INNER, HIGH);
	digitalWrite(MOUTH_OUTER, LOW);
	delay(500);
}