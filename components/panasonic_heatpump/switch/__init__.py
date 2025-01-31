import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
  UNIT_PERCENT,
)
from .. import CONF_PANASONIC_HEATPUMP_ID, PanasonicHeatpumpComponent, panasonic_heatpump_ns


CONF_SET_HEATPUMP_STATE = "set_heatpump_state"
CONF_SET_HOLIDAY_MODE = "set_holiday_mode"
CONF_SET_FORCE_DHW = "set_force_DHW"
CONF_SET_FORCE_DEFROST = "set_force_defrost"
CONF_SET_FORCE_STERILIZATION = "set_force_sterilization"
CONF_SET_PUMP = "set_pump"
CONF_SET_MAIN_SCHEDULE = "set_main_schedule"
CONF_SET_ALT_EXTERNAL_SENSOR = "set_alt_external_sensor"
CONF_SET_BUFFER = "set_buffer"

TYPES = [
  CONF_SET_HEATPUMP_STATE,
  CONF_SET_HOLIDAY_MODE,
  CONF_SET_FORCE_DHW,
  CONF_SET_FORCE_DEFROST,
  CONF_SET_FORCE_STERILIZATION,
  CONF_SET_PUMP,
  CONF_SET_MAIN_SCHEDULE,
  CONF_SET_ALT_EXTERNAL_SENSOR,
  CONF_SET_BUFFER,
]

PanasonicHeatpumpSwitch = panasonic_heatpump_ns.class_("PanasonicHeatpumpSwitch", switch.Switch)

CONFIG_SCHEMA = cv.Schema(
  {
    cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

    cv.Optional(CONF_SET_HEATPUMP_STATE): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_HOLIDAY_MODE): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_FORCE_DHW): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_FORCE_DEFROST): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_FORCE_STERILIZATION): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_PUMP): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_MAIN_SCHEDULE): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_ALT_EXTERNAL_SENSOR): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
    cv.Optional(CONF_SET_BUFFER): switch.switch_schema(
      PanasonicHeatpumpSwitch,
    ),
  }
)

async def to_code(config):
  hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
  for key in TYPES:
    await setup_conf(config, key, hub)

async def setup_conf(parent_config, key, hub):
  if child_config := parent_config.get(key):
    var = await switch.new_switch(child_config)
    await cg.register_parented(var, parent_config[CONF_PANASONIC_HEATPUMP_ID])
    cg.add(getattr(hub, f"set_{key}_switch")(var))
