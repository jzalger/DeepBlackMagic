#include <Arduino.h>
#include <HardwareSerial.h>
#include "sbus.h"

#define RECORD_PIN A0
#define AUX_UP_PIN A1
#define AUX_DOWN_PIN A5

#define SBUS_HIGH 2046
#define SBUS_MID 1024
#define SBUS_MIN 0
#define SBUS_DELAY 6
#define SBUS_INC 160
#define SERIAL_RX_PIN 16
#define SERIAL_TX_PIN 17

#define SBUS_REC_CH 0
#define SBUS_IRIS_CH 1
#define SBUS_ISO_CH 2



bool recording = false;
uint8_t iris_index = 0;
uint16_t iris_level = 1748;

struct Button {
  const uint8_t pin;
  bool pressed;
};

bfs::SbusData data;

// Equates to [f1.8, f2, f2.8, f4, f5.6, f8, f11, f16, f22]
//uint8_t apertures[9] = {44, 65, 90, 110, 120, 140, 155, 180, 212};
uint16_t apertures[9] = {300, 460, 620, 780, 940, 1100, 1260, 1420, 1600};

void IRAM_ATTR record_isr();
void IRAM_ATTR aux_up_isr();
void IRAM_ATTR aux_down_isr();

void toggle_sbus();
void init_sbus();
void toggle_record();
void increase_fstop();
void decrease_fstop();