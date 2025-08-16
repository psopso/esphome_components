#pragma once
#include "esphome.h"

namespace esphome {
namespace xt211_dlms {

struct Xt211DlmsComponent : public PollingComponent, public uart::UARTDevice {
 public:
  float voltage = 0;
  float current = 0;

  Xt211DlmsComponent(uart::UARTComponent *parent, int dir_pin)
      : PollingComponent(1000), uart::UARTDevice(parent), dir_pin_(dir_pin) {}

  void setup() override {
    pinMode(dir_pin_, OUTPUT);
    digitalWrite(dir_pin_, LOW);
    ESP_LOGD("xt211_dlms", "XT211 setup done");
  }

  void update() override {
    while (available()) {
      uint8_t b = read();
      parse_byte(b);
    }
  }

  sensor::Sensor *voltage_sensor{nullptr};
  sensor::Sensor *current_sensor{nullptr};

 protected:
  int dir_pin_;

  static const int MAX_FRAME = 128;
  uint8_t frame_buffer[MAX_FRAME];
  int frame_index = 0;
  bool frame_started = false;

  void parse_byte(uint8_t b) {
    if (!frame_started && b == 0x0F) {
      frame_started = true;
      frame_index = 0;
      frame_buffer[frame_index++] = b;
      return;
    }

    if (frame_started) {
      frame_buffer[frame_index++] = b;
      if (frame_index >= MAX_FRAME) {
        frame_started = false;
        frame_index = 0;
        ESP_LOGW("xt211_dlms", "Frame too long, reset");
      }
      if (b == 0x7E) {
        process_frame(frame_buffer, frame_index);
        frame_started = false;
        frame_index = 0;
      }
    }
  }

  void process_frame(uint8_t *buf, int len) {
    // zde budeš parsovat OBIS podle XT211 dokumentace
    voltage = 230.0 + (rand() % 10 - 5);
    current = 5.0 + (rand() % 100) / 10.0;

    if (voltage_sensor) voltage_sensor->publish_state(voltage);
    if (current_sensor) current_sensor->publish_state(current);

    ESP_LOGD("xt211_dlms", "Frame len=%d, Voltage=%.2fV, Current=%.2fA", len, voltage, current);
  }
};

}  // namespace xt211_dlms
}  // namespace esphome
