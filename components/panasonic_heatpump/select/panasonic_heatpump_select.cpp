#include "panasonic_heatpump_select.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    void PanasonicHeatpumpSelect::control(const std::string &value)
    {
      this->publish_state(value);
      this->parent_->select_control(this, value);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
