#include "paj7620_gesture.h"

namespace esphome {
namespace paj7620_gesture {

void PAJ7620GestureComponent::setup() {
  // Tutaj dodaj kod inicjalizacji czujnika (i2c begin, reset, itp.)
}

void PAJ7620GestureComponent::update() {
  // Tutaj umieść kod odczytu gestu z PAJ7620
  // Na start: publikujemy stałą wartość do testu (zobaczysz to w Home Assistant)
  if (gesture_sensor_) {
    gesture_sensor_->publish_state("no_gesture");
  }
}

}  // namespace paj7620_gesture
}  // namespace esphome
