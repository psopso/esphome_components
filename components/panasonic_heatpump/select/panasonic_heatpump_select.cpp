#include "panasonic_heatpump_select.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    void PanasonicHeatpumpSelect::control(const std::string &value)
    {
      this->publish_state(value);
      auto index = this->active_index();
      if (index.has_value())
        this->parent_->select_control(this, index.value());
    }
  } // namespace panasonic_heatpump
} // namespace esphome
