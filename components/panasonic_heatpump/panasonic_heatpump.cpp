#include "panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump";

    void PanasonicHeatpumpComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "Panasonic Heatpump");
#ifdef USE_SENSOR
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top1_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top5_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top6_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top7_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top8_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top9_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top10_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top11_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top12_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top14_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top15_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top16_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top21_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top22_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top23_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top24_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top25_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top27_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top28_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top29_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top30_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top31_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top32_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top33_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top34_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top35_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top36_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top37_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top38_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top39_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top40_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top41_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top42_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top43_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top45_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top46_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top47_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top48_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top49_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top50_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top51_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top52_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top53_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top54_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top55_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top56_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top57_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top62_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top63_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top64_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top65_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top66_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top67_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top70_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top71_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top72_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top73_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top74_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top75_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top77_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top78_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top79_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top80_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top82_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top83_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top84_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top85_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top86_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top87_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top88_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top89_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top90_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top91_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top93_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top95_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top96_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top97_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top98_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top102_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top103_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top104_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top105_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top113_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top115_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top116_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top117_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top118_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top127_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top128_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top131_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top134_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top135_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top136_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top137_sensor_);
      LOG_SENSOR("", "Panasonic Heatpump Sensor", this->top138_sensor_);
#endif
#ifdef USE_BINARY_SENSOR
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top0_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top2_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top3_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top13_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top26_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top60_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top61_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top68_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top69_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top99_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top100_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top108_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top109_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top110_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top119_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top120_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top121_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top122_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top123_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top124_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top129_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top132_binary_sensor_);
      LOG_BINARY_SENSOR("", "Panasonic Heatpump BinarySensor", this->top133_binary_sensor_);
#endif
#ifdef USE_TEXT_SENSOR
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top4_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top17_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top18_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top19_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top20_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top44_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top58_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top59_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top76_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top81_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top92_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top94_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top101_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top106_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top107_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top111_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top112_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top114_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top125_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top126_text_sensor_);
      LOG_TEXT_SENSOR("", "Panasonic Heatpump TextSensor", this->top130_text_sensor_);
#endif
#ifdef USE_NUMBER
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set5_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set6_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set7_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set8_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set11_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set15_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_1_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_2_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_3_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_4_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_5_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_6_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_7_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_8_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_9_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_10_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_11_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_12_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_13_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_14_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_15_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set16_16_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set18_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set19_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set20_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set21_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set22_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set23_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set27_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set29_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set36_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set37_number_);
      LOG_NUMBER("", "Panasonic Heatpump Number", this->set38_number_);
#endif
#ifdef USE_SELECT
      LOG_SELECT("", "Panasonic Heatpump Select", this->set3_select_);
      LOG_SELECT("", "Panasonic Heatpump Select", this->set4_select_);
      LOG_SELECT("", "Panasonic Heatpump Select", this->set9_select_);
      LOG_SELECT("", "Panasonic Heatpump Select", this->set17_select_);
      LOG_SELECT("", "Panasonic Heatpump Select", this->set26_select_);
      LOG_SELECT("", "Panasonic Heatpump Select", this->set35_select_);
#endif
#ifdef USE_SWITCH
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set1_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set2_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set10_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set12_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set13_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set14_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set24_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set25_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set28_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set30_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set31_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set32_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set33_switch_);
      LOG_SWITCH("", "Panasonic Heatpump Switch", this->set34_switch_);
