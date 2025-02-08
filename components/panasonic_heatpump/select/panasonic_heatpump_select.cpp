#include "panasonic_heatpump_select.h"
#include "esphome/core/log.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump.select";

    void PanasonicHeatpumpSelect::dump_config()
    {
      LOG_SELECT("", "Panasonic Heatpump Select", this);
    }

    void PanasonicHeatpumpSelect::control(const std::string &value)
    {
      this->publish_state(value);
      auto index = this->active_index();
      if (index.has_value())
        this->parent_->select_control(this, index.value());
    }
  } // namespace panasonic_heatpump
} // namespace esphome
