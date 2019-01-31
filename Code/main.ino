/*
    Author: Emre Şahin, Arda Peçel
    Date: 31.01.2019
    Version: v1.0
*/
///////////////////////////////////
const int relay_pin = 8;
///////////////////////////////////
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(7, 8); // RX,TX
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
  } else if (pir_fonc()) {
    digitalWrite(relay_pin, HIGH);
  }
  else {
    digitalWrite(relay_pin, LOW);
  }
}

char bt_funct() {
  if (bluetooth.available())
  {
    char data = bluetooth.read();
    Serial.print("Gelen Veri: ");
    Serial.println(data);

    if (data == '0') {
      relay(true);
    } else if (data == '1') {
      relay(false);
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
