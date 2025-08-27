
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL

DEPENDENCIES = ["uart"]

xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")
# DĚDÍ z PollingComponent + uart.UARTDevice (žádné ruční předávání UART*)
Xt211Dlms = xt211_dlms_ns.class_("Xt211Dlms", cg.PollingComponent, uart.UARTDevice)

CONF_DIR_PIN = "dir_pin"
CONF_SENSORS = "sensors"
CONF_OBIS = "obis_code"

SENSOR_SCHEMA = sensor.sensor_schema().extend({
    cv.Required(CONF_OBIS): cv.string,
})

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Xt211Dlms),
    cv.Optional(CONF_DIR_PIN, default=-1): cv.int_,
    cv.Optional(CONF_UPDATE_INTERVAL, default="5s"): cv.update_interval,
    cv.Optional(CONF_SENSORS, default=[]): cv.ensure_list(SENSOR_SCHEMA),
}).extend(cv.polling_component_schema("5s")).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    # registrace komponenty a UART zařízení (z UART_DEVICE_SCHEMA – obsahuje uart_id apod.)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_dir_pin(config[CONF_DIR_PIN]))

    # vytvoření pod-senzorů dle YAML
    for s_conf in config.get(CONF_SENSORS, []):
        s = await sensor.new_sensor(s_conf)          # async v ESPHome 2024/2025+
        cg.add(var.add_sensor(s, s_conf[CONF_OBIS])) # předáme ukazatel a OBIS