#endif
    }

    void PanasonicHeatpumpComponent::loop()
    {
      uint8_t byte_hp;
      uint8_t byte_wm;

      while (this->uart_hp_->available())
      {
        this->uart_hp_->read_byte(&byte_hp);
        this->uart_wm_->write_byte(byte_hp);

        // Message shall start with 0x71, if not skip this byte
        if (!this->response_receiving_)
        {
          if (byte_hp != 0x71)
            continue;
          this->response_receiving_ = true;
        }
        // Add current byte to message buffer
        this->response_message_.push_back(byte_hp);

        // 2. bytes contains the payload size
        if (this->response_message_.size() == 2)
          this->response_payload_length_ = byte_hp;
        // Discard message if 3. and 4. byte are not as expected
        if (this->response_message_.size() == 3 && byte_hp != 0x01 ||
            this->response_message_.size() == 4 && byte_hp != 0x10)
        {
          ESP_LOGW(TAG, "Invalid response message: %d. byte is 0x%02X but expexted is 0x%02X",
            response_message_.size(), byte_hp, response_message_.size() == 3 ? "01" : "10");
          delay(10);
          this->response_message_.clear();
          this->response_receiving_ = false;
          continue;
        }

        // Decode message if message is complete
        if (this->response_message_.size() > 2 && this->response_message_.size() == this->response_payload_length_ + 3)
        {
          this->log_uart_hex("<<<", this->response_message_, ',');
          this->decode_response(this->response_message_);
          this->response_message_.clear();
          this->response_receiving_ = false;
        }
      }

      while (this->uart_wm_->available())
      {
        // stop forwording messages if no message is currently processing
        if (!this->forward_requests_ && !this->request_receiving_)
          continue;

        this->uart_wm_->read_byte(&byte_wm);
        this->uart_hp_->write_byte(byte_wm);

        // Message shall start with 0x71, if not skip this byte
        if (!this->request_receiving_)
        {
          if (byte_wm != 0x71)
            continue;
          this->request_receiving_ = true;
        }
        // Add current byte to message buffer
        this->request_message_.push_back(byte_wm);

        // 2. bytes contains the payload size
        if (this->request_message_.size() == 2)
          this->request_payload_length_ = byte_wm;
        // Discard message if 3. and 4. byte are not as expected
        if (this->request_message_.size() == 3 && byte_wm != 0x01 ||
            this->request_message_.size() == 4 && byte_wm != 0x10)
        {
          ESP_LOGW(TAG, "Invalid request message: %d. byte is 0x%02X but expexted is 0x%02X",
            request_message_.size(), byte_wm, request_message_.size() == 3 ? "01" : "10");
          delay(10);
          this->request_message_.clear();
          this->request_receiving_ = false;
          continue;
        }

        // Decode message if message is complete
        if (this->request_message_.size() > 2 && this->request_message_.size() == this->request_payload_length_ + 3)
        {
          this->log_uart_hex(">>>", this->request_message_, ',');
          this->request_message_.clear();
          this->request_receiving_ = false;
        }
      }
    }

    void PanasonicHeatpumpComponent::log_uart_hex(std::string prefix, std::vector<uint8_t> bytes, uint8_t separator)
    {
      if (this->log_uart_msg_ == false) return;

      std::string logStr;
      logStr = "[" + std::to_string(bytes.size()) + "]";
      ESP_LOGI(TAG, "%s %s", prefix.c_str(), logStr.c_str());
      delay(10);

      logStr = "";
      char buffer[5];
      for (size_t i = 0; i < bytes.size(); i++)
      {
        if (i > 0) logStr += separator;
        sprintf(buffer, "%02X", bytes[i]);
        logStr += buffer;
      }

      size_t chunkSize = 90;
      for (size_t i = 0; i < logStr.length(); i += chunkSize)
      {
        ESP_LOGI(TAG, "%s %s", prefix.c_str(), logStr.substr(i, chunkSize).c_str());
        delay(10);
      }
    }

    void PanasonicHeatpumpComponent::decode_response(std::vector<uint8_t> bytes)
    {
      // Read response message:
      // format:          0x71 [payload_length] 0x01 0x10 [[TOP0 - TOP114] ...] 0x00 [checksum]
      // payload_length:  payload_length + 3 = packet_length
      // checksum:        if (sum(all bytes) & 0xFF == 0) ==> valid packet

      if (bytes.size() != RESPONSE_MSG_SIZE)
      {
        ESP_LOGW(TAG, "Invalid response message length: recieved %d - expected %d", bytes.size(), RESPONSE_MSG_SIZE);
        delay(10);
        return;
      }

      uint8_t checksum = 0;
      for (int i = 0; i < bytes.size(); i++)
      {
        checksum += bytes[i];
      }
      // checksum = checksum & 0xFF;
      if (checksum != 0)
      {
        ESP_LOGW(TAG, "Invalid response message: checksum = 0x%02X, last_byte = 0x%02X", checksum, bytes[202]);
        delay(10);
        return;
      }

#ifdef USE_SENSOR
      if (this->top1_sensor_) this->top1_sensor_->publish_state(PanasonicDecode::getPumpFlow(bytes[169], bytes[170]));
      if (this->top5_sensor_) this->top5_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[143]) + PanasonicDecode::getFractional(bytes[118], 0));
      if (this->top6_sensor_) this->top6_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[144]) + PanasonicDecode::getFractional(bytes[118], 3));
      if (this->top7_sensor_) this->top7_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[153]));
      if (this->top8_sensor_) this->top8_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[166]));
      if (this->top9_sensor_) this->top9_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[42]));
      if (this->top10_sensor_) this->top10_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[141]));
      if (this->top11_sensor_) this->top11_sensor_->publish_state(PanasonicDecode::getWord(bytes[182], bytes[183]));
      if (this->top12_sensor_) this->top12_sensor_->publish_state(PanasonicDecode::getWord(bytes[179], bytes[180]));
      if (this->top14_sensor_) this->top14_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[142]));
      if (this->top15_sensor_) this->top15_sensor_->publish_state(PanasonicDecode::getPower(bytes[194]));
      if (this->top16_sensor_) this->top16_sensor_->publish_state(PanasonicDecode::getPower(bytes[193]));
      if (this->top21_sensor_) this->top21_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[158]));
      if (this->top22_sensor_) this->top22_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[99]));
      if (this->top23_sensor_) this->top23_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[84]));
      if (this->top24_sensor_) this->top24_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[94]));
      if (this->top25_sensor_) this->top25_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[44]));
      if (this->top27_sensor_) this->top27_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[38]));
      if (this->top28_sensor_) this->top28_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[39]));
      if (this->top29_sensor_) this->top29_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[75]));
      if (this->top30_sensor_) this->top30_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[76]));
      if (this->top31_sensor_) this->top31_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[78]));
      if (this->top32_sensor_) this->top32_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[77]));
      if (this->top33_sensor_) this->top33_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[156]));
      if (this->top34_sensor_) this->top34_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[40]));
      if (this->top35_sensor_) this->top35_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[41]));
      if (this->top36_sensor_) this->top36_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[145]));
      if (this->top37_sensor_) this->top37_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[146]));
      if (this->top38_sensor_) this->top38_sensor_->publish_state(PanasonicDecode::getPower(bytes[196]));
      if (this->top39_sensor_) this->top39_sensor_->publish_state(PanasonicDecode::getPower(bytes[195]));
      if (this->top40_sensor_) this->top40_sensor_->publish_state(PanasonicDecode::getPower(bytes[198]));
      if (this->top41_sensor_) this->top41_sensor_->publish_state(PanasonicDecode::getPower(bytes[197]));
      if (this->top42_sensor_) this->top42_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[147]));
      if (this->top43_sensor_) this->top43_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[148]));
      if (this->top45_sensor_) this->top45_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[43]));
      if (this->top46_sensor_) this->top46_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[149]));
      if (this->top47_sensor_) this->top47_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[150]));
      if (this->top48_sensor_) this->top48_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[151]));
      if (this->top49_sensor_) this->top49_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[154]));
      if (this->top50_sensor_) this->top50_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[155]));
      if (this->top51_sensor_) this->top51_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[157]));
      if (this->top52_sensor_) this->top52_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[159]));
      if (this->top53_sensor_) this->top53_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[160]));
      if (this->top54_sensor_) this->top54_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[161]));
      if (this->top55_sensor_) this->top55_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[162]));
      if (this->top56_sensor_) this->top56_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[139]));
      if (this->top57_sensor_) this->top57_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[140]));
      if (this->top62_sensor_) this->top62_sensor_->publish_state(PanasonicDecode::getIntMinus1Times10(bytes[173]));
      if (this->top63_sensor_) this->top63_sensor_->publish_state(PanasonicDecode::getIntMinus1Times10(bytes[174]));
      if (this->top64_sensor_) this->top64_sensor_->publish_state(PanasonicDecode::getIntMinus1Div5(bytes[163]));
      if (this->top65_sensor_) this->top65_sensor_->publish_state(PanasonicDecode::getIntMinus1Times50(bytes[171]));
      if (this->top66_sensor_) this->top66_sensor_->publish_state(PanasonicDecode::getIntMinus1Times50(bytes[164]));
      if (this->top67_sensor_) this->top67_sensor_->publish_state(PanasonicDecode::getIntMinus1Div5(bytes[165]));
      if (this->top70_sensor_) this->top70_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[100]));
      if (this->top71_sensor_) this->top71_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[101]));
      if (this->top72_sensor_) this->top72_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[86]));
      if (this->top73_sensor_) this->top73_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[87]));
      if (this->top74_sensor_) this->top74_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[89]));
      if (this->top75_sensor_) this->top75_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[88]));
      if (this->top77_sensor_) this->top77_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[83]));
      if (this->top78_sensor_) this->top78_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[85]));
      if (this->top79_sensor_) this->top79_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[95]));
      if (this->top80_sensor_) this->top80_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[96]));
      if (this->top82_sensor_) this->top82_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[79]));
      if (this->top83_sensor_) this->top83_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[80]));
      if (this->top84_sensor_) this->top84_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[82]));
      if (this->top85_sensor_) this->top85_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[81]));
      if (this->top86_sensor_) this->top86_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[90]));
      if (this->top87_sensor_) this->top87_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[91]));
      if (this->top88_sensor_) this->top88_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[93]));
      if (this->top89_sensor_) this->top89_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[92]));
      if (this->top90_sensor_) this->top90_sensor_->publish_state(PanasonicDecode::getWord(bytes[185], bytes[186]));
      if (this->top91_sensor_) this->top91_sensor_->publish_state(PanasonicDecode::getWord(bytes[188], bytes[189]));
      if (this->top93_sensor_) this->top93_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[172]));
      if (this->top95_sensor_) this->top95_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[45]));
      if (this->top96_sensor_) this->top96_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[104]));
      if (this->top97_sensor_) this->top97_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[105]));
      if (this->top98_sensor_) this->top98_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[106]));
      if (this->top102_sensor_) this->top102_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[61]));
      if (this->top103_sensor_) this->top103_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[62]));
      if (this->top104_sensor_) this->top104_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[63]));
      if (this->top105_sensor_) this->top105_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[64]));
      if (this->top113_sensor_) this->top113_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[59]));
      if (this->top115_sensor_) this->top115_sensor_->publish_state(PanasonicDecode::getIntMinus1Div50(bytes[125]));
      if (this->top116_sensor_) this->top116_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[126]));
      if (this->top117_sensor_) this->top117_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[127]));
      if (this->top118_sensor_) this->top118_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[128]));
      if (this->top127_sensor_) this->top127_sensor_->publish_state(PanasonicDecode::getValvePID(bytes[177]));
      if (this->top128_sensor_) this->top128_sensor_->publish_state(PanasonicDecode::getValvePID(bytes[178]));
      if (this->top131_sensor_) this->top131_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[65]));
      if (this->top134_sensor_) this->top134_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[66]));
      if (this->top135_sensor_) this->top135_sensor_->publish_state(PanasonicDecode::getIntMinus128(bytes[68]));
      if (this->top136_sensor_) this->top136_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[67]));
      if (this->top137_sensor_) this->top137_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[69]));
      if (this->top138_sensor_) this->top138_sensor_->publish_state(PanasonicDecode::getIntMinus1(bytes[70]));
