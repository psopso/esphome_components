#pragma once
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpComponent;
    class PanasonicHeatpumpSensor : public sensor::Sensor, public Component, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpSensor() = default;
      void dump_config() override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
