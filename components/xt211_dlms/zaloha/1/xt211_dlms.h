#pragma once
#include "esphome.h"

namespace esphome {
namespace xt211_dlms {

class Xt211Dlms : public PollingComponent {
 public:
  void set_uart(UARTComponent *uart) { this->uart_ = uart; }
  void set_dir_pin(int pin) { this->dir_pin_ = pin; }
  void set_update_interval(uint32_t ms) { this->update_interval_ = ms; }
  void add_sensor(Sensor *sensor, std::string obis) {
    sensors_.push_back(sensor);
    obis_codes_.push_back(obis);
  }

  void setup() override {
    // inicializace UART a DIR PIN
  }

  void update() override {
    // čtení OBIS kódů a aktualizace sensorů
  }

 protected:
  UARTComponent *uart_;
  int dir_pin_;
  uint32_t update_interval_;
  std::vector<Sensor *> sensors_;
  std::vector<std::string> obis_codes_;
};

}  // namespace xt211_dlms
}  // namespace esphome
