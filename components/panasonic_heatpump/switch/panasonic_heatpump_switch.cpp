#include "panasonic_heatpump_switch.h"
#include "esphome/core/log.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump.switch";

    void PanasonicHeatpumpSwitch::dump_config()
    {
      LOG_SWITCH("", "Panasonic Heatpump Switch", this);
      delay(10);
    }

    void PanasonicHeatpumpSwitch::write_state(bool state)
    {
      this->publish_state(state);
      this->parent_->control_switch(this, state);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
