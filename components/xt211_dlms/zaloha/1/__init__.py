import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL
from esphome.components import uart
from esphome.core import coroutine

DEPENDENCIES = ['uart']

xt211_dlms_ns = cg.esphome_ns.namespace('xt211_dlms')
Xt211Dlms = xt211_dlms_ns.class_('Xt211Dlms', cg.Component)

CONF_DIR_PIN = 'dir_pin'
CONF_SENSORS = 'sensors'

SENSOR_SCHEMA = cv.Schema({
    cv.Required('id'): cv.declare_id(cg.Sensor),
    cv.Required('obis_code'): cv.string,
})

CONFIG_SCHEMA = cv.Schema({
    cv.Required(CONF_ID): cv.declare_id(Xt211Dlms),
    cv.Required('uart_id'): cv.use_id(uart.UART),
    cv.Required(CONF_DIR_PIN): cv.int_,
    cv.Optional(CONF_UPDATE_INTERVAL, default="1s"): cv.time,
    cv.Optional(CONF_SENSORS, default=[]): cv.ensure_list(SENSOR_SCHEMA),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # UART
    uart_var = config['uart_id']
    cg.add(var.set_uart(uart_var))

    # Dir pin
    cg.add(var.set_dir_pin(config[CONF_DIR_PIN]))

    # Update interval
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))

    # Sensors
    for sensor_conf in config.get(CONF_SENSORS, []):
        sens = await cg.get_variable(sensor_conf['id'])
        cg.add(var.add_sensor(sens, sensor_conf['obis_code']))
