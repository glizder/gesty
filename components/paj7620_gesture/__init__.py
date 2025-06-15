import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, text_sensor
from esphome.const import CONF_ID

CODEOWNERS = ["@twoj_github"]
DEPENDENCIES = ["i2c"]

paj7620_gesture_ns = cg.esphome_ns.namespace("paj7620_gesture")
PAJ7620GestureComponent = paj7620_gesture_ns.class_(
    "PAJ7620GestureComponent", cg.PollingComponent, i2c.I2CDevice
)

CONF_GESTURE = "gesture"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(PAJ7620GestureComponent),
            cv.Optional(CONF_GESTURE): text_sensor.text_sensor_schema,
            cv.Optional("address", default=0x73): cv.i2c_address,
            cv.Optional("update_interval", default="100ms"): cv.update_interval,
        }
    )
    .extend(i2c.i2c_device_schema(False))
    .extend(cv.polling_component_schema("100ms"))
)

async def to_code(config):
    var = await cg.register_component(config, PAJ7620GestureComponent.new())
    await i2c.register_i2c_device(var, config)
    if CONF_GESTURE in config:
        sens = await text_sensor.new_text_sensor(config[CONF_GESTURE])
        cg.add(var.set_gesture_sensor(sens))
        await text_sensor.register_text_sensor(sens, config[CONF_GESTURE])
