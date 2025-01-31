import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
  UNIT_CENTIMETER,
  UNIT_PERCENT,
)
from .. import CONF_PANASONIC_HEATPUMP_ID, PanasonicHeatpumpComponent, panasonic_heatpump_ns


CONF_SET_Z1_HEAT_REQUEST_TEMPERATURE = "set_z1_heat_request_temperature"
CONF_SET_Z1_COOL_REQUEST_TEMPERATURE = "set_z1_cool_request_temperature"
CONF_SET_Z2_HEAT_REQUEST_TEMPERATURE = "set_z2_heat_request_temperature"
CONF_SET_Z2_COOL_REQUEST_TEMPERATURE = "set_z2_cool_request_temperature"
CONF_SET_DHW_TEMP = "set_DHW_temp"
CONF_SET_MAX_PUMP_DUTY = "set_max_pump_duty"
CONF_SET_ZONE1_HEAT_TARGET_HIGH = "set_zone1_heat_target_high"
CONF_SET_ZONE1_HEAT_TARGET_LOW = "set_zone1_heat_target_low"
CONF_SET_ZONE1_HEAT_OUTSIDE_LOW = "set_zone1_heat_outside_low"
CONF_SET_ZONE1_HEAT_OUTSIDE_HIGH = "set_zone1_heat_outside_high"
CONF_SET_ZONE2_HEAT_TARGET_HIGH = "set_zone2_heat_target_high"
CONF_SET_ZONE2_HEAT_TARGET_LOW = "set_zone2_heat_target_low"
CONF_SET_ZONE2_HEAT_OUTSIDE_LOW = "set_zone2_heat_outside_low"
CONF_SET_ZONE2_HEAT_OUTSIDE_HIGH = "set_zone2_heat_outside_high"
CONF_SET_ZONE1_COOL_TARGET_HIGH = "set_zone1_cool_target_high"
CONF_SET_ZONE1_COOL_TARGET_LOW = "set_zone1_cool_target_low"
CONF_SET_ZONE1_COOL_OUTSIDE_LOW = "set_zone1_cool_outside_low"
CONF_SET_ZONE1_COOL_OUTSIDE_HIGH = "set_zone1_cool_outside_high"
CONF_SET_ZONE2_COOL_TARGET_HIGH = "set_zone2_cool_target_high"
CONF_SET_ZONE2_COOL_TARGET_LOW = "set_zone2_cool_target_low"
CONF_SET_ZONE2_COOL_OUTSIDE_LOW = "set_zone2_cool_outside_low"
CONF_SET_ZONE2_COOL_OUTSIDE_HIGH = "set_zone2_cool_outside_high"
CONF_SET_FLOOR_HEAT_DELTA = "set_floor_heat_delta"
CONF_SET_FLOOR_COOL_DELTA = "set_floor_cool_delta"
CONF_SET_DHW_HEAT_DELTA = "set_dhw_heat_delta"
CONF_SET_HEATER_DELAY_TIME = "set_heater_delay_time"
CONF_SET_HEATER_START_DELTA = "set_heater_start_delta"
CONF_SET_HEATER_STOP_DELTA = "set_heater_stop_delta"
CONF_SET_BUFFER_DELTA = "set_buffer_delta"
CONF_SET_HEATINGOFFOUTDOORTEMP = "set_heatingoffoutdoortemp"
CONF_SET_BIVALENT_START_TEMPERATURE = "set_bivalent_start_temperature"
CONF_SET_BIVALENT_STOP_TEMPERATURE = "set_bivalent_stop_temperature"

