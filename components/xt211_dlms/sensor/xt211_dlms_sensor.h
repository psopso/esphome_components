#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include <vector>

namespace esphome {
namespace xt211_dlms {

// Deklarujeme dopředu třídu hubu
class XT211DLMSHub;

// Třída pro jeden senzor
class XT211DLMSSensor : public sensor::Sensor, public Component {
 public:
  void set_obis_code(const std::string &obis_code) { this->obis_code_ = obis_code; }
  std::string get_obis_code() { return this->obis_code_; }

 protected:
  std::string obis_code_;
};


// Třída pro hlavní hub
class XT211DLMSHub : public PollingComponent, public uart::UARTDevice {
 public:
  // Metoda volaná z 'sensor.py' pro přidání senzoru
  void register_sensor(XT211DLMSSensor *sensor);

  // Standardní ESPHome metody
  void setup() override;
  void dump_config() override;
  void update() override; // Zde bude probíhat čtení dat

 protected:
  // Vektor pro uložení všech vytvořených senzorů
  std::vector<XT211DLMSSensor *> sensors_;
  
  // Zde vaše existující metody pro DLMS komunikaci...
  // např. optional<float> read_obis_code(const std::string &code);
};

}  // namespace xt211_dlms
}  // namespace esphome