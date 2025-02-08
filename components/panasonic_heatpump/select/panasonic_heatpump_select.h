#pragma once
#include "esphome/components/select/select.h"
#include "esphome/core/component.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpSelect : public select::Select, public Component, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpSelect() = default;
      void dump_config() override;

    protected:
      void control(const std::string &value) override;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