#endif
#ifdef USE_BINARY_SENSOR
      if (this->top0_binary_sensor_) this->top0_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[4])));
      if (this->top2_binary_sensor_) this->top2_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[4])));
      if (this->top3_binary_sensor_) this->top3_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[7])));
      if (this->top13_binary_sensor_) this->top13_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[5])));
      if (this->top26_binary_sensor_) this->top26_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[111])));
      if (this->top60_binary_sensor_) this->top60_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[112])));
      if (this->top61_binary_sensor_) this->top61_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[112])));
      if (this->top68_binary_sensor_) this->top68_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[5])));
      if (this->top69_binary_sensor_) this->top69_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[117])));
      if (this->top99_binary_sensor_) this->top99_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[24])));
      if (this->top100_binary_sensor_) this->top100_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[24])));
      if (this->top108_binary_sensor_) this->top108_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit3and4(bytes[20])));
      if (this->top109_binary_sensor_) this->top109_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[20])));
      if (this->top110_binary_sensor_) this->top110_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[20])));
      if (this->top119_binary_sensor_) this->top119_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[23])));
      if (this->top120_binary_sensor_) this->top120_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[23])));
      if (this->top121_binary_sensor_) this->top121_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit3and4(bytes[23])));
      if (this->top122_binary_sensor_) this->top122_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[23])));
      if (this->top123_binary_sensor_) this->top123_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[116])));
      if (this->top124_binary_sensor_) this->top124_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit3and4(bytes[116])));
      if (this->top129_binary_sensor_) this->top129_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[26])));
      if (this->top132_binary_sensor_) this->top132_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit3and4(bytes[26])));
      if (this->top133_binary_sensor_) this->top133_binary_sensor_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[26])));
