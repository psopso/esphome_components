#pragma once
#include "esphome/components/number/number.h"
#include "esphome/core/component.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpNumber : public number::Number, public Component, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpNumber() = default;
      void dump_config() override;

    protected:
      void control(float value) override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
