import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")
Xt211DlmsComponent = xt211_dlms_ns.class_("Xt211DlmsComponent", cg.PollingComponent, uart.UARTDevice)

# schema pro jeden senzor v seznamu
SENSOR_ITEM_SCHEMA = cv.Schema({
    cv.Required("obis"): cv.string,
    cv.Required("name"): cv.string,
    cv.Optional("unit_of_measurement"): cv.string,
    cv.Optional("accuracy_decimals"): cv.int_,
})

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Xt211DlmsComponent),
    cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
    cv.Optional("dir_pin", default=-1): cv.int_,
    cv.Optional("update_interval", default="60s"): cv.string,
    cv.Optional("sensors", default=[]): cv.ensure_list(SENSOR_ITEM_SCHEMA),
}).extend(cv.polling_component_schema("60s"))


async def to_code(config):
    # získat reálný UART objekt
    uart_var = await cg.get_variable(config["uart_id"])

    # vytvořit C++ instanci
    var = cg.new_Pvariable(config[cv.GenerateID()], uart_var, config.get("dir_pin", -1))
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    # zaregistrovat senzory definované v YAML
    for s in config.get("sensors", []):
        # vytvoříme sensor config pro sensor.new_sensor()
        sensor_conf = {
            "name": s["name"],
        }
        if "unit_of_measurement" in s:
            sensor_conf["unit_of_measurement"] = s["unit_of_measurement"]
        if "accuracy_decimals" in s:
            sensor_conf["accuracy_decimals"] = s["accuracy_decimals"]

        sens = await sensor.new_sensor(sensor_conf)
        # přidáme sensor do C++ objektu
        cg.add(var.add_sensor(sens))

    # uložíme seznam OBISů do C++ volitelně (pokud budeš chtít, můžeme to implementovat)
    # prozatím se OBIS konfigurace drží v Pythonu jen pro registraci senzorů
