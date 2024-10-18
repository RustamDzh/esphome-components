#include "wnk811sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace wnk811 {

static const char *const TAG = "wnk811sensor";

void WNK811Component::setup() {
  ESP_LOGD(TAG, "Setting up WNK811sensor...");
}

void WNK811sensorComponent::update() {
  float pressure = read_pressure();
  float temperature = read_temperature();

  if (pressure_sensor_ != nullptr) {
    pressure_sensor_->publish_state(pressure);
  }

  if (temperature_sensor_ != nullptr) {
    temperature_sensor_->publish_state(temperature);
  }
}

float WNK811Component::read_pressure() {
  uint8_t data[3];
  this->read_bytes(0x06, data, 3);

  uint32_t pressure_raw = (static_cast<uint32_t>(data[2]) << 16) | (static_cast<uint32_t>(data[1]) << 8) | data[0];
  float pressure_hpa = static_cast<float>(pressure_raw) / 100.0f;  // Adjust the scaling factor as needed
  float pressure_atm = pressure_hpa / 1013.25f;  // Convert hPa to atm

  ESP_LOGD(TAG, "Pressure: %.2f atm", pressure_atm);
  return pressure_atm;
}

float WNK811Component::read_temperature() {
  uint8_t data[3];
  this->read_bytes(0x09, data, 3);

  uint32_t temperature_raw = (static_cast<uint32_t>(data[2]) << 16) | (static_cast<uint32_t>(data[1]) << 8) | data[0];
  float temperature = static_cast<float>(temperature_raw) / 100.0f;  // Adjust the scaling factor as needed

  ESP_LOGD(TAG, "Temperature: %.2f °C", temperature);
  return temperature;
}

}  // namespace wnk811sensor
}  // namespace esphome