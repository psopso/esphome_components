import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import uart
import esphome.const as const

dlms_logger_ns = cg.esphome_ns.namespace("dlms_logger")

DlmsLogger = dlms_logger_ns.class_("DlmsLogger", cg.Component, uart.UARTDevice)

DEPENDENCIES = ["uart"]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DlmsLogger),
    }
).extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
