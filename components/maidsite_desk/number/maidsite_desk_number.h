#pragma once
#include "esphome/components/number/number.h"
#include "esphome/core/component.h"
#include "../maidsite_desk.h"


namespace esphome
{
  namespace maidsite_desk
  {
    class MaidsiteDeskComponent;
    class MaidsiteDeskNumber : public number::Number, public Parented<MaidsiteDeskComponent>
    {
    public:
      MaidsiteDeskNumber() = default;
      void dump_config() override;

    protected:
      void control(float value) override;
    };
  } // namespace maidsite_desk
} // namespace esphome
