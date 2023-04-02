#include <Arduino.h>
#include <HardwareSerial.h>
#include "sbus.h"

#define RECORD_PIN A0
#define AUX_UP_PIN A1
#define AUX_DOWN_PIN A5

#define SBUS_HIGH 212
#define SBUS_MID 128
#define SBUS_MIN 44
#define SERIAL_RX_PIN 16
#define SERIAL_TX_PIN 17

#define SBUS_REC_CH 0
#define SBUS_IRIS_CH 1
#define SBUS_ISO_CH 2

bool rec_state = false;
bool aux_up_state = false;
bool aux_down_state = false;

struct Button {
  const uint8_t pin;
  bool pressed;
};

// Equates to [f1.8, f2, f2.8, f4, f5.6, f8, f11, f16, f22]
uint8_t apertures[9] = {44, 65, 90, 110, 120, 140, 155, 180, 212};

void IRAM_ATTR record_isr();
void IRAM_ATTR aux_up_isr();
void IRAM_ATTR aux_down_isr();

void toggle_record();
void increase_fstop();
void decrease_fstop();