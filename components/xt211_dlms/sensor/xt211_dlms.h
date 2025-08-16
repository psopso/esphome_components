#pragma once
#include "esphome.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace xt211_dlms {

class Xt211Dlms : public PollingComponent {
 public:
  void set_uart(uart::UARTComponent *uart) { this->uart_ = uart; }
  void set_dir_pin(int pin) { this->dir_pin_ = pin; }
  void add_sensor(sensor::Sensor *sensor, const std::string &obis) {
    sensors_.push_back(sensor);
    obis_codes_.push_back(obis);
  }

  void setup() override;
  void update() override;

 protected:
  uart::UARTComponent *uart_;
  int dir_pin_;
  std::vector<sensor::Sensor *> sensors_;
  std::vector<std::string> obis_codes_;
};

}  // namespace xt211_dlms
}  // namespace esphome
