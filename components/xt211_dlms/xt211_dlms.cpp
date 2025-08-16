#include "xt211_dlms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xt211_dlms {

static const char *const TAG = "xt211_dlms";

Xt211DlmsComponent::Xt211DlmsComponent(uart::UARTComponent *parent, int dir_pin)
    : uart::UARTDevice(parent), dir_pin_(dir_pin) {}

void Xt211DlmsComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up XT211 DLMS component...");
  this->pos_ = 0;
  this->in_frame_ = false;
}

void Xt211DlmsComponent::loop() {
  while (this->available()) {
    uint8_t b;
    this->read_byte(&b);
    this->handle_byte_(b);
  }
}

void Xt211DlmsComponent::update() {
  ESP_LOGD(TAG, "Polling XT211 meter...");
  // TODO: implement request/response if needed
}

void Xt211DlmsComponent::handle_byte_(uint8_t b) {
  if (!in_frame_) {
    if (b == 0x7E) {  // start flag
      in_frame_ = true;
      pos_ = 0;
      buf_[pos_++] = b;
    }
    return;
  }

  buf_[pos_++] = b;
  if (pos_ >= MAX_FRAME) {
    in_frame_ = false;
    pos_ = 0;
    return;
  }

  if (b == 0x7E && pos_ > 1) {
    process_frame_(buf_, pos_);
    in_frame_ = false;
    pos_ = 0;
  }
}

void Xt211DlmsComponent::process_frame_(const uint8_t *frame, int len) {
  ESP_LOGI(TAG, "Got frame of %d bytes", len);

  // Dummy example: parse some values
  if (len > 10) {
    float voltage = frame[5] + (frame[6] / 100.0f);
    float current = frame[7] / 10.0f;

    if (this->voltage_sensor_)
      this->voltage_sensor_->publish_state(voltage);

    if (this->current_sensor_)
      this->current_sensor_->publish_state(current);
  }
}

}  // namespace xt211_dlms
}  // namespace esphome
