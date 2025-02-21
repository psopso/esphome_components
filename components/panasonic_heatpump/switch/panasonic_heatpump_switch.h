#pragma once
#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"
#include "../panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpSwitch : public switch_::Switch, public Component, public Parented<PanasonicHeatpumpComponent>
    {
    public:
      PanasonicHeatpumpSwitch() = default;
      void dump_config() override;
      void set_id(int id) { this->id_ = id; }

    protected:
      void write_state(bool state) override;
      int id_;
    };
  } // namespace panasonic_heatpump
} // namespace esphome
