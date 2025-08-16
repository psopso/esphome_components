#pragma once
#include "esphome.h"
#include "esphome/components/uart/uart.h"

namespace xt211_dlms {

class Xt211DlmsComponent : public PollingComponent, public esphome::uart::UARTDevice {
 public:
  Xt211DlmsComponent(uart::UARTComponent *parent, int dir_pin) : UARTDevice(parent), dir_pin_(dir_pin) {}
  void setup() override;
  void update() override;

 protected:
  int dir_pin_;
  float voltage_{0};
  float current_{0};

  void parse_frame_();
};

}  // namespace xt211_dlms
