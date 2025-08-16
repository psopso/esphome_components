#include "xt211_dlms.h"

namespace xt211_dlms {

void Xt211DlmsComponent::setup() {
  pinMode(dir_pin_, OUTPUT);
  digitalWrite(dir_pin_, LOW);
}

void Xt211DlmsComponent::update() {
  parse_frame_();
}

void Xt211DlmsComponent::parse_frame_() {
  while (available()) {
    uint8_t b = read();
    // Zde vložte svůj DLMS parser
    // Např. detekce rámce, checksum, dekódování OBIS hodnot
  }
}

}  // namespace xt211_dlms
