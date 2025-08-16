#include "xt211_dlms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xt211_dlms {

static const char *const TAG = "xt211_dlms";

Xt211DlmsComponent::Xt211DlmsComponent(uart::UARTComponent *parent, int dir_pin)
    : uart::UARTDevice(parent), dir_pin_(dir_pin) {}

void Xt211DlmsComponent::setup() {
  if (this->dir_pin_ >= 0) {
    pinMode(this->dir_pin_, OUTPUT);
    digitalWrite(this->dir_pin_, LOW);  // RX mód (pro push nepotřebujeme TX)
  }
  ESP_LOGCONFIG(TAG, "Setup done (dir_pin=%d)", this->dir_pin_);
}

void Xt211DlmsComponent::loop() {
  // průběžné čtení z UARTu
  while (this->available()) {
    const uint8_t b = this->read();
    this->handle_byte_(b);
  }
}

void Xt211DlmsComponent::update() {
  // záměrně prázdné – vše řešíme v loop()
}

void Xt211DlmsComponent::handle_byte_(uint8_t b) {
  if (!this->in_frame_) {
    // start – zachytíme buď HDLC FLAG 0x7E, nebo rovnou APDU Data-Notification 0x0F (některé implementace posílají bez HDLC)
    if (b == 0x7E || b == 0x0F) {
      this->in_frame_ = true;
      this->pos_ = 0;
      this->buf_[this->pos_++] = b;
    }
    return;
  }

  // uvnitř rámce
  if (this->pos_ < MAX_FRAME) {
    this->buf_[this->pos_++] = b;
  } else {
    ESP_LOGW(TAG, "Frame too long, dropping");
    this->in_frame_ = false;
    this->pos_ = 0;
    return;
  }

  // jednoduché ukončení rámce:
  //  - pokud začal 0x7E (HDLC), končí také 0x7E
  //  - pokud začal 0x0F (APDU), často také končí 0x7E (záleží na implementaci)
  if (b == 0x7E) {
    this->process_frame_(this->buf_, this->pos_);
    this->in_frame_ = false;
    this->pos_ = 0;
  }
}

void Xt211DlmsComponent::process_frame_(const uint8_t *frame, int len) {
  ESP_LOGD(TAG, "Got frame len=%d", len);

  // pokus o detekci LLC a APDU Data-Notification
  int llc = -1;
  for (int i = 0; i <= len - 3; ++i) {
    if (frame[i] == 0xE6 && frame[i + 1] == 0xE7 && frame[i + 2] == 0x00) {
      llc = i;
      break;
    }
  }

  if (llc >= 0 && llc + 3 < len) {
    const uint8_t *apdu = frame + llc + 3;
    const int apdu_len = len - (llc + 3);
    if (apdu_len > 0 && apdu[0] == 0x0F) {
      ESP_LOGV(TAG, "Data-Notification APDU detected (len=%d)", apdu_len);
      // TODO: zde doplň skutečné parsování OBIS dle dokumentace výrobce
      // Pro ověření propojení (kompilace a publikace) pošleme demo hodnoty:
      if (this->voltage_sensor_ != nullptr) this->voltage_sensor_->publish_state(230.0f);
      if (this->current_sensor_ != nullptr) this->current_sensor_->publish_state(5.0f);
      return;
    }
  }

  // fallback: pokud jsme nenašli LLC/APDU, jen zalogujeme prvních pár bajtů
  char preview[64];
  int n = (len < 16) ? len : 16;
  int off = 0;
  for (int i = 0; i < n && off < (int)sizeof(preview) - 3; ++i) {
    off += snprintf(preview + off, sizeof(preview) - off, "%02X ", frame[i]);
  }
  ESP_LOGV(TAG, "Frame preview: %s", preview);
}

}  // namespace xt211_dlms
}  // namespace esphome
