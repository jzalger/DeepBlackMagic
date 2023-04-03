#include "main.h"

bfs::SbusTx sbus(&Serial1, SERIAL_RX_PIN, SERIAL_TX_PIN, true);

Button record_btn = {RECORD_PIN, false};
Button aux_up_btn = {AUX_UP_PIN, false};
Button aux_down_btn = {AUX_DOWN_PIN, false};
unsigned long button_time = 0;
unsigned long last_button_time = 0;

// #################################################################################

void IRAM_ATTR record_isr(){
  button_time = millis();
  if (button_time - last_button_time > 500){
    record_btn.pressed = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR aux_up_isr(){
  button_time = millis();
  if (button_time - last_button_time > 500){
    aux_up_btn.pressed = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR aux_down_isr(){
  button_time = millis();
  if (button_time - last_button_time > 500){
    aux_down_btn.pressed = true;
    last_button_time = button_time;
  }
}

// ###################################################################

void setup() {
  Serial.begin(115200);
  pinMode(RECORD_PIN, INPUT_PULLDOWN);
  attachInterrupt(RECORD_PIN, record_isr, HIGH);
  pinMode(AUX_UP_PIN, INPUT_PULLDOWN);
  attachInterrupt(AUX_UP_PIN, aux_up_isr, HIGH);
  pinMode(AUX_DOWN_PIN, INPUT_PULLDOWN);
  attachInterrupt(AUX_DOWN_PIN, aux_down_isr, HIGH);
  sbus.Begin();
}

void loop() {
  if (record_btn.pressed) {
    toggle_record();
    Serial.printf("Toggle Record\n");
    record_btn.pressed = false;
  }
  if (aux_up_btn.pressed) {
    increase_fstop();
    Serial.printf("Increase fstop\n");
    aux_up_btn.pressed = false;
  }
  if (aux_down_btn.pressed) {
    decrease_fstop();
    Serial.printf("Decrease fstop\n");
    aux_down_btn.pressed = false;
  }
}

// ################################################################################

void send_sbus(int ch, int value) {
  //Writes the value for a specific channel to the SBUS
  bfs::SbusData data;
  data.ch[ch] = value;
  sbus.data(data);
  sbus.Write();
}

void toggle_record() {
  // Starts or stops camera recording
  if (recording == false){
    send_sbus(SBUS_REC_CH, SBUS_HIGH);
  } else {
    send_sbus(SBUS_REC_CH, SBUS_MIN);
  }
  
}

void increase_fstop() {
  // Increases the f-stop (closes the aperature) by one stop
  if (iris_index < 8) {
    ++iris_index;
    Serial.printf("Sending aperature val: %d at index %d\n", apertures[iris_index], iris_index);
    send_sbus(SBUS_IRIS_CH, apertures[iris_index]);
  }
}

void decrease_fstop() {
  // Decreases the f-stop (opens the aperature) by one stop
    if (iris_index > 0) {
    --iris_index;
    Serial.printf("Sending aperature val: %d at index %d\n", apertures[iris_index], iris_index);
    send_sbus(SBUS_IRIS_CH, apertures[iris_index]);
  }
}
