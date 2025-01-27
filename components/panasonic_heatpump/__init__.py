import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID, CONF_ADDRESS

CODEOWNERS = ['@elvit']
MULTICONF = True
DEPENDENCIES = ['uart']

CONF_PANASONIC_HEATPUMP_ID = "panasonic_heatpump"
CONF_UART_HP = "uart_hp"
CONF_UART_WM = "uart_wm"

panasonic_heatpump_ns = cg.esphome_ns.namespace('panasonic_heatpump')
PanasonicHeatpumpComponent = panasonic_heatpump_ns.class_('PanasonicHeatpumpComponent', cg.Component)

CONFIG_SCHEMA = (
  cv.Schema(
    {
      cv.GenerateID(): cv.declare_id(PanasonicHeatpumpComponent),
      
      cv.Required(CONF_UART_HP): cv.use_id(uart.UARTComponent),
      cv.Required(CONF_UART_WM): cv.use_id(uart.UARTComponent),
    }
  ).extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
  var = cg.new_Pvariable(config[CONF_ID])
  await cg.register_component(var, config)

  uart_hp = await cg.get_variable(config[CONF_UART_HP])
  cg.add(var.set_uart_hp(uart_hp))

  uart_wm = await cg.get_variable(config[CONF_UART_WM])
  cg.add(var.set_uart_wm(uart_wm))
