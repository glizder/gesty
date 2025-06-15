#pragma once

#include "esphome/core/component.h"
#include "text_sensor/text_sensor.h" // Poprawiona ścieżka dołączenia
#include "i2c/i2c.h"             // Poprawiona ścieżka dołączenia
#include "esphome/core/log.h"

// Stałe adresy rejestrów PAJ7620
#define PAJ7620_ADDRESS 0x73

// Rejestry
#define PAJ7620_REG_BANK_SEL 0xEF // Bank selection register
#define PAJ7620_REG_INT_FLAG1 0x43 // Interrupt Flag 1 (Gesture)
#define PAJ7620_REG_INT_FLAG2 0x44 // Interrupt Flag 2 (Object detection)
#define PAJ7620_REG_STATE_GES 0x43 // Gesture state register

// Wartości gestów
#define PAJ7620_GESTURE_NO_GESTURE 0x00
#define PAJ7620_GESTURE_UP 0x01
#define PAJ7620_GESTURE_DOWN 0x02
#define PAJ7620_GESTURE_LEFT 0x03
#define PAJ7620_GESTURE_RIGHT 0x04
#define PAJ7620_GESTURE_FORWARD 0x05
#define PAJ7620_GESTURE_BACKWARD 0x06
#define PAJ7620_GESTURE_CLOCKWISE 0x07
#define PAJ7620_GESTURE_ANTICLOCKWISE 0x08
#define PAJ7620_GESTURE_WAVE 0x09 // Wave (complex gesture)

namespace esphome {
namespace paj7620_gesture {

// Deklaracja klasy PAJ7620GestureSensor
class PAJ7620GestureSensor : public text_sensor::TextSensor,
                             public PollingComponent,
                             public i2c::I2CDevice {
public:
    PAJ7620GestureSensor();

    void setup() override;
    void update() override;
    void dump_config() override;

protected:
    bool paj7620_init();
    uint8_t read_gesture_data();
    std::string gesture_to_string(uint8_t gesture_code);

    struct RegData {
        uint8_t reg;
        uint8_t data;
    };

    // Pełne dane inicjalizacyjne z Waveshare Wiki / oficjalnych bibliotek
    static const RegData INIT_BANK0_REG_ARRAY[];
    static const uint8_t INIT_BANK0_REG_ARRAY_SIZE;

    static const RegData INIT_BANK1_REG_ARRAY[];
    static const uint8_t INIT_BANK1_REG_ARRAY_SIZE;

    bool write_reg(uint8_t reg, uint8_t data);
    bool read_reg(uint8_t reg, uint8_t *data);
    bool select_bank(uint8_t bank);
};

} // namespace paj7620_gesture
} // namespace esphome