#endif
#ifdef USE_TEXT_SENSOR
      if (this->top4_text_sensor_) this->top4_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::OpModeDesc, PanasonicDecode::getOpMode(bytes[6])));
      if (this->top17_text_sensor_) this->top17_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Powerfulmode, PanasonicDecode::getRight3bits(bytes[7])));
      if (this->top18_text_sensor_) this->top18_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Quietmode, PanasonicDecode::getBit3and4and5(bytes[7])));
      if (this->top19_text_sensor_) this->top19_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::HolidayState, PanasonicDecode::getBit3and4(bytes[5])));
      if (this->top20_text_sensor_) this->top20_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Valve, PanasonicDecode::getBit7and8(bytes[111])));
      if (this->top44_text_sensor_) this->top44_text_sensor_->publish_state(PanasonicDecode::getErrorInfo(bytes[113], bytes[114]));
      if (this->top58_text_sensor_) this->top58_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::BlockedFree, PanasonicDecode::getBit5and6(bytes[9])));
      if (this->top59_text_sensor_) this->top59_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::BlockedFree, PanasonicDecode::getBit7and8(bytes[9])));
      if (this->top76_text_sensor_) this->top76_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::HeatCoolModeDesc, PanasonicDecode::getBit7and8(bytes[28])));
      if (this->top81_text_sensor_) this->top81_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::HeatCoolModeDesc, PanasonicDecode::getBit5and6(bytes[28])));
      if (this->top92_text_sensor_) this->top92_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ModelNames, PanasonicDecode::getModel(bytes, 129)));
      if (this->top94_text_sensor_) this->top94_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ZonesState, PanasonicDecode::getBit1and2(bytes[6])));
      if (this->top101_text_sensor_) this->top101_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::SolarModeDesc, PanasonicDecode::getBit3and4(bytes[24])));
      if (this->top106_text_sensor_) this->top106_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::PumpFlowRateMode, PanasonicDecode::getBit3and4(bytes[29])));
      if (this->top107_text_sensor_) this->top107_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::LiquidType, PanasonicDecode::getBit1(bytes[20])));
      if (this->top111_text_sensor_) this->top111_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ZonesSensorType, PanasonicDecode::getSecondByte(bytes[22])));
      if (this->top112_text_sensor_) this->top112_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ZonesSensorType, PanasonicDecode::getFirstByte(bytes[22])));
      if (this->top114_text_sensor_) this->top114_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ExtPadHeaterType, PanasonicDecode::getBit3and4(bytes[25])));
      if (this->top125_text_sensor_) this->top125_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Valve2, PanasonicDecode::getBit5and6(bytes[116])));
      if (this->top126_text_sensor_) this->top126_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Valve, PanasonicDecode::getBit7and8(bytes[116])));
      if (this->top130_text_sensor_) this->top130_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Bivalent, PanasonicDecode::getBit5and6(bytes[26])));
