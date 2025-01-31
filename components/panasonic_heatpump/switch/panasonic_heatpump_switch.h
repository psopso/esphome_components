#pragma once
#include "esphome/components/switch/switch.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpSwitch : public switch::Switch, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpSwitch() = default;

    protected:
      void write_state(bool state) override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
