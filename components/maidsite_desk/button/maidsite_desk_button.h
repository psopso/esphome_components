#pragma once
#include "esphome/components/button/button.h"
#include "../maidsite_desk.h"


namespace esphome
{
  namespace maidsite_desk
  {
    class MaidsiteDeskButton : public button::Button, public Parented<MaidsiteDeskComponent>
    {
    public:
      MaidsiteDeskButton() = default;

    protected:
      void press_action() override;
    };
  } // namespace maidsite_desk
} // namespace esphome
