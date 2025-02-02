import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import (
  DEVICE_CLASS_RUNNING,
)
from . import PanasonicHeatpumpComponent, CONF_PANASONIC_HEATPUMP_ID

CONF_TOP0 = "top0"
CONF_TOP2 = "top2"
CONF_TOP3 = "top3"
CONF_TOP13 = "top13"
CONF_TOP26 = "top26"
CONF_TOP60 = "top60"
CONF_TOP61 = "top61"
CONF_TOP68 = "top68"
CONF_TOP69 = "top69"
CONF_TOP99 = "top99"
CONF_TOP100 = "top100"
CONF_TOP108 = "top108"
CONF_TOP109 = "top109"
CONF_TOP110 = "top110"
CONF_TOP119 = "top119"
CONF_TOP120 = "top120"
CONF_TOP121 = "top121"
CONF_TOP122 = "top122"
CONF_TOP123 = "top123"
CONF_TOP124 = "top124"
CONF_TOP129 = "top129"
CONF_TOP132 = "top132"
CONF_TOP133 = "top133"

TYPES = [
  CONF_TOP0,
  CONF_TOP2,
  CONF_TOP3,
  CONF_TOP13,
  CONF_TOP26,
  CONF_TOP60,
  CONF_TOP61,
  CONF_TOP68,
  CONF_TOP69,
  CONF_TOP99,
  CONF_TOP100,
  CONF_TOP108,
  CONF_TOP109,
  CONF_TOP110,
  CONF_TOP119,
  CONF_TOP120,
  CONF_TOP121,
  CONF_TOP122,
  CONF_TOP123,
  CONF_TOP124,
  CONF_TOP129,
  CONF_TOP132,
  CONF_TOP133,
]

CONFIG_SCHEMA = cv.All(
  cv.Schema(
    {
      cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

      cv.Optional(CONF_TOP0): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP2): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP3): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP13): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP26): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP60): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP61): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP68): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP69): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP99): binary_sensor.binary_sensor_schema(
      ),
      cv.Optional(CONF_TOP100): binary_sensor.binary_sensor_schema(
      ),
      cv.Optional(CONF_TOP108): binary_sensor.binary_sensor_schema(
      ),
      cv.Optional(CONF_TOP109): binary_sensor.binary_sensor_schema(
        device_class = DEVICE_CLASS_RUNNING,
      ),
      cv.Optional(CONF_TOP110): binary_sensor.binary_sensor_schema(
      ),
      cv.Optional(CONF_TOP119): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP120): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP121): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP122): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP123): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP124): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP129): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP132): binary_sensor.binary_sensor_schema(),
      cv.Optional(CONF_TOP133): binary_sensor.binary_sensor_schema(),
    }
  ).extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
  hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
  for key in TYPES:
    await setup_conf(config, key, hub)

async def setup_conf(parent_config, key, hub):
  if child_config := parent_config.get(key):
    var = await binary_sensor.new_binary_sensor(child_config)
    cg.add(getattr(hub, f"set_{key}_binary_sensor")(var))
