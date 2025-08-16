#include "xt211_dlms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xt211_dlms {

static const char *const TAG = "xt211_dlms.sensor";

void Xt211Dlms::setup() {
  ESP_LOGI(TAG, "XT211 DLMS sensor initialized");
  if (this->dir_pin_ >= 0) {
    pinMode(this->dir_pin_, OUTPUT);
    digitalWrite(this->dir_pin_, LOW);
  }
}

void Xt211Dlms::update() {
  ESP_LOGD(TAG, "Polling XT211 DLMS...");

  // Zatím dummy hodnoty
  for (size_t i = 0; i < sensors_.size(); i++) {
    float value = (float) random(100, 1000) / 10.0f;
    ESP_LOGI(TAG, "OBIS %s = %.2f", obis_codes_[i].c_str(), value);
    sensors_[i]->publish_state(value);
  }
}

}  // namespace xt211_dlms
}  // namespace esphome
