#include "panasonic_heatpump_switch.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    void PanasonicHeatpumpSwitch::write_state(bool state)
    {
      this->publish_state(state);
      this->parent_->switch_control(this, state);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
