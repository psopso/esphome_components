import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL, UNIT_EMPTY, ICON_FLASH
from esphome.components import sensor, uart

DEPENDENCIES = ["uart"]

xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")
Xt211Dlms = xt211_dlms_ns.class_("Xt211Dlms", cg.PollingComponent)

CONF_UART_ID = "uart_id"
CONF_DIR_PIN = "dir_pin"
CONF_SENSORS = "sensors"
CONF_OBIS = "obis_code"

SENSOR_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_EMPTY,
    icon=ICON_FLASH,
).extend({
    cv.Required(CONF_OBIS): cv.string,
})

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Xt211Dlms),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Required(CONF_DIR_PIN): cv.int_,
    cv.Optional(CONF_UPDATE_INTERVAL, default="5s"): cv.update_interval,
    cv.Optional(CONF_SENSORS): cv.ensure_list(SENSOR_SCHEMA),
}).extend(cv.polling_component_schema("5s"))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # UART
    uart_var = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart(uart_var))

    # DIR pin
    cg.add(var.set_dir_pin(config[CONF_DIR_PIN]))

    # Sensors
    for sens_conf in config.get(CONF_SENSORS, []):
        s = await sensor.new_sensor(sens_conf)
        cg.add(var.add_sensor(s, sens_conf[CONF_OBIS]))
