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
#ifdef USE_BUTTON
#include "esphome/components/button/button.h"
#endif
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_SELECT
#include "esphome/components/select/select.h"
#endif
#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif
#include "decode.h"
#include "commands.h"
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
      SUB_SENSOR(top127);
      SUB_SENSOR(top128);
      SUB_SENSOR(top131);
      SUB_SENSOR(top134);
      SUB_SENSOR(top135);
      SUB_SENSOR(top136);
      SUB_SENSOR(top137);
      SUB_SENSOR(top138);
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
      SUB_BINARY_SENSOR(top119);
      SUB_BINARY_SENSOR(top120);
      SUB_BINARY_SENSOR(top121);
      SUB_BINARY_SENSOR(top122);
      SUB_BINARY_SENSOR(top123);
      SUB_BINARY_SENSOR(top124);
      SUB_BINARY_SENSOR(top129);
      SUB_BINARY_SENSOR(top132);
      SUB_BINARY_SENSOR(top133);
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
      SUB_TEXT_SENSOR(top125);
      SUB_TEXT_SENSOR(top126);
      SUB_TEXT_SENSOR(top130);
#endif
#ifdef USE_BUTTON
      SUB_BUTTON(reset);

      void button_press_action(button::Button* object);
#endif
#ifdef USE_NUMBER
      SUB_NUMBER(z1_heat_request_temperature);
      SUB_NUMBER(z1_cool_request_temperature);
      SUB_NUMBER(z2_heat_request_temperature);
      SUB_NUMBER(z2_cool_request_temperature);
      SUB_NUMBER(dhw_temp);
      SUB_NUMBER(max_pump_duty);
      SUB_NUMBER(zone1_heat_target_high);
      SUB_NUMBER(zone1_heat_target_low);
      SUB_NUMBER(zone1_heat_outside_low);
      SUB_NUMBER(zone1_heat_outside_high);
      SUB_NUMBER(zone2_heat_target_high);
      SUB_NUMBER(zone2_heat_target_low);
      SUB_NUMBER(zone2_heat_outside_low);
      SUB_NUMBER(zone2_heat_outside_high);
      SUB_NUMBER(zone1_cool_target_high);
      SUB_NUMBER(zone1_cool_target_low);
      SUB_NUMBER(zone1_cool_outside_low);
      SUB_NUMBER(zone1_cool_outside_high);
      SUB_NUMBER(zone2_cool_target_high);
      SUB_NUMBER(zone2_cool_target_low);
      SUB_NUMBER(zone2_cool_outside_low);
      SUB_NUMBER(zone2_cool_outside_high);
      SUB_NUMBER(floor_heat_delta);
      SUB_NUMBER(floor_cool_delta);
      SUB_NUMBER(dhw_heat_delta);
      SUB_NUMBER(heater_delay_time);
      SUB_NUMBER(heater_start_delta);
      SUB_NUMBER(heater_stop_delta);
      SUB_NUMBER(buffer_delta);
      SUB_NUMBER(heatingoffoutdoortemp);
      SUB_NUMBER(bivalent_start_temperature);
      SUB_NUMBER(bivalent_stop_temperature);

      void number_control(number::Number* object, float value);
#endif
#ifdef USE_SELECT
      SUB_SELECT(quiet_mode);
      SUB_SELECT(powerful_mode);
      SUB_SELECT(operation_mode);
      SUB_SELECT(zones);
      SUB_SELECT(external_pad_heater);
      SUB_SELECT(powerful_mode2);
      SUB_SELECT(bivalent_mode);

      void select_control(select::Select* object, const std::string &value);
#endif
#ifdef USE_SWITCH
      SUB_SWITCH(heatpump_state);
      SUB_SWITCH(holiday_mode);
      SUB_SWITCH(force_dhw);
      SUB_SWITCH(force_defrost);
      SUB_SWITCH(force_sterilization);
      SUB_SWITCH(pump);
      SUB_SWITCH(main_schedule);
      SUB_SWITCH(alt_external_sensor);
      SUB_SWITCH(buffer);

      void switch_control(switch::Switch* object, bool state);
#endif

      PanasonicHeatpumpComponent() = default;
      float get_setup_priority() const override { return setup_priority::LATE; }
      void dump_config() override;
      void loop() override;

      void set_uart_hp(uart::UARTComponent *uart) { this->uart_hp_ = uart; }
      void set_uart_wm(uart::UARTComponent *uart) { this->uart_wm_ = uart; }
      void set_log_uart_msg(bool enable) { this->log_uart_msg_ = enable; }
      void set_polling_time(uint32_t time_sec) { this->polling_time_ = time_sec; }

    protected:
      uart::UARTComponent *uart_hp_;
      uart::UARTComponent *uart_wm_;
      bool log_uart_msg_{false};
      uint32_t polling_time_{1};

      std::vector<uint8_t> response_message_;
      std::vector<uint8_t> request_message_;
      std::vector<uint8_t> command_message_;
      uint8_t response_payload_length_;
      uint8_t request_payload_length_;
      bool response_receiving_{false};
      bool request_receiving_{false};
      bool forward_requests_{true};

      void decode_response(std::vector<uint8_t> data);
      void send_initial_message();
      void send_periodical_message();
      void send_command_message(uint8_t value, uint8_t index);
      void log_uart_hex(std::string prefix, std::vector<uint8_t> bytes, uint8_t separator);
    };
  }  // namespace panasonic_heatpump
}  // namespace esphome