#endif
    }

    void PanasonicHeatpumpComponent::send_initial_message()
    {
      // send command
      this->uart_hp_->write_array(PanasonicCommand::InitialMessage, REQUEST_INIT_MSG_SIZE);
      this->log_uart_hex(">>>", this->command_message_, ',');
      delay(100);  // NOLINT
    }

    void PanasonicHeatpumpComponent::send_periodical_message()
    {
      // send command
      this->uart_hp_->write_array(PanasonicCommand::PeriodicalMessage, REQUEST_DATA_MSG_SIZE);
      this->log_uart_hex(">>>", this->command_message_, ',');
      delay(100);  // NOLINT
    }

    void PanasonicHeatpumpComponent::send_command_message(uint8_t value, uint8_t index)
    {
      // initialize the command
      command_message_.clear();
      command_message_.insert(this->command_message_.end(), PanasonicCommand::CommandMessage, 
        PanasonicCommand::CommandMessage + REQUEST_DATA_MSG_SIZE);
      // set command byte
      command_message_[index] = value;
      // calculate and set set checksum (last element)
      command_message_.back() = PanasonicCommand::calcChecksum(command_message_, command_message_.size() - 1);

      // ToDo: Wait until no request is send or stop periodic message.
      // while (request_receiving_ == 1) { delay(1); }

      // send command
      // this->uart_hp_->write_array(this->command_message_);
      this->log_uart_hex(">>>", this->command_message_, ',');
      delay(100);  // NOLINT
    }

