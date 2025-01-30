#pragma once
#include "esphome/components/number/number.h"
#include "../maidsite_desk.h"


namespace esphome
{
  namespace maidsite_desk
  {
    class MaidsiteDeskNumber : public number::Number, public Parented<MaidsiteDeskComponent>
    {
    public:
      MaidsiteDeskNumber() = default;

    protected:
      void control(float value) override;
    };
  } // namespace maidsite_desk
} // namespace esphome
