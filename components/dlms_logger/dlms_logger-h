#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <vector>

namespace esphome {
namespace dlms_logger {

class DlmsLogger : public Component, public uart::UARTDevice {
 public:
  explicit DlmsLogger(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

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
