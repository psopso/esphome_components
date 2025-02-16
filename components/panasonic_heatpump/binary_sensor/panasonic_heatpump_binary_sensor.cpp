#include "panasonic_heatpump_binary_sensor.h"
#include "esphome/core/log.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump.binary_sensor";

    void PanasonicHeatpumpBinarySensor::dump_config()
    {
      LOG_BINARY_SENSOR("", "Panasonic Heatpump Binary Sensor", this);
      delay(10);
    }
  } // namespace panasonic_heatpump
} // namespace esphome
