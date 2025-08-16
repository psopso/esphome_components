#pragma once

#include "esphome/core/component.h"      // PollingComponent
#include "esphome/components/uart/uart.h" // uart::UARTDevice
#include "esphome/core/sensor.h"          // sensor::Sensor

namespace esphome {
namespace xt211_dlms {

class Xt211DlmsComponent : public PollingComponent, public uart::UARTDevice {
 public:
  Xt211DlmsComponent(uart::UARTComponent *parent, int dir_pin);

  void set_voltage_sensor(sensor::Sensor *s) { this->voltage_sensor_ = s; }
  void set_current_sensor(sensor::Sensor *s) { this->current_sensor_ = s; }

  void setup() override;
  void loop() override;
  void update() override;

 protected:
  int dir_pin_{-1};

  static constexpr int MAX_FRAME = 512;
  uint8_t buf_[MAX_FRAME];
  int pos_{0};
  bool in_frame_{false};

  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *current_sensor_{nullptr};

  void handle_byte_(uint8_t b);
  void process_frame_(const uint8_t *frame, int len);
};

}  // namespace xt211_dlms
}  // namespace esphome
