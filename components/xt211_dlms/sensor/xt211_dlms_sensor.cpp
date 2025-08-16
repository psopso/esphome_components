#include "xt211_dlms_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xt211_dlms {

static const char *const TAG = "xt211_dlms";

void XT211DLMSHub::register_sensor(XT211DLMSSensor *sensor) {
  this->sensors_.push_back(sensor);
}

void XT211DLMSHub::setup() {
  // Inicializace UART a vaší DLMS komunikace
  ESP_LOGCONFIG(TAG, "Inicializace XT211 DLMS hubu...");
}

void XT211DLMSHub::dump_config() {
  ESP_LOGCONFIG(TAG, "XT211 DLMS Hub:");
  for (auto *sensor : this->sensors_) {
    LOG_SENSOR("  ", "Senzor", sensor);
    ESP_LOGCONFIG(TAG, "    OBIS kód: %s", sensor->get_obis_code().c_str());
  }
}

// Tato metoda se volá v intervalu, který nastavíte v YAML pro hub
void XT211DLMSHub::update() {
  ESP_LOGD(TAG, "Zahajuji čtení dat z elektroměru...");

  // Projdete všechny registrované senzory
  for (auto *sensor : this->sensors_) {
    std::string code = sensor->get_obis_code();
    ESP_LOGV(TAG, "Čtení OBIS kódu: %s", code.c_str());

    // Zde zavoláte vaši existující funkci pro čtení dat z elektroměru
    // optional<float> value = this->read_obis_code(code);
    
    // --- Příklad (nahraďte vaší logikou) ---
    float value_from_meter = 0.0f; // Sem přijde hodnota z vaší DLMS funkce
    bool success = true; // Zde bude výsledek vaší DLMS funkce
    
    // Příkladová logika - naplňte `value_from_meter` a `success`
    if (code == "1.8.0") { value_from_meter = 12345.678; }
    else if (code == "1.7.0") { value_from_meter = 350.0; }
    else { success = false; }
    // --- Konec příkladu ---


    if (success) {
      // Pokud je čtení úspěšné, publikujte stav do senzoru
      ESP_LOGD(TAG, "Hodnota pro OBIS %s je %f", code.c_str(), value_from_meter);
      sensor->publish_state(value_from_meter);
    } else {
      // Pokud čtení selže, můžete publikovat NaN nebo logovat chybu
      ESP_LOGW(TAG, "Nepodařilo se přečíst hodnotu pro OBIS kód: %s", code.c_str());
      sensor->publish_state(NAN);
    }
  }
}

}  // namespace xt211_dlms
}  // namespace esphome