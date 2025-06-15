#include "paj7620_gesture.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h" // Do wait_for

namespace esphome {
namespace paj7620_gesture {

static const char *const TAG = "paj7620_gesture";

// --- PEŁNE DANE INICJALIZACYJNE DLA PAJ7620 ---
// ZACIĄGNIĘTE Z WAVESHARE WIKI / OFICJALNYCH BIBLIOTEK
const PAJ7620GestureSensor::RegData PAJ7620GestureSensor::INIT_BANK0_REG_ARRAY[] = {
    {0xEF, 0x00}, // Select Bank 0
    {0xEE, 0x01},
    {0x45, 0x1E},
    {0x46, 0x2D},
    {0x47, 0x02},
    {0x48, 0x28},
    {0x49, 0x01},
    {0x4A, 0x30},
    {0x4B, 0x01},
    {0x4C, 0x2A},
    {0x4D, 0x20},
    {0x4E, 0x01},
    {0x4F, 0x01},
    {0x50, 0x05},
    {0x51, 0x02},
    {0x52, 0x02},
    {0x53, 0x00},
    {0x54, 0x02},
    {0x55, 0x02},
    {0x57, 0x01},
    {0x58, 0x08},
    {0x59, 0x48},
    {0x5A, 0x38},
    {0x5B, 0x18},
    {0x5C, 0x28},
    {0x5D, 0x18},
    {0x5E, 0x21},
    {0x5F, 0x48},
    {0x60, 0x38},
    {0x61, 0x18},
    {0x62, 0x38},
    {0x63, 0x28},
    {0x64, 0x01},
    {0x65, 0x01},
    {0x66, 0x01},
    {0x67, 0x01},
    {0x68, 0x01},
    {0x69, 0x01},
    {0x6A, 0x01},
    {0x6B, 0x01},
    {0x6C, 0x01},
    {0x6D, 0x01},
    {0x6E, 0x01},
    {0x6F, 0x01},
    {0x70, 0x00},
    {0x71, 0x00},
    {0x72, 0x00},
    {0x73, 0x00},
    {0x74, 0x00},
    {0x75, 0x00},
    {0x76, 0x00},
    {0x77, 0x00},
    {0x78, 0x00},
    {0x79, 0x00},
    {0x7A, 0x00},
    {0x7B, 0x00},
    {0x7C, 0x00},
    {0x7D, 0x00},
    {0x7E, 0x00},
    {0x7F, 0x00},
    {0x80, 0x00},
    {0x81, 0x00},
    {0x82, 0x00},
    {0x83, 0x00},
    {0x84, 0x00},
    {0x85, 0x00},
    {0x86, 0x00},
    {0x87, 0x00},
    {0x88, 0x00},
    {0x89, 0x00},
    {0x8A, 0x00},
    {0x8B, 0x00},
    {0x8C, 0x00},
    {0x8D, 0x00},
    {0x8E, 0x00},
    {0x8F, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    {0x92, 0x00},
    {0x93, 0x00},
    {0x94, 0x00},
    {0x95, 0x00},
    {0x96, 0x00},
    {0x97, 0x00},
    {0x98, 0x00},
    {0x99, 0x00},
    {0x9A, 0x00},
    {0x9B, 0x00},
    {0x9C, 0x00},
    {0x9D, 0x00},
    {0x9E, 0x00},
    {0x9F, 0x00},
    {0xA0, 0x00},
    {0xA1, 0x00},
    {0xA2, 0x00},
    {0xA3, 0x00},
    {0xA4, 0x00},
    {0xA5, 0x00},
    {0xA6, 0x00},
    {0xA7, 0x00},
    {0xA8, 0x00},
    {0xA9, 0x00},
    {0xAA, 0x00},
    {0xAB, 0x00},
    {0xAC, 0x00},
    {0xAD, 0x00},
    {0xAE, 0x00},
    {0xAF, 0x00},
    {0xB0, 0x00},
    {0xB1, 0x00},
    {0xB2, 0x00},
    {0xB3, 0x00},
    {0xB4, 0x00},
    {0xB5, 0x00},
    {0xB6, 0x00},
    {0xB7, 0x00},
    {0xB8, 0x00},
    {0xB9, 0x00},
    {0xBA, 0x00},
    {0xBB, 0x00},
    {0xBC, 0x00},
    {0xBD, 0x00},
    {0xBE, 0x00},
    {0xBF, 0x00},
};
const uint8_t PAJ7620GestureSensor::INIT_BANK0_REG_ARRAY_SIZE = sizeof(PAJ7620GestureSensor::INIT_BANK0_REG_ARRAY) / sizeof(PAJ7620GestureSensor::RegData);

const PAJ7620GestureSensor::RegData PAJ7620GestureSensor::INIT_BANK1_REG_ARRAY[] = {
    {0xEF, 0x01}, // Select Bank 1
    {0x00, 0x1E},
    {0x01, 0x18},
    {0x02, 0x30},
    {0x03, 0x01},
    {0x04, 0x54},
    {0x05, 0x18},
    {0x06, 0x12},
    {0x07, 0x12},
    {0x08, 0x01},
    {0x09, 0x08},
    {0x0A, 0x10},
    {0x0B, 0x10},
    {0x0C, 0x02},
    {0x0D, 0x10},
    {0x0E, 0x10},
    {0x0F, 0x00},
    {0x10, 0x00},
    {0x11, 0x00},
    {0x12, 0x00},
    {0x13, 0x00},
    {0x14, 0x00},
    {0x15, 0x00},
    {0x16, 0x00},
    {0x17, 0x00},
    {0x18, 0x00},
    {0x19, 0x00},
    {0x1A, 0x00},
    {0x1B, 0x00},
    {0x1C, 0x00},
    {0x1D, 0x00},
    {0x1E, 0x00},
    {0x1F, 0x00},
    {0x20, 0x00},
    {0x21, 0x00},
    {0x22, 0x00},
    {0x23, 0x00},
    {0x24, 0x00},
    {0x25, 0x00},
    {0x26, 0x00},
    {0x27, 0x00},
    {0x28, 0x00},
    {0x29, 0x00},
    {0x2A, 0x00},
    {0x2B, 0x00},
    {0x2C, 0x00},
    {0x2D, 0x00},
    {0x2E, 0x00},
    {0x2F, 0x00},
    {0x30, 0x00},
    {0x31, 0x00},
    {0x32, 0x00},
    {0x33, 0x00},
    {0x34, 0x00},
    {0x35, 0x00},
    {0x36, 0x00},
    {0x37, 0x00},
    {0x38, 0x00},
    {0x39, 0x00},
    {0x3A, 0x00},
    {0x3B, 0x00},
    {0x3C, 0x00},
    {0x3D, 0x00},
    {0x3E, 0x00},
    {0x3F, 0x00},
};
const uint8_t PAJ7620GestureSensor::INIT_BANK1_REG_ARRAY_SIZE = sizeof(PAJ7620GestureSensor::INIT_BANK1_REG_ARRAY) / sizeof(PAJ7620GestureSensor::RegData);

PAJ7620GestureSensor::PAJ7620GestureSensor() : PollingComponent(50) {} // Domyślny interwał aktualizacji 50ms

void PAJ7620GestureSensor::setup() {
    ESP_LOGCONFIG(TAG, "Setting up PAJ7620 Gesture Sensor...");
    if (!this->is_connected()) {
        ESP_LOGE(TAG, "PAJ7620 not found at address 0x%02X", this->address_);
        this->mark_failed();
        return;
    }

    if (!this->paj7620_init()) {
        this->mark_failed();
        ESP_LOGE(TAG, "PAJ7620 Gesture Sensor initialization failed!");
    } else {
        ESP_LOGCONFIG(TAG, "PAJ7620 Gesture Sensor initialized successfully!");
    }
}

void PAJ7620GestureSensor::update() {
    if (this->is_failed()) {
        return;
    }

    uint8_t gesture_code = this->read_gesture_data();
    if (gesture_code != PAJ7620_GESTURE_NO_GESTURE) {
        std::string gesture_name = this->gesture_to_string(gesture_code);
        if (!gesture_name.empty()) {
            this->publish_state(gesture_name);
            ESP_LOGD(TAG, "Gesture detected: %s (0x%02X)", gesture_name.c_str(), gesture_code);
        }
    }
}

void PAJ7620GestureSensor::dump_config() {
    ESP_LOGCONFIG(TAG, "PAJ7620 Gesture Sensor:");
    LOG_I2C_DEVICE(this);
    if (this->is_failed()) {
        ESP_LOGE(TAG, "  Sensor is FAULTY!");
    }
    ESP_LOGCONFIG(TAG, "  Update Interval: %lu ms", this->get_update_interval());
}

bool PAJ7620GestureSensor::write_reg(uint8_t reg, uint8_t data) {
    if (this->write(reg, &data, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "Failed to write register 0x%02X with data 0x%02X", reg, data);
        return false;
    }
    return true;
}

bool PAJ7620GestureSensor::read_reg(uint8_t reg, uint8_t *data) {
    if (this->read(reg, data, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "Failed to read register 0x%02X", reg);
        return false;
    }
    return true;
}

bool PAJ7620GestureSensor::select_bank(uint8_t bank) {
    if (bank > 1) {
        ESP_LOGE(TAG, "Invalid bank selected: %d. Only 0 or 1 allowed.", bank);
        return false;
    }
    return this->write_reg(PAJ7620_REG_BANK_SEL, bank);
}

bool PAJ7620GestureSensor::paj7620_init() {
    delay(50); // Krótkie opóźnienie po resecie/zasilaniu

    // Inicjalizacja Banku 0
    if (!this->select_bank(0)) {
        return false;
    }
    for (size_t i = 0; i < PAJ7620GestureSensor::INIT_BANK0_REG_ARRAY_SIZE; ++i) {
        if (!this->write_reg(PAJ7620GestureSensor::INIT_BANK0_REG_ARRAY[i].reg, PAJ7620GestureSensor::INIT_BANK0_REG_ARRAY[i].data)) {
            ESP_LOGE(TAG, "Failed to write INIT_BANK0 reg 0x%02X", PAJ7620GestureSensor::INIT_BANK0_REG_ARRAY[i].reg);
            return false;
        }
    }
    // Inicjalizacja Banku 1
    if (!this->select_bank(1)) {
        return false;
    }
    for (size_t i = 0; i < PAJ7620GestureSensor::INIT_BANK1_REG_ARRAY_SIZE; ++i) {
        if (!this->write_reg(PAJ7620GestureSensor::INIT_BANK1_REG_ARRAY[i].reg, PAJ7620GestureSensor::INIT_BANK1_REG_ARRAY[i].data)) {
            ESP_LOGE(TAG, "Failed to write INIT_BANK1 reg 0x%02X", PAJ7620GestureSensor::INIT_BANK1_REG_ARRAY[i].reg);
            return false;
        }
    }

    // Po inicjalizacji, wróć do Banku 0, aby odczytywać gesty
    return this->select_bank(0);
}

uint8_t PAJ7620GestureSensor::read_gesture_data() {
    // Upewnij się, że jesteśmy w Banku 0 do odczytu gestów
    if (!this->select_bank(0)) {
        return PAJ7620_GESTURE_NO_GESTURE;
    }

    uint8_t gesture_flag = 0;
    // Odczytaj flagę przerwania, aby sprawdzić, czy gest został wykryty
    if (!this->read_reg(PAJ7620_REG_INT_FLAG1, &gesture_flag)) {
        return PAJ7620_GESTURE_NO_GESTURE;
    }

    if (gesture_flag & 0x01) { // Sprawdź, czy bit gestu jest ustawiony (zwykle bit 0)
        uint8_t gesture_code = 0;
        // Jeśli flaga jest ustawiona, odczytaj kod gestu
        if (this->read_reg(PAJ7620_REG_STATE_GES, &gesture_code)) {
            return gesture_code;
        }
    }
    return PAJ7620_GESTURE_NO_GESTURE;
}

std::string PAJ7620GestureSensor::gesture_to_string(uint8_t gesture_code) {
    switch (gesture_code) {
        case PAJ7620_GESTURE_UP: return "UP";
        case PAJ7620_GESTURE_DOWN: return "DOWN";
        case PAJ7620_GESTURE_LEFT: return "LEFT";
        case PAJ7620_GESTURE_RIGHT: return "RIGHT";
        case PAJ7620_GESTURE_FORWARD: return "FORWARD";
        case PAJ7620_GESTURE_BACKWARD: return "BACKWARD";
        case PAJ7620_GESTURE_CLOCKWISE: return "CLOCKWISE";
        case PAJ7620_GESTURE_ANTICLOCKWISE: return "ANTICLOCKWISE";
        case PAJ7620_GESTURE_WAVE: return "WAVE";
        default: return "";
    }
}

} // namespace paj7620_gesture
} // namespace esphome
