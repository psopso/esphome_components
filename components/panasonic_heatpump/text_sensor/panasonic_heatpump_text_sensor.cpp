#include "panasonic_heatpump_text_sensor.h"
#include "esphome/core/log.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump.text_sensor";

    void PanasonicHeatpumpTextSensor::dump_config()
    {
      LOG_TEXT_SENSOR("", "Panasonic Heatpump Text Sensor", this);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
