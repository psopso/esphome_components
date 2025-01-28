import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
  UNIT_AMPERE,
  UNIT_CELSIUS,
  UNIT_HERTZ,
  UNIT_HOUR,
  UNIT_KELVIN,
  UNIT_MINUTE,
  UNIT_WATT,
  UNIT_EMPTY,
  DEVICE_CLASS_TEMPERATURE,
  DEVICE_CLASS_DURATION,
  DEVICE_CLASS_FREQUENCY,
  DEVICE_CLASS_POWER,
  DEVICE_CLASS_PRESSURE,
  DEVICE_CLASS_CURRENT,
  DEVICE_CLASS_VOLUME_FLOW_RATE,
  STATE_CLASS_MEASUREMENT,
  STATE_CLASS_TOTAL_INCREASING,
  ICON_COUNTER,
)
from . import PanasonicHeatpumpComponent, CONF_PANASONIC_HEATPUMP_ID

UNIT_LITRE_PER_MINUTE = "L/min"
UNIT_ROTATIONS_PER_MINUTE = "r/min"
UNIT_PRESSURE_KGFCM2 = "kgf/cm²"
UNIT_BAR = "bar"

ICON_FAN_SPEED = "mdi:fan"

CONF_SENS_TOP1 = "top1"
CONF_SENS_TOP5 = "top5"
CONF_SENS_TOP6 = "top6"
CONF_SENS_TOP7 = "top7"
CONF_SENS_TOP8 = "top8"
CONF_SENS_TOP9 = "top9"
CONF_SENS_TOP10 = "top10"
CONF_SENS_TOP11 = "top11"
CONF_SENS_TOP12 = "top12"
CONF_SENS_TOP14 = "top14"
CONF_SENS_TOP15 = "top15"
CONF_SENS_TOP16 = "top16"
CONF_SENS_TOP21 = "top21"
CONF_SENS_TOP22 = "top22"
CONF_SENS_TOP23 = "top23"
CONF_SENS_TOP24 = "top24"
CONF_SENS_TOP25 = "top25"
CONF_SENS_TOP27 = "top27"
CONF_SENS_TOP28 = "top28"
CONF_SENS_TOP29 = "top29"
CONF_SENS_TOP30 = "top30"
CONF_SENS_TOP31 = "top31"
CONF_SENS_TOP32 = "top32"
CONF_SENS_TOP33 = "top33"
CONF_SENS_TOP34 = "top34"
CONF_SENS_TOP35 = "top35"
CONF_SENS_TOP36 = "top36"
CONF_SENS_TOP37 = "top37"
CONF_SENS_TOP38 = "top38"
CONF_SENS_TOP39 = "top39"
CONF_SENS_TOP40 = "top40"
CONF_SENS_TOP41 = "top41"
CONF_SENS_TOP42 = "top42"
CONF_SENS_TOP43 = "top43"
CONF_SENS_TOP45 = "top45"
CONF_SENS_TOP46 = "top46"
CONF_SENS_TOP47 = "top47"
CONF_SENS_TOP48 = "top48"
CONF_SENS_TOP49 = "top49"
CONF_SENS_TOP50 = "top50"
CONF_SENS_TOP51 = "top51"
CONF_SENS_TOP52 = "top52"
CONF_SENS_TOP53 = "top53"
CONF_SENS_TOP54 = "top54"
CONF_SENS_TOP55 = "top55"
CONF_SENS_TOP56 = "top56"
CONF_SENS_TOP57 = "top57"
CONF_SENS_TOP62 = "top62"
CONF_SENS_TOP63 = "top63"
CONF_SENS_TOP64 = "top64"
CONF_SENS_TOP65 = "top65"
CONF_SENS_TOP66 = "top66"
CONF_SENS_TOP67 = "top67"
CONF_SENS_TOP70 = "top70"
CONF_SENS_TOP71 = "top71"
CONF_SENS_TOP72 = "top72"
CONF_SENS_TOP73 = "top73"
CONF_SENS_TOP74 = "top74"
CONF_SENS_TOP75 = "top75"
CONF_SENS_TOP77 = "top77"
CONF_SENS_TOP78 = "top78"
CONF_SENS_TOP79 = "top79"
CONF_SENS_TOP80 = "top80"
CONF_SENS_TOP82 = "top82"
CONF_SENS_TOP83 = "top83"
CONF_SENS_TOP84 = "top84"
CONF_SENS_TOP85 = "top85"
CONF_SENS_TOP86 = "top86"
CONF_SENS_TOP87 = "top87"
CONF_SENS_TOP88 = "top88"
CONF_SENS_TOP89 = "top89"
CONF_SENS_TOP90 = "top90"
CONF_SENS_TOP91 = "top91"
CONF_SENS_TOP93 = "top93"
CONF_SENS_TOP95 = "top95"
CONF_SENS_TOP96 = "top96"
CONF_SENS_TOP97 = "top97"
CONF_SENS_TOP98 = "top98"
CONF_SENS_TOP102 = "top102"
CONF_SENS_TOP103 = "top103"
CONF_SENS_TOP104 = "top104"
CONF_SENS_TOP105 = "top105"
CONF_SENS_TOP113 = "top113"
CONF_SENS_TOP115 = "top115"
CONF_SENS_TOP116 = "top116"
CONF_SENS_TOP117 = "top117"
CONF_SENS_TOP118 = "top118"
CONF_SENS_TOP119 = "top119"
CONF_SENS_TOP120 = "top120"
CONF_SENS_TOP121 = "top121"
CONF_SENS_TOP122 = "top122"
CONF_SENS_TOP123 = "top123"
CONF_SENS_TOP125 = "top125"
CONF_SENS_TOP126 = "top126"

