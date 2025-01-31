#pragma once
#include "esphome/components/number/number.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpNumber : public number::Number, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpNumber() = default;

    protected:
      void control(float value) override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
