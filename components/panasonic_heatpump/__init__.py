import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

CODEOWNERS = ['@elvit']
MULTICONF = True
DEPENDENCIES = ['uart']

CONF_PANASONIC_HEATPUMP_ID = "panasonic_heatpump"
CONF_UART_HP = "uart_hp"    # uart_id
CONF_UART_WM = "uart_wm"    # uart_id_2
CONF_LOG_UART_MSG = "log_uart_msg"
CONF_POLLING_TIME_SEC = "polling_time_in_sec"

panasonic_heatpump_ns = cg.esphome_ns.namespace('panasonic_heatpump')
PanasonicHeatpumpComponent = panasonic_heatpump_ns.class_('PanasonicHeatpumpComponent', cg.Component)  #, uart.UARTDevice)

CONFIG_SCHEMA = (
  cv.Schema(
    {
      cv.GenerateID(): cv.declare_id(PanasonicHeatpumpComponent),

      cv.Required(CONF_UART_HP): cv.use_id(uart.UARTComponent),
      cv.Required(CONF_UART_WM): cv.use_id(uart.UARTComponent),
      cv.Optional(CONF_LOG_UART_MSG, default=False): cv.boolean,
      cv.Optional(CONF_POLLING_TIME_SEC, default=2): cv.int_range(min=1),
    }
  )
  .extend(cv.COMPONENT_SCHEMA)
  # .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
  var = cg.new_Pvariable(config[CONF_ID])
  await cg.register_component(var, config)
  # await uart.register_uart_device(var, config)

  uart_hp = await cg.get_variable(config[CONF_UART_HP])
  cg.add(var.set_uart_hp(uart_hp))
  uart_wm = await cg.get_variable(config[CONF_UART_WM])
  cg.add(var.set_uart_wm(uart_wm))
  cg.add(var.set_log_uart_msg(config[CONF_LOG_UART_MSG]))
  cg.add(var.set_polling_time(config[CONF_POLLING_TIME_SEC]))
