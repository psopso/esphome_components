#pragma once

#include <vector>
#include <string>

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

const int SLEEP_MINUTES = 5;

namespace esphome {
namespace xt211_dlms {

// Dědíme z PollingComponent + uart::UARTDevice (správná cesta v ESPHome)
class Xt211Dlms : public PollingComponent, public uart::UARTDevice {
 public:
  // konstruktor bez parametrů – UART se naváže přes uart.register_uart_device()
  Xt211Dlms() = default;

  void set_dir_pin(int pin) { this->dir_pin_ = pin; }
  void add_sensor(sensor::Sensor *sensor, const std::string &obis) {
    this->sensors_.push_back(sensor);
    this->obis_codes_.push_back(obis);
  }

  void setup() override;
  void loop() override;
  void update() override;

 protected:
  int dir_pin_{-1};

  // definice podřízených senzorů
  std::vector<sensor::Sensor *> sensors_;
  std::vector<std::string> obis_codes_;

  // jednoduchý RX buffer pro RX dump/parsování
  static constexpr size_t BUF_SIZE = 1024;
  uint8_t rx_buf_[BUF_SIZE];
  size_t rx_len_{0};

  void handle_byte_(uint8_t b);
  void try_parse_frame_();  // místo pro budoucí DLMS/COSEM parser
};


}  // namespace xt211_dlms
}  // namespace esphome
