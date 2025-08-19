#include "xt211_dlms.h"

namespace esphome {
namespace xt211_dlms {

static const char *const TAG = "xt211_dlms.sensor";
int LOOP_COUNTER;

void Xt211Dlms::setup() {
  ESP_LOGI(TAG, "XT211 DLMS init (dir_pin=%d, sensors=%u)", this->dir_pin_, (unsigned)this->sensors_.size());
  if (this->dir_pin_ >= 0) {
    pinMode(this->dir_pin_, OUTPUT);
    digitalWrite(this->dir_pin_, LOW);  // RX mód pro RS485 transceiver
  }
  this->rx_len_ = 0;
}

void Xt211Dlms::loop() {
  // Non-blocking čtení UARTu přes UARTDevice API
//  while (this->available()) {
//    uint8_t b;
//    if (!this->read_byte(&b)) break;
//    this->handle_byte_(b);
//  }
//  delay(10000);
  uint64_t sleep_us = (uint64_t)SLEEP_MINUTES * 60ULL * 1000000ULL;
  LOOP_COUNTER = LOOP_COUNTER + 1;
  if (LOOP_COUNTER > 1000) {
    ESP_LOGI(TAG, "XT211 DLMS LOOP: %d", LOOP_COUNTER);
    LOOP_COUNTER = 0;
    esp_sleep_enable_timer_wakeup(sleep_us);
    esp_deep_sleep_start();
  };
//  Serial.println("Going to deep sleep...");
//  esp_sleep_enable_timer_wakeup(sleep_us);
//  esp_deep_sleep_start();
  
}

void Xt211Dlms::update() {
  // ZATÍM: demo – publikuj „živé“ hodnoty, abys viděl, že senzory fungují.
  // Až bude parser, smažeme a budeme publikovat skutečné hodnoty z try_parse_frame_().
  for (size_t i = 0; i < this->sensors_.size(); i++) {
    float v = (millis() % 10000) / 100.0f + i;  // pseudo-hodnota
    ESP_LOGI(TAG, "Publish demo: %s = %.2f", this->obis_codes_[i].c_str(), v);
    this->sensors_[i]->publish_state(v);
  }
}

void Xt211Dlms::handle_byte_(uint8_t b) {
  if (this->rx_len_ < BUF_SIZE) {
    this->rx_buf_[this->rx_len_++] = b;
    // jednoduché detekování HDLC konce rámce (0x7E)
    if (b == 0x7E && this->rx_len_ > 1) {
      this->try_parse_frame_();
      this->rx_len_ = 0;
    }
  } else {
    ESP_LOGW(TAG, "RX buffer overflow, dropping frame");
    this->rx_len_ = 0;
  }
}

void Xt211Dlms::try_parse_frame_() {
  // Zatím jen hex dump (prvních ~64 B), pro ověření příjmu
  char line[128];
  int off = 0;
  size_t n = this->rx_len_ < 64 ? this->rx_len_ : 64;
  for (size_t i = 0; i < n && off < (int)sizeof(line) - 4; i++) {
    off += snprintf(line + off, sizeof(line) - off, "%02X ", this->rx_buf_[i]);
  }
  ESP_LOGV(TAG, "RX (%u B): %s", (unsigned)this->rx_len_, line);

  // TODO: zde později DLMS/COSEM parsování (LLC E6 E7 00, APDU 0x0F Data-Notification apod.)
}

/*
void XT211DlmsSensor::update() {
  // Čteme všechny dostupné bajty z UARTu
  std::vector<uint8_t> data;
  while (this->available()) {
    data.push_back(this->read());
  }

  if (!data.empty()) {
    // Vypíšeme hex dump
    char buf[6];
    std::string hex_line;
    for (uint8_t b : data) {
      snprintf(buf, sizeof(buf), "%02X ", b);
      hex_line += buf;
    }
    ESP_LOGI(TAG, "UART HEX: %s", hex_line.c_str());
  }
}
*/

}  // namespace xt211_dlms
}  // namespace esphome
