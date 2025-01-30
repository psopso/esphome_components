#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif
#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif
#ifdef USE_TEXT_SENSOR
#include "esphome/components/text_sensor/text_sensor.h"
#endif
#include "decode.h"
#include <vector>
#include <string>


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicHeatpumpComponent : public Component
    {
    public:
#ifdef USE_SENSOR
      SUB_SENSOR(top1);
      SUB_SENSOR(top5);
      SUB_SENSOR(top6);
      SUB_SENSOR(top7);
      SUB_SENSOR(top8);
      SUB_SENSOR(top9);
      SUB_SENSOR(top10);
      SUB_SENSOR(top11);
      SUB_SENSOR(top12);
      SUB_SENSOR(top14);
      SUB_SENSOR(top15);
      SUB_SENSOR(top16);
      SUB_SENSOR(top21);
      SUB_SENSOR(top22);
      SUB_SENSOR(top23);
      SUB_SENSOR(top24);
      SUB_SENSOR(top25);
      SUB_SENSOR(top27);
      SUB_SENSOR(top28);
      SUB_SENSOR(top29);
      SUB_SENSOR(top30);
      SUB_SENSOR(top31);
      SUB_SENSOR(top32);
      SUB_SENSOR(top33);
      SUB_SENSOR(top34);
      SUB_SENSOR(top35);
      SUB_SENSOR(top36);
      SUB_SENSOR(top37);
      SUB_SENSOR(top38);
      SUB_SENSOR(top39);
      SUB_SENSOR(top40);
      SUB_SENSOR(top41);
      SUB_SENSOR(top42);
      SUB_SENSOR(top43);
      SUB_SENSOR(top45);
      SUB_SENSOR(top46);
      SUB_SENSOR(top47);
      SUB_SENSOR(top48);
      SUB_SENSOR(top49);
      SUB_SENSOR(top50);
      SUB_SENSOR(top51);
      SUB_SENSOR(top52);
      SUB_SENSOR(top53);
      SUB_SENSOR(top54);
      SUB_SENSOR(top55);
      SUB_SENSOR(top56);
      SUB_SENSOR(top57);
      SUB_SENSOR(top62);
      SUB_SENSOR(top63);
      SUB_SENSOR(top64);
      SUB_SENSOR(top65);
      SUB_SENSOR(top66);
      SUB_SENSOR(top67);
      SUB_SENSOR(top70);
      SUB_SENSOR(top71);
      SUB_SENSOR(top72);
      SUB_SENSOR(top73);
      SUB_SENSOR(top74);
      SUB_SENSOR(top75);
      SUB_SENSOR(top77);
      SUB_SENSOR(top78);
      SUB_SENSOR(top79);
      SUB_SENSOR(top80);
      SUB_SENSOR(top82);
      SUB_SENSOR(top83);
      SUB_SENSOR(top84);
      SUB_SENSOR(top85);
      SUB_SENSOR(top86);
      SUB_SENSOR(top87);
      SUB_SENSOR(top88);
      SUB_SENSOR(top89);
      SUB_SENSOR(top90);
      SUB_SENSOR(top91);
      SUB_SENSOR(top93);
      SUB_SENSOR(top95);
      SUB_SENSOR(top96);
      SUB_SENSOR(top97);
      SUB_SENSOR(top98);
      SUB_SENSOR(top102);
      SUB_SENSOR(top103);
      SUB_SENSOR(top104);
      SUB_SENSOR(top105);
      SUB_SENSOR(top113);
      SUB_SENSOR(top115);
      SUB_SENSOR(top116);
      SUB_SENSOR(top117);
      SUB_SENSOR(top118);
      SUB_SENSOR(top119);
      SUB_SENSOR(top120);
      SUB_SENSOR(top121);
      SUB_SENSOR(top122);
      SUB_SENSOR(top123);
      SUB_SENSOR(top125);
      SUB_SENSOR(top126);
#endif
#ifdef USE_BINARY_SENSOR
      SUB_BINARY_SENSOR(top0);
      SUB_BINARY_SENSOR(top2);
      SUB_BINARY_SENSOR(top3);
      SUB_BINARY_SENSOR(top13);
      SUB_BINARY_SENSOR(top26);
      SUB_BINARY_SENSOR(top60);
      SUB_BINARY_SENSOR(top61);
      SUB_BINARY_SENSOR(top68);
      SUB_BINARY_SENSOR(top69);
      SUB_BINARY_SENSOR(top99);
      SUB_BINARY_SENSOR(top100);
      SUB_BINARY_SENSOR(top108);
      SUB_BINARY_SENSOR(top109);
      SUB_BINARY_SENSOR(top110);
#endif
#ifdef USE_TEXT_SENSOR
      SUB_TEXT_SENSOR(top4);
      SUB_TEXT_SENSOR(top17);
      SUB_TEXT_SENSOR(top18);
      SUB_TEXT_SENSOR(top19);
      SUB_TEXT_SENSOR(top20);
      SUB_TEXT_SENSOR(top44);
      SUB_TEXT_SENSOR(top58);
      SUB_TEXT_SENSOR(top59);
      SUB_TEXT_SENSOR(top76);
      SUB_TEXT_SENSOR(top81);
      SUB_TEXT_SENSOR(top92);
      SUB_TEXT_SENSOR(top94);
      SUB_TEXT_SENSOR(top101);
      SUB_TEXT_SENSOR(top106);
      SUB_TEXT_SENSOR(top107);
      SUB_TEXT_SENSOR(top111);
      SUB_TEXT_SENSOR(top112);
      SUB_TEXT_SENSOR(top114);
      SUB_TEXT_SENSOR(top124);
#endif

      PanasonicHeatpumpComponent() = default;
      float get_setup_priority() const override { return setup_priority::LATE; }
      void dump_config() override;
      void loop() override;

      void set_uart_hp(uart::UARTComponent *uart) { this->uart_hp_ = uart; }
      void set_uart_wm(uart::UARTComponent *uart) { this->uart_wm_ = uart; }

    protected:
      uart::UARTComponent *uart_hp_;
      uart::UARTComponent *uart_wm_;

      std::vector<uint8_t> response_data_;
      std::vector<uint8_t> request_data_;
      uint8_t response_payload_length_;
      uint8_t request_payload_length_;
      bool response_receiving_{false};
      bool request_receiving_{false};

      void decode_response(std::vector<uint8_t> data);
      void send_request();
      void log_uart_hex(std::string prefix, std::vector<uint8_t> bytes, uint8_t separator);
    };
  }  // namespace panasonic_heatpump
}  // namespace esphome