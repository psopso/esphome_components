#pragma once
#include "esphome.h"

class Xt211Dlms : public PollingComponent {
 public:
  Xt211Dlms(UARTComponent *parent, int dir_pin)
      : PollingComponent(1000), uart(parent), dir_pin_(dir_pin) {}

  void setup() override {
    pinMode(dir_pin_, OUTPUT);
    digitalWrite(dir_pin_, LOW);
    ESP_LOGD("xt211_dlms", "XT211 setup done");
  }

  void update() override {
    while (uart->available()) {
      uint8_t b = uart->read();
      // Jednoduchý testovací parser: ukládá byte do testové hodnoty
      buffer[buffer_index++] = b;
      if (buffer_index >= sizeof(buffer)) buffer_index = 0;

      // Každý 5. byte vydáme testovou hodnotu
      if (buffer_index % 5 == 0) {
        float voltage = 230.0 + (rand() % 10 - 5);  // simulace ±5 V
        float current = 5.0 + (rand() % 100) / 10.0; // simulace ±5 A
        voltage_sensor->publish_state(voltage);
        current_sensor->publish_state(current);
        ESP_LOGD("xt211_dlms", "Voltage=%.2f V, Current=%.2f A", voltage, current);
      }
    }
  }

  // senzory registrované v YAML
  sensor::Sensor *voltage_sensor = new sensor::Sensor();
  sensor::Sensor *current_sensor = new sensor::Sensor();

 protected:
  UARTComponent *uart;
  int dir_pin_;
  uint8_t buffer[64];
  int buffer_index = 0;
};
