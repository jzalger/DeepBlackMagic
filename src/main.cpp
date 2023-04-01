#include <Arduino.h>
#include "sbus.h"

#define RECORD_PIN 0
#define AUX_UP 1
#define AUX_DOWN 2

#define SBUS_HIGH 212
#define SBUS_MID 128
#define SBUS_MIN 44

bool rec_state = false;
bool aux_up_state = false;
bool aux_down_state = false;


void setup() {
  Serial.begin(9600);
  pinMode(RECORD_PIN, INPUT);
  pinMode(AUX_UP, INPUT);
  pinMode(AUX_DOWN, INPUT);
}

void loop() {
  rec_state = digitalRead(RECORD_PIN);
  aux_up_state = digitalRead(AUX_UP);
  aux_down_state = digitalRead(AUX_DOWN);
}