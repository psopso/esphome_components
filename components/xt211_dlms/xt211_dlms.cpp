#include "xt211_dlms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xt211_dlms {

static const char *const TAG = "xt211_dlms";

void Xt211DlmsComponent::setup() {
  ESP_LOGI(TAG, "XT211 DLMS component setup");
}

void Xt211DlmsComponent::update() {
  ESP_LOGD(TAG, "Polling XT211 meter...");
  // TODO: načtení rámce z UART
  this->parse_frame_();
}

void Xt211DlmsComponent::parse_frame_() {
  ESP_LOGD(TAG, "Parsing frame (dummy implementation)");
  if (this->energy_sensor != nullptr) {
    this->energy_sensor->publish_state(12345);  // test hodnota
  }
}

}  // namespace xt211_dlms
}  // namespace esphome
