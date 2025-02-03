#include "panasonic_heatpump_switch.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    void PanasonicHeatpumpSwitch::write_state(bool state)
    {
      this->publish_state(state);
      size_t value = state ? 1 : 0;
      this->parent_->switch_control(this, value);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
