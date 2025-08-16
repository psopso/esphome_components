#pragma once

#include "esphome.h"

namespace esphome {
namespace xt211_dlms {

class Xt211Dlms : public PollingComponent {
 public:
  void setup() override;
  void update() override;

  void add_sensor(sensor::Sensor *sens) { sensors_.push_back(sens); }

 protected:
  std::vector<sensor::Sensor *> sensors_;
};

}  // namespace xt211_dlms
}  // namespace esphome
