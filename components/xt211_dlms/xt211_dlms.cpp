#pragma once

#include "esphome.h"
#include "esphome/components/uart/uart.h"  // <<< toto je klíčové

namespace xt211_dlms {

class Xt211DlmsComponent : public PollingComponent, public esphome::uart::UARTDevice {
 public:
  void setup() override;
  void update() override;

 protected:
  void parse_frame_();
  int dir_pin_;
};

}  // namespace xt211_dlms
