#include "panasonic_heatpump_number.h"
#include "esphome/core/log.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump.number";

    void PanasonicHeatpumpNumber::dump_config()
    {
      LOG_NUMBER("", "Panasonic Heatpump Number", this);
    }

    void PanasonicHeatpumpNumber::control(float value)
    {
      this->publish_state(value);
      this->parent_->number_control(this, value);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
