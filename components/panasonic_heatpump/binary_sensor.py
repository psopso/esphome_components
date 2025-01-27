import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import (
  DEVICE_CLASS_HEAT,
)
from . import PanasonicHeatpumpComponent, CONF_PANASONIC_HEATPUMP_ID

CONF_BIN_SENS_TOP0 = "top0"
CONF_BIN_SENS_TOP2 = "top2"
CONF_BIN_SENS_TOP3 = "top3"
CONF_BIN_SENS_TOP13 = "top13"
CONF_BIN_SENS_TOP26 = "top26"
CONF_BIN_SENS_TOP60 = "top60"
CONF_BIN_SENS_TOP61 = "top61"
CONF_BIN_SENS_TOP68 = "top68"
CONF_BIN_SENS_TOP69 = "top69"
CONF_BIN_SENS_TOP99 = "top99"
CONF_BIN_SENS_TOP100 = "top100"
CONF_BIN_SENS_TOP108 = "top108"
CONF_BIN_SENS_TOP109 = "top109"
CONF_BIN_SENS_TOP110 = "top110"

TYPES = [
  CONF_BIN_SENS_TOP0,
  CONF_BIN_SENS_TOP2,
  CONF_BIN_SENS_TOP3,
  CONF_BIN_SENS_TOP13,
  CONF_BIN_SENS_TOP26,
  CONF_BIN_SENS_TOP60,
  CONF_BIN_SENS_TOP61,
  CONF_BIN_SENS_TOP68,
  CONF_BIN_SENS_TOP69,
  CONF_BIN_SENS_TOP99,
  CONF_BIN_SENS_TOP100,
  CONF_BIN_SENS_TOP108,
  CONF_BIN_SENS_TOP109,
  CONF_BIN_SENS_TOP110,
]

CONFIG_SCHEMA = cv.All(
  cv.Schema(
    {
      cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

      cv.Optional(CONF_BIN_SENS_TOP0): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP2): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP3): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP13): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP26): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP60): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP61): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP68): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP69): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP99): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP100): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP108): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP109): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_BIN_SENS_TOP110): binary_sensor.binary_sensor_schema(),
    }
  ).extend(cv.COMPONENT_SCHEMA)
)

async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        var = await binary_sensor.new_binary_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_binary_sensor")(var))

async def to_code(config):
    hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
