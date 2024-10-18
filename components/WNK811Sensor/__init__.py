import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, i2c
from esphome.const import (
    CONF_ID,
    CONF_PRESSURE,
    CONF_TEMPERATURE
)

AUTO_LOAD = ["sensor"]
DEPENDENCIES = ["i2c"]

wnk811sensor_ns = cg.esphome_ns.namespace("wnk811sensor")
WNK811Sensor = wnk811sensor_ns.class_("WNK811Sensor", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(WNK811SensorComponent),
    cv.Optional(CONF_PRESSURE): sensor.sensor_schema(
        unit_of_measurement="atm",  # Указываем единицу измерения в атмосферах
        accuracy_decimals=2,
        device_class=sensor.DEVICE_CLASS_PRESSURE,
        state_class=sensor.STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
        unit_of_measurement="°C",
        accuracy_decimals=2,
        device_class=sensor.DEVICE_CLASS_TEMPERATURE,
        state_class=sensor.STATE_CLASS_MEASUREMENT,
    ),
}).extend(i2c.i2c_device_schema(0x6D))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_PRESSURE in config:
        sens = await sensor.new_sensor(config[CONF_PRESSURE])
        cg.add(var.set_pressure_sensor(sens))

    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(sens))