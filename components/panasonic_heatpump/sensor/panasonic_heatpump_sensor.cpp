#include "panasonic_heatpump_sensor.h"
#include "esphome/core/log.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump.sensor";

    void PanasonicHeatpumpSensor::dump_config()
    {
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this);
      delay(10);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
