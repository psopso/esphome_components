import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")
Xt211DlmsComponent = xt211_dlms_ns.class_("Xt211DlmsComponent", cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Xt211DlmsComponent),
    cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
    cv.Required("dir_pin"): cv.GPIO_OUTPUT_PIN_SCHEMA,
}).extend(cv.polling_component_schema("1000ms"))

def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()], config["uart_id"], config["dir_pin"])
    cg.add(var)
    cg.register_component(var)
