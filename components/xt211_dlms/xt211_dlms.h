#include "esphome.h"

class Xt211Dlms : public Component, public UARTDevice {
 public:
  // senzory
  static Sensor *total_energy;
  static Sensor *export_energy;
  static Sensor *voltage_L1;
  static Sensor *voltage_L2;
  static Sensor *voltage_L3;
  static Sensor *current_L1;
  static Sensor *current_L2;
  static Sensor *current_L3;
  static Sensor *power_L1;
  static Sensor *power_L2;
  static Sensor *power_L3;
  static Sensor *power_total;

  GPIOPin rs485_dir;

  Xt211Dlms(UARTComponent *parent, GPIOPin dir_pin)
      : UARTDevice(parent), rs485_dir(dir_pin) {
    // inicializace senzorů
    total_energy = new Sensor();
    export_energy = new Sensor();
    voltage_L1 = new Sensor();
    voltage_L2 = new Sensor();
    voltage_L3 = new Sensor();
    current_L1 = new Sensor();
    current_L2 = new Sensor();
    current_L3 = new Sensor();
    power_L1 = new Sensor();
    power_L2 = new Sensor();
    power_L3 = new Sensor();
    power_total = new Sensor();
  }

  void setup() override {
    rs485_dir.setup();
    rs485_dir.digital_write(false); // receive mode
  }

  void loop() override {
    static uint8_t buf[512];
    static int pos = 0;

    while (available()) {
      uint8_t b = read();
      if (b == 0x7E) {
        if (pos > 0) {
          buf[pos++] = b;
          parseFrame(buf, pos);
          pos = 0;
        } else {
          buf[pos++] = b;
        }
      } else {
        if (pos > 0 && pos < sizeof(buf)) buf[pos++] = b;
      }
    }
  }

  void parseFrame(const uint8_t *frame, int len) {
    int llc_index = -1;
    for (int i = 0; i < len - 2; i++) {
      if (frame[i] == 0xE6 && frame[i+1] == 0xE7 && frame[i+2] == 0x00) {
        llc_index = i;
        break;
      }
    }
    if (llc_index < 0) return;

    const uint8_t *apdu = frame + llc_index + 3;
    if (apdu[0] != 0x0F) return; // jen Data-Notification

    int idx = 1;
    if (apdu[idx] == 0x00) {
      idx += 1; // NULL timestamp
    } else {
      int date_len = apdu[idx+1];
      idx += 2 + date_len;
    }

    if (apdu[idx] != 0x01) return;
    int elements = apdu[idx+1];
    idx += 2;

    for (int i = 0; i < elements/2; i++) {
      if (apdu[idx] != 0x09 || apdu[idx+1] != 0x06) return;
      uint8_t obis[6];
      memcpy(obis, apdu+idx+2, 6);
      idx += 8;

      uint8_t valType = apdu[idx];
      if (valType == 0x06) { // integer32
        uint32_t value = (apdu[idx+1] << 24) | (apdu[idx+2] << 16) |
                         (apdu[idx+3] << 8) | apdu[idx+4];
        idx += 5;
        float scaled = value / 1000.0;

        // --- OBIS mapování ---
        if (obis[2] == 1 && obis[3] == 8 && obis[4] == 0) {
          total_energy->publish_state(scaled);
        } else if (obis[2] == 2 && obis[3] == 8 && obis[4] == 0) {
          export_energy->publish_state(scaled);
        } else if (obis[2] == 32 && obis[3] == 7 && obis[4] == 0) {
          voltage_L1->publish_state(scaled);
        } else if (obis[2] == 52 && obis[3] == 7 && obis[4] == 0) {
          voltage_L2->publish_state(scaled);
        } else if (obis[2] == 72 && obis[3] == 7 && obis[4] == 0) {
          voltage_L3->publish_state(scaled);
        } else if (obis[2] == 31 && obis[3] == 7 && obis[4] == 0) {
          current_L1->publish_state(scaled);
        } else if (obis[2] == 51 && obis[3] == 7 && obis[4] == 0) {
          current_L2->publish_state(scaled);
        } else if (obis[2] == 71 && obis[3] == 7 && obis[4] == 0) {
          current_L3->publish_state(scaled);
        } else if (obis[2] == 21 && obis[3] == 7 && obis[4] == 0) {
          power_L1->publish_state(scaled);
        } else if (obis[2] == 41 && obis[3] == 7 && obis[4] == 0) {
          power_L2->publish_state(scaled);
        } else if (obis[2] == 61 && obis[3] == 7 && obis[4] == 0) {
          power_L3->publish_state(scaled);
        } else if (obis[2] == 16 && obis[3] == 7 && obis[4] == 0) {
          power_total->publish_state(scaled);
        }
      } else {
        break;
      }
    }
  }
};

// statické ukazatele
Sensor *Xt211Dlms::total_energy;
Sensor *Xt211Dlms::export_energy;
Sensor *Xt211Dlms::voltage_L1;
Sensor *Xt211Dlms::voltage_L2;
Sensor *Xt211Dlms::voltage_L3;
Sensor *Xt211Dlms::current_L1;
Sensor *Xt211Dlms::current_L2;
Sensor *Xt211Dlms::current_L3;
Sensor *Xt211Dlms::power_L1;
Sensor *Xt211Dlms::power_L2;
Sensor *Xt211Dlms::power_L3;
Sensor *Xt211Dlms::power_total;
