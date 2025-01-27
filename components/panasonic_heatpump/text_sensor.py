import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import (
  DEVICE_CLASS_HEAT,
)
from . import PanasonicHeatpumpComponent, CONF_PANASONIC_HEATPUMP_ID

CONF_TEXT_SENS_TOP4 = "top4"
CONF_TEXT_SENS_TOP17 = "top17"
CONF_TEXT_SENS_TOP18 = "top18"
CONF_TEXT_SENS_TOP19 = "top19"
CONF_TEXT_SENS_TOP20 = "top20"
CONF_TEXT_SENS_TOP44 = "top44"
CONF_TEXT_SENS_TOP58 = "top58"
CONF_TEXT_SENS_TOP59 = "top59"
CONF_TEXT_SENS_TOP76 = "top76"
CONF_TEXT_SENS_TOP81 = "top81"
CONF_TEXT_SENS_TOP92 = "top92"
CONF_TEXT_SENS_TOP94 = "top94"
CONF_TEXT_SENS_TOP101 = "top101"
CONF_TEXT_SENS_TOP106 = "top106"
CONF_TEXT_SENS_TOP107 = "top107"
CONF_TEXT_SENS_TOP111 = "top111"
CONF_TEXT_SENS_TOP112 = "top112"
CONF_TEXT_SENS_TOP114 = "top114"
CONF_TEXT_SENS_TOP124 = "top124"

TYPES = [
  CONF_TEXT_SENS_TOP4,
  CONF_TEXT_SENS_TOP17,
  CONF_TEXT_SENS_TOP18,
  CONF_TEXT_SENS_TOP19,
  CONF_TEXT_SENS_TOP20,
  CONF_TEXT_SENS_TOP44,
  CONF_TEXT_SENS_TOP58,
  CONF_TEXT_SENS_TOP59,
  CONF_TEXT_SENS_TOP76,
  CONF_TEXT_SENS_TOP81,
  CONF_TEXT_SENS_TOP92,
  CONF_TEXT_SENS_TOP94,
  CONF_TEXT_SENS_TOP101,
  CONF_TEXT_SENS_TOP106,
  CONF_TEXT_SENS_TOP107,
  CONF_TEXT_SENS_TOP111,
  CONF_TEXT_SENS_TOP112,
  CONF_TEXT_SENS_TOP114,
  CONF_TEXT_SENS_TOP124,
]

CONFIG_SCHEMA = cv.All(
  cv.Schema(
    {
      cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

      cv.Optional(CONF_TEXT_SENS_TOP4): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP17): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP18): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP19): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP20): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP44): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP58): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP59): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP76): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP81): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP92): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP94): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP101): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP106): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP107): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP111): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP112): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP114): text_sensor.text_sensor_schema(),
      cv.Optional(CONF_TEXT_SENS_TOP124): text_sensor.text_sensor_schema(),
    }
  ).extend(cv.COMPONENT_SCHEMA)
)

async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        sens = await text_sensor.new_text_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))

async def to_code(config):
    hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
