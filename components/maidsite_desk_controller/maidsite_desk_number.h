#pragma once

#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace maidsite_desk_controller
  {

    class MaidsiteDeskController;

    class MaidsiteDeskNumber : public number::Number, public Component
    {
    private:
      int type;
      MaidsiteDeskController *parent;

    public:
      void setup() override;
      void dump_config() override;

      void set_parent(MaidsiteDeskController *parent) { this->parent = parent; }
      void set_type(int type) { this->type = type; }

      void set_min_value(float value);
      void set_max_value(float value);

    protected:
      void control(float value) override;
    };

  } // namespace maidsite_desk_controller
} // namespace esphome
