import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
  ENTITY_CATEGORY_CONFIG,
)
from .. import CONF_PANASONIC_HEATPUMP_ID, PanasonicHeatpumpComponent, panasonic_heatpump_ns


CONF_SET1 = "set1"
CONF_SET2 = "set2"
CONF_SET10 = "set10"
CONF_SET12 = "set12"
CONF_SET13 = "set13"
CONF_SET14 = "set14"
CONF_SET24 = "set24"
CONF_SET25 = "set25"
CONF_SET28 = "set28"
CONF_SET30 = "set30"
CONF_SET31 = "set31"
CONF_SET32 = "set32"
CONF_SET33 = "set33"
CONF_SET34 = "set34"

TYPES = [
  CONF_SET1,
  CONF_SET2,
  CONF_SET10,
  CONF_SET12,
  CONF_SET13,
  CONF_SET14,
  CONF_SET24,
  CONF_SET25,
  CONF_SET28,
  CONF_SET30,
  CONF_SET31,
  CONF_SET32,
  CONF_SET33,
  CONF_SET34,
]

PanasonicHeatpumpSwitch = panasonic_heatpump_ns.class_("PanasonicHeatpumpSwitch", switch.Switch)

CONFIG_SCHEMA = cv.Schema(
  {
    cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

    cv.Optional(CONF_SET1): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET2): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET10): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET12): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET13): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET14): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET24): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET25): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET28): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET30): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET31): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET32): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET33): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
    ),
    cv.Optional(CONF_SET34): switch.switch_schema(
      PanasonicHeatpumpSwitch,
      entity_category=ENTITY_CATEGORY_CONFIG,
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
