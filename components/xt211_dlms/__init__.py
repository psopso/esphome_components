import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    UNIT_VOLT,
    UNIT_AMPERE,
    ICON_FLASH,
    ICON_CURRENT_AC,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_CURRENT,
)

DEPENDENCIES = ["uart"]

xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")
Xt211DlmsComponent = xt211_dlms_ns.class_(
    "Xt211DlmsComponent", cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Xt211DlmsComponent),
        cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
        cv.Required("dir_pin"): cv.gpio_pin,
        cv.Optional("voltage"): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=1,
            icon=ICON_FLASH,
            device_class=DEVICE_CLASS_VOLTAGE,
        ),
        cv.Optional("current"): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            accuracy_decimals=2,
            icon=ICON_CURRENT_AC,
            device_class=DEVICE_CLASS_CURRENT,
        ),
    }
).extend(cv.polling_component_schema("60s"))


async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID], await cg.get_variable(config["uart_id"]), config["dir_pin"])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if "voltage" in config:
        sens = await sensor.new_sensor(config["voltage"])
        cg.add(var.set_voltage_sensor(sens))

    if "current" in config:
        sens = await sensor.new_sensor(config["current"])
        cg.add(var.set_current_sensor(sens))
