#include "xt211_dlms.h"

namespace esphome {
namespace xt211_dlms {

static const char *const TAG = "xt211_dlms.sensor";
int LOOP_COUNTER = 0;
int bufferIndex = 0;
int errorCounter = 0;

// Proměnné pro časování
unsigned long startTime = 0;
const unsigned long duration = 20000; // 20 sekund v milisekundách

// Stavy programu
enum State { WAITING, READING, DONE };
State currentState = WAITING;
byte buffer[BUFFER_SIZE];
char ch;

void Xt211Dlms::setup() {
  //delay(10000);
  //ESP_LOGI(TAG, "XT211 DLMS init (dir_pin=%d, sensors=%u)", this->dir_pin_, (unsigned)this->sensors_.size());
  if (this->dir_pin_ >= 0) {
    pinMode(this->dir_pin_, OUTPUT);
    digitalWrite(this->dir_pin_, LOW);  // RX mód pro RS485 transceiver
  }
  this->rx_len_ = 0;
}

void Xt211Dlms::loop() {
  switch (currentState) {
    case WAITING:
      // Čekání na první byte
      if (this -> available() > 0) {
        ESP_LOGI(TAG, "První byte přijat, zahajuji 20s čtení...");
        startTime = millis(); // Zaznamenání času startu
        currentState = READING;
      }
      break;

    case READING:
      // Čtení dat po dobu 20 sekund
      if (millis() - startTime < duration) {
        // Dokud je čas a je co číst
        while (this -> available() > 0 && bufferIndex < BUFFER_SIZE) {
          uint8_t b;
          if (!this->read_byte(&b)) {
            errorCounter ++;
            break;  
          }
          ESP_LOGI(TAG, "Byte: %02X", b);  
          buffer[bufferIndex] = b;
          bufferIndex++;
        }
      } else {
        // Čas vypršel
        ESP_LOGI(TAG, "Čtení dokončeno. Vypisuji buffer: %d   %d", bufferIndex, errorCounter);
        currentState = DONE;
      }
      break;

    case DONE:
      // Výpis bufferu na sériovou linku
      log_hex_array("XT211", buffer, bufferIndex);

      //Serial.println("\nVýpis dokončen. Restartuji...");

      // Resetování proměnných pro další cyklus
      bufferIndex = 0;
      errorCounter = 0;
      currentState = WAITING;
      delay(1000); // Krátká pauza před dalším čekáním
      ESP_LOGI(TAG, "------------------------------------");
      ESP_LOGI(TAG, "Arduino je připraveno a čeká na první byte...");
      break;
  }

// Non-blocking čtení UARTu přes UARTDevice API
//  while (this->available()) {
//    uint8_t b;
//    if (!this->read_byte(&b)) break;
//    this->handle_byte_(b);
//  }
//  delay(10000);
//  uint64_t sleep_us = (uint64_t)SLEEP_MINUTES * 60ULL * 1000000ULL;
//  LOOP_COUNTER = LOOP_COUNTER + 1;
//  if (LOOP_COUNTER > 5000) {
//    ESP_LOGI(TAG, "XT211 DLMS LOOP: %d", LOOP_COUNTER);
//    LOOP_COUNTER = 0;

//    esp_log_level_set("*", ESP_LOG_NONE);   // zastaví další logy
//    uart_wait_tx_idle(CONFIG_ESP_CONSOLE_UART_NUM); // počká na vyprázdnění TX

    //esp_sleep_enable_timer_wakeup(sleep_us);
    //esp_deep_sleep_start();
//  Serial.println("Going to deep sleep...");
//  esp_sleep_enable_timer_wakeup(sleep_us);
//  esp_deep_sleep_start();
  
};

void Xt211Dlms::update() {
  // ZATÍM: demo – publikuj „živé“ hodnoty, abys viděl, že senzory fungují.
  // Až bude parser, smažeme a budeme publikovat skutečné hodnoty z try_parse_frame_().
  for (size_t i = 0; i < this->sensors_.size(); i++) {
    float v = (millis() % 10000) / 100.0f + i;  // pseudo-hodnota
//    ESP_LOGI(TAG, "Publish demo: %s = %.2f", this->obis_codes_[i].c_str(), v);
//    this->sensors_[i]->publish_state(v);
  }
}

void Xt211Dlms::handle_byte_(uint8_t b) {
/*  if (this->rx_len_ < BUF_SIZE) {
    this->rx_buf_[this->rx_len_++] = b;
    // jednoduché detekování HDLC konce rámce (0x7E)
    if (b == 0x7E && this->rx_len_ > 1) {
      this->try_parse_frame_();
      this->rx_len_ = 0;
    }
  } else {
    ESP_LOGW(TAG, "RX buffer overflow, dropping frame");
    this->rx_len_ = 0;
  }*/
}

void Xt211Dlms::try_parse_frame_() {
/*
  // Zatím jen hex dump (prvních ~64 B), pro ověření příjmu
  char line[128];
  int off = 0;
  size_t n = this->rx_len_ < 64 ? this->rx_len_ : 64;
  for (size_t i = 0; i < n && off < (int)sizeof(line) - 4; i++) {
    off += snprintf(line + off, sizeof(line) - off, "%02X ", this->rx_buf_[i]);
  }
//  ESP_LOGV(TAG, "RX (%u B): %s", (unsigned)this->rx_len_, line);

  // TODO: zde později DLMS/COSEM parsování (LLC E6 E7 00, APDU 0x0F Data-Notification apod.)
*/
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

//zaloguje pole bajtů ve formátu 0x..,0x..,...
static void log_hex_array(const char *tag, const uint8_t *data, size_t len) {
    std::string out;
    out.reserve(len * 5);  // cca "0xXX," = 5 znaků na bajt

    ESP_LOGI(tag, "Délka k převodu: %d", len);    

    for (size_t i = 0; i < len; i++) {
        ESP_LOGI(tag, "i: %d", i);    
        char buf[6];
        sprintf(buf, "0x%02X", data[i]);
        out += buf;
        if (i < len - 1) out += ",";
    }

    ESP_LOGI(tag, "Bytes: %s", out.c_str());
}
