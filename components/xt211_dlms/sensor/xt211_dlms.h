#pragma once

#include <vector>
#include <string>

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

//Pro wifi ntp
#include "esphome/core/hal.h"
#include "esphome/components/network/ip_address.h"
#include "esphome/core/application.h"
#include "esphome/components/time/real_time_clock.h"
#include "esphome/components/time/sntp_component.h"

namespace esphome {
namespace xt211_dlms {

// Dědíme z PollingComponent + uart::UARTDevice (správná cesta v ESPHome)
class Xt211Dlms : public PollingComponent, public uart::UARTDevice {
 public:
  // konstruktor bez parametrů – UART se naváže přes uart.register_uart_device()
  Xt211Dlms() = default;

  void set_dir_pin(int pin) { this->dir_pin_ = pin; }
  void add_sensor(sensor::Sensor *sensor, const std::string &obis) {
    this->sensors_.push_back(sensor);
    this->obis_codes_.push_back(obis);
  }

  void setup() override;
  void loop() override;
  void update() override;
  void dump_config() override;

 protected:
  int dir_pin_{-1};

  // definice podřízených senzorů
  std::vector<sensor::Sensor *> sensors_;
  std::vector<std::string> obis_codes_;

  // jednoduchý RX buffer pro RX dump/parsování
  static constexpr size_t BUF_SIZE = 1024;
  uint8_t rx_buf_[BUF_SIZE];
  size_t rx_len_{0};

  void handle_byte_(uint8_t b);
  void try_parse_frame_();  // místo pro budoucí DLMS/COSEM parser
};

private:
  void synchronize_time() {
    // 1. Získáme ukazatel na globální SNTP komponentu
    sntp::SNTPComponent *sntp_component = App.get_sntp();

    // 2. Zkontrolujeme, zda SNTP komponenta existuje (byla definována v YAML)
    if (sntp_component != nullptr) {
        ESP_LOGD(TAG, "Vyvolávám synchronizaci času přes SNTP komponentu.");
        // 3. Zavoláme metodu pro synchronizaci. Tato metoda je interní, ale funguje.
        // V novějších verzích ESPHome může být potřeba použít jiný přístup,
        // ale tento je nejběžnější.
        sntp_component->request_sync();

        // Po úspěšné synchronizaci můžete pracovat s aktuálním časem
        // Například:
        auto time_now = App.get_time(); // Získáme časovou komponentu
        if (time_now->is_valid()) {
            ESP_LOGI(TAG, "Aktuální čas je: %s", time_now->now().strftime("%Y-%m-%d %H:%M:%S").c_str());
        } else {
            ESP_LOGW(TAG, "Čas ještě není synchronizován.");
        }

    } else {
        ESP_LOGW(TAG, "SNTP komponenta není v konfiguraci YAML definována!");
    }
  }
};

}  // namespace xt211_dlms
}  // namespace esphome