TYPES = [
  CONF_SET_Z1_HEAT_REQUEST_TEMPERATURE,
  CONF_SET_Z1_COOL_REQUEST_TEMPERATURE,
  CONF_SET_Z2_HEAT_REQUEST_TEMPERATURE,
  CONF_SET_Z2_COOL_REQUEST_TEMPERATURE,
  CONF_SET_DHW_TEMP,
  CONF_SET_MAX_PUMP_DUTY,
  CONF_SET_ZONE1_HEAT_TARGET_HIGH,
  CONF_SET_ZONE1_HEAT_TARGET_LOW,
  CONF_SET_ZONE1_HEAT_OUTSIDE_LOW,
  CONF_SET_ZONE1_HEAT_OUTSIDE_HIGH,
  CONF_SET_ZONE2_HEAT_TARGET_HIGH,
  CONF_SET_ZONE2_HEAT_TARGET_LOW,
  CONF_SET_ZONE2_HEAT_OUTSIDE_LOW,
  CONF_SET_ZONE2_HEAT_OUTSIDE_HIGH,
  CONF_SET_ZONE1_COOL_TARGET_HIGH,
  CONF_SET_ZONE1_COOL_TARGET_LOW,
  CONF_SET_ZONE1_COOL_OUTSIDE_LOW,
  CONF_SET_ZONE1_COOL_OUTSIDE_HIGH,
  CONF_SET_ZONE2_COOL_TARGET_HIGH,
  CONF_SET_ZONE2_COOL_TARGET_LOW,
  CONF_SET_ZONE2_COOL_OUTSIDE_LOW,
  CONF_SET_ZONE2_COOL_OUTSIDE_HIGH,
  CONF_SET_FLOOR_HEAT_DELTA,
  CONF_SET_FLOOR_COOL_DELTA,
  CONF_SET_DHW_HEAT_DELTA,
  CONF_SET_HEATER_DELAY_TIME,
  CONF_SET_HEATER_START_DELTA,
  CONF_SET_HEATER_STOP_DELTA,
  CONF_SET_BUFFER_DELTA,
  CONF_SET_HEATINGOFFOUTDOORTEMP,
  CONF_SET_BIVALENT_START_TEMPERATURE,
  CONF_SET_BIVALENT_STOP_TEMPERATURE,
]

PanasonicHeatpumpNumber = panasonic_heatpump_ns.class_("PanasonicHeatpumpNumber", number.Number)

CONFIG_SCHEMA = cv.Schema(
  {
    cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

    cv.Optional(CONF_SET_Z1_HEAT_REQUEST_TEMPERATURE): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_Z1_COOL_REQUEST_TEMPERATURE): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_Z2_HEAT_REQUEST_TEMPERATURE): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_Z2_COOL_REQUEST_TEMPERATURE): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_DHW_TEMP): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_MAX_PUMP_DUTY): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_HEAT_TARGET_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_HEAT_TARGET_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_HEAT_OUTSIDE_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_HEAT_OUTSIDE_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_HEAT_TARGET_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_HEAT_TARGET_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_HEAT_OUTSIDE_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_HEAT_OUTSIDE_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_COOL_TARGET_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_COOL_TARGET_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_COOL_OUTSIDE_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE1_COOL_OUTSIDE_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_COOL_TARGET_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_COOL_TARGET_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_COOL_OUTSIDE_LOW): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_ZONE2_COOL_OUTSIDE_HIGH): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_FLOOR_HEAT_DELTA): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_FLOOR_COOL_DELTA): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_DHW_HEAT_DELTA): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_HEATER_DELAY_TIME): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_HEATER_START_DELTA): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_HEATER_STOP_DELTA): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_BUFFER_DELTA): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_HEATINGOFFOUTDOORTEMP): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_BIVALENT_START_TEMPERATURE): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
    cv.Optional(CONF_SET_BIVALENT_STOP_TEMPERATURE): number.number_schema(
      PanasonicHeatpumpNumber,
      unit_of_measurement=UNIT_CENTIMETER,
    ),
  }
)

async def to_code(config):
  hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
  for key in TYPES:
    await setup_conf(config, key, hub)

async def setup_conf(parent_config, key, hub):
  if child_config := parent_config.get(key):
    var = await number.new_number(child_config, min_value=0, max_value=100, step=.1)
    await cg.register_parented(var, parent_config[CONF_PANASONIC_HEATPUMP_ID])
    cg.add(getattr(hub, f"set_{key}_number")(var))
