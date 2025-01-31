#pragma once
#include "esphome/components/select/select.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpSelect : public select::Select, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpSelect() = default;

    protected:
      void control(const std::string &value) override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
