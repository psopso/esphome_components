#include "dlms_logger.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dlms_logger {

static const char *const TAG = "dlms_logger";

// implementace konstruktoru
//DlmsLogger::DlmsLogger(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

void DlmsLogger::setup() {
  buffer_.clear();
  collecting_ = false;
  start_time_ = 0;
}

void DlmsLogger::loop() {
  while (available()) {
    uint8_t b;
    read_byte(&b);

    if (!collecting_) {
      collecting_ = true;
      buffer_.clear();
      start_time_ = millis();
    }
    buffer_.push_back(b);
  }

  if (collecting_ && (millis() - start_time_ > 20000)) {
    log_buffer();
    collecting_ = false;
    buffer_.clear();
  }
}

void DlmsLogger::log_buffer() {
  if (buffer_.empty()) return;
  std::string out;
  char tmp[8];
  for (size_t i = 0; i < buffer_.size(); i++) {
    snprintf(tmp, sizeof(tmp), "0x%02X", buffer_[i]);
    out += tmp;
    if (i < buffer_.size() - 1) out += ",";
  }

  // Maximální délka zprávy, co ESP_LOGI spolkne najednou
  const size_t chunk_size = 400;

  for (size_t i = 0; i < out.size(); i += chunk_size) {
      ESP_LOGI(TAG, "%s", out.substr(i, chunk_size).c_str());
  }
  //ESP_LOGI(TAG, "Paket: %s", out.c_str());
}

}  // namespace dlms_logger
}  // namespace esphome
