#pragma once
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/core/component.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpBinarySensor : public binary_sensor::BinarySensor, public Component, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpBinarySensor() = default;
      void dump_config() override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
