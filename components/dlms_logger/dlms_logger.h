#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <vector>
#include "dlms_logger.h" 
#include "dlms_parser.h" 

std::vector<DlmsRecord> parseDlmsResponse(const uint8_t* buf, size_t len);

namespace esphome {
namespace dlms_logger {

class DlmsLogger : public Component, public uart::UARTDevice {
 public:
  DlmsLogger() = default;  // musí existovat prázdný konstruktor

  void setup() override;
  void loop() override;

 protected:
  std::vector<uint8_t> buffer_;
  bool collecting_{false};
  uint32_t start_time_{0};

  void log_buffer();
};

}  // namespace dlms_logger
}  // namespace esphome
