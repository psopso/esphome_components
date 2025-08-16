#pragma once

#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace xt211_dlms {

class Xt211DlmsComponent : public PollingComponent, public esphome::uart::UARTDevice {
 public:
  Xt211DlmsComponent(esphome::uart::UARTComponent *parent, int dir_pin);

  // registrace senzoru z Pythonu
  void add_sensor(esphome::sensor::Sensor *s) { this->sensors_.push_back(s); }

  void setup() override;
  void loop() override;
  void update() override;

 protected:
  int dir_pin_{-1};
  std::vector<esphome::sensor::Sensor *> sensors_;

  static constexpr int MAX_FRAME = 1024;
  uint8_t frame_buf_[MAX_FRAME];
  int frame_pos_{0};
  bool in_frame_{false};

  // interní
  void handle_byte_(uint8_t b);
  void process_frame_(const uint8_t *frame, int len);
};

}  // namespace xt211_dlms
}  // namespace esphome
