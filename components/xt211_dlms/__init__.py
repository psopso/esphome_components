import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL

xt211_dlms_ns = cg.esphome_ns.namespace('xt211_dlms')
Xt211Dlms = xt211_dlms_ns.class_('Xt211Dlms', cg.Component)

CONF_SENSORS = 'sensors'

CONFIG_SCHEMA = cv.Schema({
    cv.Required(CONF_ID): cv.declare_id(Xt211Dlms),
    cv.Optional(CONF_UPDATE_INTERVAL, default="1000ms"): cv.update_interval,
    cv.Optional(CONF_SENSORS, default=[]): cv.ensure_list({
        cv.Required(CONF_ID): cv.declare_id(sensor.Sensor),
        cv.Optional('obis_code'): cv.string,
    }),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var)

    for s_conf in config.get(CONF_SENSORS, []):
        sens = sensor.new_sensor(s_conf)
        cg.add(var.add_sensor(sens))
