#include "panasonic_heatpump_number.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    void PanasonicHeatpumpNumber::control(float value)
    {
      this->publish_state(value);
      this->parent_->number_control(this, value);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