TYPES = [
  CONF_SENS_TOP1,
  CONF_SENS_TOP5,
  CONF_SENS_TOP6,
  CONF_SENS_TOP7,
  CONF_SENS_TOP8,
  CONF_SENS_TOP9,
  CONF_SENS_TOP10,
  CONF_SENS_TOP11,
  CONF_SENS_TOP12,
  CONF_SENS_TOP14,
  CONF_SENS_TOP15,
  CONF_SENS_TOP16,
  CONF_SENS_TOP21,
  CONF_SENS_TOP22,
  CONF_SENS_TOP23,
  CONF_SENS_TOP24,
  CONF_SENS_TOP25,
  CONF_SENS_TOP27,
  CONF_SENS_TOP28,
  CONF_SENS_TOP29,
  CONF_SENS_TOP30,
  CONF_SENS_TOP31,
  CONF_SENS_TOP32,
  CONF_SENS_TOP33,
  CONF_SENS_TOP34,
  CONF_SENS_TOP35,
  CONF_SENS_TOP36,
  CONF_SENS_TOP37,
  CONF_SENS_TOP38,
  CONF_SENS_TOP39,
  CONF_SENS_TOP40,
  CONF_SENS_TOP41,
  CONF_SENS_TOP42,
  CONF_SENS_TOP43,
  CONF_SENS_TOP45,
  CONF_SENS_TOP46,
  CONF_SENS_TOP47,
  CONF_SENS_TOP48,
  CONF_SENS_TOP49,
  CONF_SENS_TOP50,
  CONF_SENS_TOP51,
  CONF_SENS_TOP52,
  CONF_SENS_TOP53,
  CONF_SENS_TOP54,
  CONF_SENS_TOP55,
  CONF_SENS_TOP56,
  CONF_SENS_TOP57,
  CONF_SENS_TOP62,
  CONF_SENS_TOP63,
  CONF_SENS_TOP64,
  CONF_SENS_TOP65,
  CONF_SENS_TOP66,
  CONF_SENS_TOP67,
  CONF_SENS_TOP70,
  CONF_SENS_TOP71,
  CONF_SENS_TOP72,
  CONF_SENS_TOP73,
  CONF_SENS_TOP74,
  CONF_SENS_TOP75,
  CONF_SENS_TOP77,
  CONF_SENS_TOP78,
  CONF_SENS_TOP79,
  CONF_SENS_TOP80,
  CONF_SENS_TOP82,
  CONF_SENS_TOP83,
  CONF_SENS_TOP84,
  CONF_SENS_TOP85,
  CONF_SENS_TOP86,
  CONF_SENS_TOP87,
  CONF_SENS_TOP88,
  CONF_SENS_TOP89,
  CONF_SENS_TOP90,
  CONF_SENS_TOP91,
  CONF_SENS_TOP93,
  CONF_SENS_TOP95,
  CONF_SENS_TOP96,
  CONF_SENS_TOP97,
  CONF_SENS_TOP98,
  CONF_SENS_TOP102,
  CONF_SENS_TOP103,
  CONF_SENS_TOP104,
  CONF_SENS_TOP105,
  CONF_SENS_TOP113,
  CONF_SENS_TOP115,
  CONF_SENS_TOP116,
  CONF_SENS_TOP117,
  CONF_SENS_TOP118,
  CONF_SENS_TOP119,
  CONF_SENS_TOP120,
  CONF_SENS_TOP121,
  CONF_SENS_TOP122,
  CONF_SENS_TOP123,
  CONF_SENS_TOP125,
  CONF_SENS_TOP126,
]

