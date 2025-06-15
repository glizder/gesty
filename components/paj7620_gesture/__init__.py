import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, text_sensor
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_UPDATE_INTERVAL, CONF_NAME

# Tworzymy przestrzeń nazw dla naszego komponentu w ESPHome
paj7620_gesture_ns = cg.esphome_ns.namespace("paj7620_gesture")
PAJ7620GestureSensor = paj7620_gesture_ns.class_(
    "PAJ7620GestureSensor",
    text_sensor.TextSensor,
    cg.PollingComponent,
    i2c.I2CDevice
)

# Właściciele kodu (opcjonalne, ale dobra praktyka)
CODEOWNERS = ["@glizder"]

# Zależności komponentu - w tym przypadku potrzebujemy komponentu I2C
DEPENDENCIES = ["i2c"]

# Ten schemat jest teraz dla samego komponentu 'paj7620_gesture'
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(PAJ7620GestureSensor),
        cv.Required(CONF_ID): cv.declare_id(PAJ7620GestureSensor),
        cv.Required(CONF_NAME): cv.string,
        cv.Optional(CONF_ADDRESS, default=0x73): cv.i2c_address,
        cv.Optional(CONF_UPDATE_INTERVAL, default="50ms"): cv.positive_time_period_milliseconds,
    }
).extend(i2c.i2c_device_schema(0x73))


# Ta funkcja 'to_code' jest wywoływana, gdy parser ESPHome napotka sekcję 'paj7620_gesture:' w YAML.
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    cg.add(var.set_name(config[CONF_NAME]))
    await text_sensor.register_text_sensor(var, config)
