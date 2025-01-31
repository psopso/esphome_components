import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import button
from esphome.const import (
  ENTITY_CATEGORY_CONFIG,
)
from .. import CONF_PANASONIC_HEATPUMP_ID, PanasonicHeatpumpComponent, panasonic_heatpump_ns


CONF_RESET = "reset"

TYPES = [
  CONF_RESET,
]

PanasonicHeatpumpButton = panasonic_heatpump_ns.class_("PanasonicHeatpumpButton", button.Button)

CONFIG_SCHEMA = cv.Schema(
  {
    cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

    cv.Optional(CONF_RESET): button.button_schema(
      PanasonicHeatpumpButton,
    ),
  }
)

async def to_code(config):
  hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
  for key in TYPES:
    await setup_conf(config, key, hub)

async def setup_conf(parent_config, key, hub):
  if child_config := parent_config.get(key):
    var = await button.new_button(child_config)
    await cg.register_parented(var, parent_config[CONF_PANASONIC_HEATPUMP_ID])
    cg.add(getattr(hub, f"set_{key}_button")(var))
