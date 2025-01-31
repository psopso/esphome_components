import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import select
from esphome.const import (
  UNIT_PERCENT,
)
from .. import CONF_PANASONIC_HEATPUMP_ID, PanasonicHeatpumpComponent, panasonic_heatpump_ns


CONF_SET_QUIET_MODE = "set_quiet_mode"
CONF_SET_POWERFUL_MODE = "set_powerful_mode"
CONF_SET_OPERATION_MODE = "set_operation_mode"
CONF_SET_ZONES = "set_zones"
CONF_SET_EXTERNAL_PAD_HEATER = "set_external_pad_heater"
CONF_SET_POWERFUL_MODE = "set_powerful_mode"
CONF_SET_BIVALENT_MODE = "set_bivalent_mode"

TYPES = [
  CONF_SET_QUIET_MODE,
  CONF_SET_POWERFUL_MODE,
  CONF_SET_OPERATION_MODE,
  CONF_SET_ZONES,
  CONF_SET_EXTERNAL_PAD_HEATER,
  CONF_SET_POWERFUL_MODE,
  CONF_SET_BIVALENT_MODE,
]

PanasonicHeatpumpSelect = panasonic_heatpump_ns.class_("PanasonicHeatpumpSelect", select.Select)

CONFIG_SCHEMA = cv.Schema(
  {
    cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

    cv.Optional(CONF_SET_QUIET_MODE): select.select_schema(
      PanasonicHeatpumpSelect,
    ),
    cv.Optional(CONF_SET_POWERFUL_MODE): select.select_schema(
      PanasonicHeatpumpSelect,
    ),
    cv.Optional(CONF_SET_OPERATION_MODE): select.select_schema(
      PanasonicHeatpumpSelect,
    ),
    cv.Optional(CONF_SET_ZONES): select.select_schema(
      PanasonicHeatpumpSelect,
    ),
    cv.Optional(CONF_SET_EXTERNAL_PAD_HEATER): select.select_schema(
      PanasonicHeatpumpSelect,
    ),
    cv.Optional(CONF_SET_POWERFUL_MODE): select.select_schema(
      PanasonicHeatpumpSelect,
    ),
    cv.Optional(CONF_SET_BIVALENT_MODE): select.select_schema(
      PanasonicHeatpumpSelect,
    ),
  }
)

async def to_code(config):
  hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
  for key in TYPES:
    await setup_conf(config, key, hub)

async def setup_conf(parent_config, key, hub):
  if child_config := parent_config.get(key):
    var = await select.new_select(child_config, options=["dummy1", "dummy2"])
    await cg.register_parented(var, parent_config[CONF_PANASONIC_HEATPUMP_ID])
    cg.add(getattr(hub, f"set_{key}_select")(var))
