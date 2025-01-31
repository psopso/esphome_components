#pragma once
#include "esphome/components/button/button.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpButton : public button::Button, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpButton() = default;

    protected:
      void press_action() override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
