import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import uart
from esphome.const import CONF_ID

CODEOWNERS = ['@elvit']
MULTICONF = True
DEPENDENCIES = ['uart']

CONF_MAIDSITE_DESK_ID = "maidsite_desk"

maidsite_desk_ns = cg.esphome_ns.namespace('maidsite_desk')
MaidsiteDeskComponent = maidsite_desk_ns.class_('MaidsiteDeskComponent', cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = (
  cv.Schema(
    {
      cv.GenerateID(): cv.declare_id(MaidsiteDeskComponent),
    }
  )
  .extend(uart.UART_DEVICE_SCHEMA)
  .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
  var = cg.new_Pvariable(config[CONF_ID])
  await cg.register_component(var, config)
  await uart.register_uart_device(var, config)
