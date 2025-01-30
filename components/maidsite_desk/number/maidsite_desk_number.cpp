#include "maidsite_desk_number.h"


namespace esphome
{
  namespace maidsite_desk
  {
    void MaidsiteDeskNumber::control(float value)
    {
      this->publish_state(value);
      this->parent_->number_control(this, value);
    }
  } // namespace maidsite_desk
} // namespace esphome
