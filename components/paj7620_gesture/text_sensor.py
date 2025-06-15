import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID

from . import paj7620_gesture_ns, PAJ7620GestureComponent

DEPENDENCIES = ["paj7620_gesture"]

CONFIG_SCHEMA = text_sensor.text_sensor_schema(
    {
        cv.GenerateID(): cv.declare_id(PAJ7620GestureComponent),
    }
)

async def to_code(config):
    paren = await cg.get_variable(config[CONF_ID])
    sens = await text_sensor.new_text_sensor(config)
    cg.add(paren.set_gesture_sensor(sens))
