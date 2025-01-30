#include "maidsite_desk_button.h"


namespace esphome
{
  namespace maidsite_desk
  {
    void MaidsiteDeskButton::press_action()
    {
      this->parent_->button_press_action(this);
    }
  } // namespace maidsite_desk
} // namespace esphome