CONFIG_SCHEMA = cv.All(
  cv.Schema(
    {
      cv.GenerateID(CONF_PANASONIC_HEATPUMP_ID): cv.use_id(PanasonicHeatpumpComponent),

      cv.Optional(CONF_SENS_TOP1): sensor.sensor_schema(
        device_class=DEVICE_CLASS_VOLUME_FLOW_RATE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_LITRE_PER_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP5): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP6): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP7): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP8): sensor.sensor_schema(
        device_class=DEVICE_CLASS_FREQUENCY,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_HERTZ,
      ),
      cv.Optional(CONF_SENS_TOP9): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP10): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP11): sensor.sensor_schema(
        device_class=DEVICE_CLASS_DURATION,
        state_class=STATE_CLASS_TOTAL_INCREASING,
        unit_of_measurement = UNIT_HOUR,
      ),
      cv.Optional(CONF_SENS_TOP12): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_COUNTER,
      ),
      cv.Optional(CONF_SENS_TOP14): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP15): sensor.sensor_schema(
        device_class=DEVICE_CLASS_POWER,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_WATT,
      ),
      cv.Optional(CONF_SENS_TOP16): sensor.sensor_schema(
        device_class=DEVICE_CLASS_POWER,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_WATT,
      ),
      cv.Optional(CONF_SENS_TOP21): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP22): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP23): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP24): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP25): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP27): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP28): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP29): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP30): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP31): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP32): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP33): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP34): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP35): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP36): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP37): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP38): sensor.sensor_schema(
        device_class=DEVICE_CLASS_POWER,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_WATT,
      ),
      cv.Optional(CONF_SENS_TOP39): sensor.sensor_schema(
        device_class=DEVICE_CLASS_POWER,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_WATT,
      ),
      cv.Optional(CONF_SENS_TOP40): sensor.sensor_schema(
        device_class=DEVICE_CLASS_POWER,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_WATT,
      ),
      cv.Optional(CONF_SENS_TOP41): sensor.sensor_schema(
        device_class=DEVICE_CLASS_POWER,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_WATT,
      ),
      cv.Optional(CONF_SENS_TOP42): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP43): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP45): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP46): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP47): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP48): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP49): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP50): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP51): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP52): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP53): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP54): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP55): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP56): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP57): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP62): sensor.sensor_schema(
        icon=ICON_FAN_SPEED,
        unit_of_measurement = UNIT_ROTATIONS_PER_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP63): sensor.sensor_schema(
        icon=ICON_FAN_SPEED,
        unit_of_measurement = UNIT_ROTATIONS_PER_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP64): sensor.sensor_schema(
        device_class=DEVICE_CLASS_PRESSURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_PRESSURE_KGFCM2,
      ),
      cv.Optional(CONF_SENS_TOP65): sensor.sensor_schema(
        unit_of_measurement = UNIT_ROTATIONS_PER_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP66): sensor.sensor_schema(
        device_class=DEVICE_CLASS_PRESSURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_PRESSURE_KGFCM2,
      ),
      cv.Optional(CONF_SENS_TOP67): sensor.sensor_schema(
        device_class=DEVICE_CLASS_CURRENT,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_AMPERE,
      ),
      cv.Optional(CONF_SENS_TOP70): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP71): sensor.sensor_schema(
        device_class=DEVICE_CLASS_DURATION,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP72): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP73): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP74): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP75): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP77): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP78): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP79): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP80): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP82): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP83): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP84): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP85): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP86): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP87): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP88): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP89): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP90): sensor.sensor_schema(
        device_class=DEVICE_CLASS_DURATION,
        state_class=STATE_CLASS_TOTAL_INCREASING,
        unit_of_measurement = UNIT_HOUR,
      ),
      cv.Optional(CONF_SENS_TOP91): sensor.sensor_schema(
        device_class=DEVICE_CLASS_DURATION,
        state_class=STATE_CLASS_TOTAL_INCREASING,
        unit_of_measurement = UNIT_HOUR,
      ),
      cv.Optional(CONF_SENS_TOP93): sensor.sensor_schema(),
      cv.Optional(CONF_SENS_TOP95): sensor.sensor_schema(),
      cv.Optional(CONF_SENS_TOP96): sensor.sensor_schema(
        device_class=DEVICE_CLASS_DURATION,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP97): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP98): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP102): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP103): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP104): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP105): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP113): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_KELVIN,
      ),
      cv.Optional(CONF_SENS_TOP115): sensor.sensor_schema(
        device_class=DEVICE_CLASS_PRESSURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_BAR,
      ),
      cv.Optional(CONF_SENS_TOP116): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP117): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP118): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP119): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP120): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP121): sensor.sensor_schema(
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_CELSIUS,
      ),
      cv.Optional(CONF_SENS_TOP122): sensor.sensor_schema(
        device_class=DEVICE_CLASS_DURATION,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP123): sensor.sensor_schema(
        device_class=DEVICE_CLASS_DURATION,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement = UNIT_MINUTE,
      ),
      cv.Optional(CONF_SENS_TOP125): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_COUNTER,
      ),
      cv.Optional(CONF_SENS_TOP126): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_COUNTER,
      ),
    }
  ).extend(cv.COMPONENT_SCHEMA)
)

async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        sens = await sensor.new_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_sensor")(sens))

async def to_code(config):
    hub = await cg.get_variable(config[CONF_PANASONIC_HEATPUMP_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
