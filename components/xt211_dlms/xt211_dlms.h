#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace xt211_dlms {

class Xt211DlmsComponent : public PollingComponent, public uart::UARTDevice {
 public:
  sensor::Sensor *energy_sensor{nullptr};

  void setup() override;
  void update() override;

 protected:
  void parse_frame_();
};

}  // namespace xt211_dlms
}  // namespace esphome
