/*
    Author: Emre Şahin, Arda Peçel
    Date: 04.02.2019
    Version: v1.1
*/
///////////////////////////////////
const int relay_pin = 8;
const int pir_threshold = 200;
int pir_threshold_counter = pir_threshold;
///////////////////////////////////
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(7, 6); // RX,TX
bool bt_state;
bool lamp_state;
///////////////////////////////////
int pir_val = 0;
int pir_sensor = 2;
///////////////////////////////////

bool pir_fonc() {
  pir_val = digitalRead(pir_sensor);
  if (pir_val == HIGH) {
    return true;
  } else {
    return false;
  }
}


void relay(bool shutdown = false) {
  if (shutdown) {
    digitalWrite(relay_pin, LOW);
  } else if (bt_state) {
    if (lamp_state) {
      digitalWrite(relay_pin, HIGH);
    } else {
      digitalWrite(relay_pin, LOW);
    }
  } else if (pir_fonc()) {
    pir_threshold_counter = 0;
    digitalWrite(relay_pin, HIGH);
  }
  else {
    pir_threshold_counter += 1;
    delay(50);
    if (pir_threshold_counter >= pir_threshold) {
      digitalWrite(relay_pin, LOW);
      pir_threshold_counter = 0;
    }
  }
}

void bt_func() {
  if (bluetooth.available()) {
    char data = bluetooth.read();
    if (data == '0') {
      bt_state = true;
      lamp_state = false;
    } else if (data == '1') {
      bt_state = true;
      lamp_state = true;
    } else if (data == 'x') {
      bt_state = false;
    }
  }
}

void setup() {
  pinMode(relay_pin, OUTPUT);
  bluetooth.begin(9600);
  pinMode(pir_sensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  bt_func();
  relay();
}



/* TO DO LIST
  1) role bagla +
  2) role fonksıyonu +
  3) pir bagla
  4) pir fonksiyonu +
  5) toparla
  6) bluetooth bagla
  7) bluetooth kodu +
*/
