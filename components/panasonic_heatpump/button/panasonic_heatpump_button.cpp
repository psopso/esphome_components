#include "panasonic_heatpump_button.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    void PanasonicHeatpumpButton::press_action()
    {
      this->parent_->button_press_action(this);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
