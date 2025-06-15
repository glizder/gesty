#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace paj7620_gesture {

class PAJ7620GestureComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void set_gesture_sensor(text_sensor::TextSensor *sensor) { gesture_sensor_ = sensor; }
 protected:
  text_sensor::TextSensor *gesture_sensor_{nullptr};
};

}  // namespace paj7620_gesture
}  // namespace esphome
