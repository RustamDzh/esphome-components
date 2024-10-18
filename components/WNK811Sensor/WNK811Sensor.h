#ifndef WNK811_H
#define WNK811_H

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace wnk811sensor {

class WNK811SenorComponent : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;

  void set_pressure_sensor(sensor::Sensor *pressure_sensor) { pressure_sensor_ = pressure_sensor; }
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }

 protected:
  sensor::Sensor *pressure_sensor_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};

  float read_pressure();
  float read_temperature();
};

}  // namespace wnk811sensor
}  // namespace esphome

#endif  // WNK811_H