#ifdef USE_NUMBER
    void PanasonicHeatpumpComponent::number_control(number::Number* object, float value)
    {
      if (object == this->set5_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 38);
      else if (object == this->set6_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 39);
      else if (object == this->set7_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 40);
      else if (object == this->set8_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 41);
      else if (object == this->set11_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 42);
      else if (object == this->set15_number_) this->send_command_message(PanasonicCommand::setPlus1(value), 45);
      else if (object == this->set16_1_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 75);
      else if (object == this->set16_2_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 76);
      else if (object == this->set16_3_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 77);
      else if (object == this->set16_4_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 78);
      else if (object == this->set16_5_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 79);
      else if (object == this->set16_6_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 80);
      else if (object == this->set16_7_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 81);
      else if (object == this->set16_8_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 82);
      else if (object == this->set16_9_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 86);
      else if (object == this->set16_10_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 87);
      else if (object == this->set16_11_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 88);
      else if (object == this->set16_12_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 89);
      else if (object == this->set16_13_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 90);
      else if (object == this->set16_14_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 91);
      else if (object == this->set16_15_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 92);
      else if (object == this->set16_16_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 93);
      else if (object == this->set18_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 84);
      else if (object == this->set19_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 94);
      else if (object == this->set20_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 99);
      else if (object == this->set21_number_) this->send_command_message(PanasonicCommand::setPlus1(value), 104);
      else if (object == this->set22_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 105);
      else if (object == this->set23_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 106);
      else if (object == this->set27_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 59);
      else if (object == this->set29_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 83);
      else if (object == this->set36_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 65);
      else if (object == this->set37_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 66);
      else if (object == this->set38_number_) this->send_command_message(PanasonicCommand::setPlus128(value), 68);
    }
#endif
#ifdef USE_SELECT
    void PanasonicHeatpumpComponent::select_control(select::Select* object, size_t value)
    {
      if (object == this->set3_select_) this->send_command_message(PanasonicCommand::setPlus1Multiply8(value), 7);
      else if (object == this->set4_select_) this->send_command_message(PanasonicCommand::setPlus73(value), 7);
      else if (object == this->set9_select_) this->send_command_message(PanasonicCommand::setOperationMode(value), 6);
      else if (object == this->set17_select_) this->send_command_message(PanasonicCommand::setPlus1Multiply64(value), 6);
      else if (object == this->set26_select_) this->send_command_message(PanasonicCommand::setPlus1Multiply16(value), 25);
      else if (object == this->set35_select_) this->send_command_message(PanasonicCommand::setPlus1Multiply4(value), 26);
    }
#endif
#ifdef USE_SWITCH
    void PanasonicHeatpumpComponent::switch_control(switch_::Switch* object, size_t value)
    {
      if (object == this->set1_switch_) this->send_command_message(PanasonicCommand::setPlus1(value), 4);
      else if (object == this->set2_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply16(value), 5);
      else if (object == this->set10_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply64(value), 4);
      else if (object == this->set12_switch_) this->send_command_message(PanasonicCommand::setMultiply2(value), 8);
      else if (object == this->set13_switch_) this->send_command_message(PanasonicCommand::setMultiply4(value), 8);
      else if (object == this->set14_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply16(value), 4);
      else if (object == this->set24_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply64(value), 5);
      else if (object == this->set25_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply16(value), 20);
      else if (object == this->set28_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply4(value), 24);
      else if (object == this->set30_switch_) this->send_command_message(PanasonicCommand::setPlus1(value), 23);
      else if (object == this->set31_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply16(value), 23);
      else if (object == this->set32_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply64(value), 23);
      else if (object == this->set33_switch_) this->send_command_message(PanasonicCommand::setPlus1Multiply4(value), 23);
      else if (object == this->set34_switch_) this->send_command_message(PanasonicCommand::setPlus1(value), 26);
    }
#endif
  }  // namespace panasonic_heatpump
}  // namespace esphome
