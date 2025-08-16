# In sensor.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    CONF_NAME,
#    CONF_OBIS_CODE,
    # ... import other constants you need like UNIT_WATT, ICON_FLASH etc.
)

CONF_OBIS_CODE = "OBIS Code"

# Závislost na UART komponentě
DEPENDENCIES = ["uart"]

from .. import xt211_dlms_ns, Xt211DlmsComponent

# Deklarace C++ jmenného prostoru
#xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")

# Hlavní třída komponenty (hub)
#XT211DLMSHub = xt211_dlms_ns.class_("XT211DLMSHub", cg.PollingComponent, uart.UARTDevice)

# Třída pro jednotlivý senzor
XT211DLMSSensor = xt211_dlms_ns.class_("XT211DLMSSensor", sensor.Sensor, cg.Component)

# Schéma pro konfiguraci senzoru v YAML
SENSOR_SCHEMA = sensor.sensor_schema(
    unit_of_measurement="kWh",
    #icon=...,
    accuracy_decimals=0,
).extend(
    {
        # Odkaz na hub, ke kterému tento senzor patří
        cv.Required("xt211_dlms_id"): cv.use_id(Xt211DlmsComponent),
        # OBIS kód, který má tento senzor číst
        cv.Required(CONF_OBIS_CODE): cv.string,
    }
)

# Celkové schéma
CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            # Umožní vytvořit více senzorů z této platformy
            cv.GenerateID(): cv.declare_id(XT211DLMSSensor),
        }
    ).extend(SENSOR_SCHEMA),
)


# Funkce, která převede YAML konfiguraci na C++ kód
async def to_code(config):
    # Najde hub podle zadaného ID
    hub = await cg.get_variable(config["xt211_dlms_id"])
    # Vytvoří novou instanci senzoru
    var = cg.new_Pvariable(config[CONF_ID])
    
    # Inicializace senzoru
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    # Nastavení OBIS kódu
    cg.add(var.set_obis_code(config[CONF_OBIS_CODE]))
    
    # Zaregistrování senzoru u hubu - TOTO JE KLÍČOVÉ!
    cg.add(hub.register_sensor(var))
