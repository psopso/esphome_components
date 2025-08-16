#include "xt211_dlms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xt211_dlms {

static const char *TAG = "xt211_dlms";

Xt211DlmsComponent::Xt211DlmsComponent(esphome::uart::UARTComponent *parent, int dir_pin)
    : esphome::uart::UARTDevice(parent), dir_pin_(dir_pin) {}

void Xt211DlmsComponent::setup() {
  if (dir_pin_ >= 0) {
    pinMode(dir_pin_, OUTPUT);
    digitalWrite(dir_pin_, LOW);  // RX mode
  }
  ESP_LOGCONFIG(TAG, "XT211 DLMS setup, dir_pin=%d, sensors=%d", dir_pin_, (int)sensors_.size());
  frame_pos_ = 0;
  in_frame_ = false;
}

void Xt211DlmsComponent::loop() {
  // čteme datové byty non-blocking z UARTu
  while (this->available()) {
    uint8_t b;
    this->read_byte(&b);
    this->handle_byte_(b);
  }
}

void Xt211DlmsComponent::update() {
  // polling hook (pokud chceš něco periodicky)
}

void Xt211DlmsComponent::handle_byte_(uint8_t b) {
  // Pokud není frame otevřený, startujeme pouze na 0x7E (HDLC) nebo 0x0F (APDU)
  if (!in_frame_) {
    if (b == 0x7E || b == 0x0F) {
      in_frame_ = true;
      frame_pos_ = 0;
      frame_buf_[frame_pos_++] = b;
    }
    return;
  }

  // ukládáme byte
  if (frame_pos_ < MAX_FRAME) {
    frame_buf_[frame_pos_++] = b;
  } else {
    ESP_LOGW(TAG, "Frame too long, resetting");
    in_frame_ = false;
    frame_pos_ = 0;
    return;
  }

  // ukončení rámce na 0x7E
  if (b == 0x7E && frame_pos_ > 1) {
    process_frame_(frame_buf_, frame_pos_);
    in_frame_ = false;
    frame_pos_ = 0;
  }
}

void Xt211DlmsComponent::process_frame_(const uint8_t *frame, int len) {
  ESP_LOGI(TAG, "Received frame len=%d", len);

  // --- zde budeš dělat skutečné parsování podle DLMS/COSEM a OBIS ---
  // Jako kostra: rozparsujeme přítomnost LLC (E6 E7 00) a APDU 0x0F
  int llc_idx = -1;
  for (int i = 0; i + 2 < len; ++i) {
    if (frame[i] == 0xE6 && frame[i+1] == 0xE7 && frame[i+2] == 0x00) {
      llc_idx = i;
      break;
    }
  }

  if (llc_idx >= 0) {
    const uint8_t *apdu = frame + llc_idx + 3;
    int apdu_len = len - (llc_idx + 3);
    if (apdu_len > 0 && apdu[0] == 0x0F) {
      ESP_LOGD(TAG, "Data-Notification APDU detected (len=%d)", apdu_len);

      // TODO: rozparsuj date/time, strukturu a OBIS položky
      // Prozatím: publikuj demo hodnotu do všech zaregistrovaných senzorů
      for (auto s : sensors_) {
        if (s != nullptr) {
          // ukázkově publikujeme index-směrovanou hodnotu, reálně budeš přiřazovat
          s->publish_state((float)apdu_len);  
        }
      }
      return;
    }
  }

  // Fallback - vypsat prvních pár bajtů do logu
  char preview[128];
  int off = 0;
  int n = (len < 32) ? len : 32;
  for (int i = 0; i < n && off < (int)sizeof(preview) - 4; ++i) {
    off += snprintf(preview + off, sizeof(preview) - off, "%02X ", frame[i]);
  }
  ESP_LOGV(TAG, "Frame preview: %s", preview);
}

}  // namespace xt211_dlms
}  // namespace esphome
