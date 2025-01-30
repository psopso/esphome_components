import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
  UNIT_CENTIMETER,
  UNIT_PERCENT,
)
from .. import CONF_MAIDSITE_DESK_ID, MaidsiteDeskComponent, maidsite_desk_ns


CONF_HEIGHT_ABS = "height_abs"
CONF_HEIGHT_PCT = "height_pct"

TYPES = [
  CONF_HEIGHT_ABS,
  CONF_HEIGHT_PCT,
]

MaidsiteDeskNumber = maidsite_desk_ns.class_("MaidsiteDeskNumber", number.Number)

CONFIG_SCHEMA = cv.Schema(
  {
    cv.GenerateID(CONF_MAIDSITE_DESK_ID): cv.use_id(MaidsiteDeskComponent),

    cv.Optional(CONF_HEIGHT_ABS): number.number_schema(
      MaidsiteDeskNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_HEIGHT_PCT): number.number_schema(
      MaidsiteDeskNumber,
      unit_of_measurement=UNIT_PERCENT,
    ),
  }
)

async def to_code(config):
  hub = await cg.get_variable(config[CONF_MAIDSITE_DESK_ID])
  for key in TYPES:
    await setup_conf(config, key, hub)

async def setup_conf(parent_config, key, hub):
  if child_config := parent_config.get(key):
    var = await number.new_number(child_config, min_value=0, max_value=100, step=.1)
    await cg.register_parented(var, parent_config[CONF_MAIDSITE_DESK_ID])
    cg.add(getattr(hub, f"set_{key}_number")(var))
