#pragma once
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/component.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpTextSensor : public text_sensor::TextSensor, public Component, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpTextSensor() = default;
      void dump_config() override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
