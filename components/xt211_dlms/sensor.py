import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import UNIT_WATT_HOUR, ICON_FLASH, STATE_CLASS_TOTAL_INCREASING

DEPENDENCIES = ["uart"]

xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")
Xt211DlmsComponent = xt211_dlms_ns.class_("Xt211DlmsComponent", cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_WATT_HOUR,
        icon=ICON_FLASH,
        accuracy_decimals=0,
        state_class=STATE_CLASS_TOTAL_INCREASING,
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(Xt211DlmsComponent),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.polling_component_schema("60s"))
)

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    await sensor.register_sensor(var, config)
