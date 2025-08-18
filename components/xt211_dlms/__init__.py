# prázdné nebo:
import esphome.codegen as cg

from esphome.components import sntp  # Importujeme sntp
DEPENDENCIES = ["sntp"]

xt211_dlms_ns = cg.esphome_ns.namespace("xt211_dlms")
