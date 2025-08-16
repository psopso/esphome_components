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
    cv.Optional(cv.GenerateID()): cv.declare_id(sensor.Sensor),  # <-- toto přidá ID
})

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Xt211DlmsComponent),
    cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
    cv.Optional("dir_pin", default=-1): cv.int_,
    cv.Optional("update_interval", default="60s"): cv.string,
    cv.Optional("sensors", default=[]): cv.ensure_list(SENSOR_ITEM_SCHEMA),
}).extend(cv.polling_component_schema("60s"))


async def to_code(config):
    uart_var = await cg.get_variable(config["uart_id"])
    var = cg.new_Pvariable(config[cv.GenerateID()], uart_var, config.get("dir_pin", -1))
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

for s in config.get("sensors", []):
    # pokud ID není explicitně v YAML, vytvoříme nový
    sensor_id = s.get(cv.GenerateID())
    if not sensor_id:
        sensor_id = cg.new_Pvariable(cv.declare_id(sensor.Sensor))

    sensor_conf = {
        CONF_ID: sensor_id,
        "name": s["name"],
    }
    if "unit_of_measurement" in s:
        sensor_conf["unit_of_measurement"] = s["unit_of_measurement"]
    if "accuracy_decimals" in s:
        sensor_conf["accuracy_decimals"] = s["accuracy_decimals"]

    sens = await sensor.new_sensor(sensor_conf)
    cg.add(var.add_sensor(sens))
