#include "panasonic_heatpump.h"


namespace esphome
{
  namespace panasonic_heatpump
  {
    static const char *const TAG = "panasonic_heatpump";

    void PanasonicHeatpumpComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "Panasonic Heatpump");
      delay(10);
    }

    void PanasonicHeatpumpComponent::setup()
    {
      ESP_LOGCONFIG(TAG, "Setting up Panasonic Heatpump ...");
      delay(10);
      this->check_uart_settings(9600, 1, uart::UART_CONFIG_PARITY_EVEN, 8);
      // Trigger initial request
      this->next_request_ = 0;
      this->trigger_request_ = true;
    }

    void PanasonicHeatpumpComponent::update()
    {
      if (this->uart_client_ == nullptr)
        this->trigger_request_ = true;
    }

    void PanasonicHeatpumpComponent::loop()
    {
      this->read_response();
      this->send_request();
      this->read_request();

      // Next request will be polling
      this->next_request_ = 1;
      this->trigger_request_ = false;
    }

    void PanasonicHeatpumpComponent::read_response()
    {
      uint8_t byte;
      while (this->available())
      {
        // Read byte from heatpump and forward it directly to the client (CZ-TAW1)
        this->read_byte(&byte);
        if (this->uart_client_ != nullptr)
          this->uart_client_->write_byte(byte);

        // Message shall start with 0x31, 0x71 or 0xF1, if not skip this byte
        if (!this->response_receiving_)
        {
          if (byte != 0x31 && byte != 0x71 && byte != 0xF1)
            continue;
          this->response_receiving_ = true;
        }
        // Add current byte to message buffer
        this->response_message_.push_back(byte);

        // 2. bytes contains the payload size
        if (this->response_message_.size() == 2)
          this->response_payload_length_ = byte;
        // Discard message if format is wrong
        if ((this->response_message_.size() == 3 || this->response_message_.size() == 4)
            && byte != 0x01 && byte != 0x10)
        {
          ESP_LOGW(TAG, "Invalid response message: %d. byte is 0x%02X but expexted is 0x01 or 0x10",
            response_message_.size(), byte);
          delay(10);
          this->response_message_.clear();
          this->response_receiving_ = false;
          continue;
        }

        // Check if message is complete
        if (this->response_message_.size() > 2 && this->response_message_.size() == this->response_payload_length_ + 3)
        {
          this->log_uart_hex(UART_LOG_RX, this->response_message_, ',');
          this->decode_response(this->response_message_);
          this->response_message_.clear();
          this->response_receiving_ = false;
        }
      }
    }

    void PanasonicHeatpumpComponent::send_request()
    {
      if (this->trigger_request_ == false) return;

      if (this->next_request_ == 2) // command
      {
        this->log_uart_hex(UART_LOG_TX, this->command_message_, ',');
        this->write_array(this->command_message_);
        this->flush();
        return;
      }

      if (this->uart_client_ != nullptr) return;

      if (this->next_request_ == 0) // initial
      {
        // Probably not necessary but CZ-TAW1 sends this query on boot
        this->log_uart_hex(UART_LOG_TX, PanasonicCommand::InitialMessage, REQUEST_INIT_MSG_SIZE, ',');
        this->write_array(PanasonicCommand::InitialMessage, REQUEST_INIT_MSG_SIZE);
        this->flush();
      }
      else if (this->next_request_ == 1) // polling
      {
        this->log_uart_hex(UART_LOG_TX, PanasonicCommand::PollingMessage, REQUEST_DATA_MSG_SIZE, ',');
        this->write_array(PanasonicCommand::PollingMessage, REQUEST_DATA_MSG_SIZE);
        this->flush();
      }
    }

    void PanasonicHeatpumpComponent::read_request()
    {
      if (this->uart_client_ == nullptr) return;

      uint8_t byte;
      while (this->uart_client_->available())
      {
        // Read byte from client and forward it directly to the heatpump
        this->uart_client_->read_byte(&byte);
        this->write_byte(byte);

        // Message shall start with 0x31, 0x71 or 0xF1, if not skip this byte
        if (!this->request_receiving_)
        {
          if (byte != 0x31 && byte != 0x71 && byte != 0xF1)
            continue;
          this->request_receiving_ = true;
        }
        // Add current byte to message buffer
        this->request_message_.push_back(byte);

        // 2. bytes contains the payload size
        if (this->request_message_.size() == 2)
          this->request_payload_length_ = byte;

        // Discard message if format is wrong
        if ((this->request_message_.size() == 3 || this->request_message_.size() == 4)
            && byte != 0x01 && byte != 0x10)
        {
          ESP_LOGW(TAG, "Invalid request message: %d. byte is 0x%02X but expexted is 0x01 or 0x10",
            request_message_.size(), byte);
          delay(10);
          this->request_message_.clear();
          this->request_receiving_ = false;
          continue;
        }

        // Check if message is complete
        if (this->request_message_.size() > 2 && this->request_message_.size() == this->request_payload_length_ + 3)
        {
          this->log_uart_hex(UART_LOG_TX, this->request_message_, ',');
          this->request_message_.clear();
          this->request_receiving_ = false;
        }
      }
    }

    void PanasonicHeatpumpComponent::log_uart_hex(UartLogDirection direction, const uint8_t *data, size_t length, uint8_t separator)
    {
      if (this->log_uart_msg_ == false) return;

      std::string logStr;
      std::string msgDir = direction == UART_LOG_TX ? ">>>" : "<<<";
      std::string msgType = "response";
      if (direction == UART_LOG_TX)
      {
        switch(data[0])
        {
          case 0x31:
            msgType = "initial_request";
            break;
          case 0x71:
            msgType = "polling_request";
            break;
          case 0xF1:
            msgType = "command_request";
            break;
          default:
            msgType = "request";
        };
      }

      logStr = "[" + std::to_string(length) + "]";
      ESP_LOGI(TAG, "%s %s%s", msgDir.c_str(), msgType.c_str(), logStr.c_str());
      delay(10);

      logStr = "";
      char buffer[5];
      for (size_t i = 0; i < length; i++)
      {
        if (i > 0) logStr += separator;
        sprintf(buffer, "%02X", data[i]);
        logStr += buffer;
      }

      size_t chunkSize = 90;
      for (size_t i = 0; i < logStr.length(); i += chunkSize)
      {
        ESP_LOGD(TAG, "%s %s", msgDir.c_str(), logStr.substr(i, chunkSize).c_str());
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

      this->publish_sensor(bytes);
      this->publish_binary_sensor(bytes);
      this->publish_text_sensor(bytes);
      this->publish_number(bytes);
      this->publish_select(bytes);
      this->publish_switch(bytes);
    }
    
    void PanasonicHeatpumpComponent::set_command_byte(uint8_t value, uint8_t index)
    {
      if (this->next_request_ == 1)
      {
        // initialize the command
        command_message_.clear();
        command_message_.insert(this->command_message_.end(), PanasonicCommand::CommandMessage, 
        PanasonicCommand::CommandMessage + REQUEST_DATA_MSG_SIZE);
      }
      // set command byte
      command_message_[index] = value;
      // calculate and set set checksum (last element)
      command_message_.back() = PanasonicCommand::calcChecksum(command_message_, command_message_.size() - 1);

      // command will be send on next loop
      this->next_request_ = 2;
      this->trigger_request_ = true;
    }

    void PanasonicHeatpumpComponent::publish_sensor(std::vector<uint8_t> bytes)
    {
#ifdef USE_SENSOR
      if (this->top1_sensor_) this->top1_sensor_->publish_state(PanasonicDecode::getPumpFlow(bytes[169], bytes[170]));
      if (this->top5_sensor_) this->top5_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[143]) + PanasonicDecode::getFractional(bytes[118], 0));
      if (this->top6_sensor_) this->top6_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[144]) + PanasonicDecode::getFractional(bytes[118], 3));
      if (this->top7_sensor_) this->top7_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[153]));
      if (this->top8_sensor_) this->top8_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[166]));
      if (this->top9_sensor_) this->top9_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[42]));
      if (this->top10_sensor_) this->top10_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[141]));
      if (this->top11_sensor_) this->top11_sensor_->publish_state(PanasonicDecode::getWordMinus1(bytes[182], bytes[183]));
      if (this->top12_sensor_) this->top12_sensor_->publish_state(PanasonicDecode::getWordMinus1(bytes[179], bytes[180]));
      if (this->top14_sensor_) this->top14_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[142]));
      if (this->top15_sensor_) this->top15_sensor_->publish_state(PanasonicDecode::getByteMinus1Times200(bytes[194]));
      if (this->top16_sensor_) this->top16_sensor_->publish_state(PanasonicDecode::getByteMinus1Times200(bytes[193]));
      if (this->top21_sensor_) this->top21_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[158]));
      if (this->top22_sensor_) this->top22_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[99]));
      if (this->top23_sensor_) this->top23_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[84]));
      if (this->top24_sensor_) this->top24_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[94]));
      if (this->top25_sensor_) this->top25_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[44]));
      if (this->top27_sensor_) this->top27_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[38]));
      if (this->top28_sensor_) this->top28_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[39]));
      if (this->top29_sensor_) this->top29_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[75]));
      if (this->top30_sensor_) this->top30_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[76]));
      if (this->top31_sensor_) this->top31_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[78]));
      if (this->top32_sensor_) this->top32_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[77]));
      if (this->top33_sensor_) this->top33_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[156]));
      if (this->top34_sensor_) this->top34_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[40]));
      if (this->top35_sensor_) this->top35_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[41]));
      if (this->top36_sensor_) this->top36_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[145]));
      if (this->top37_sensor_) this->top37_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[146]));
      if (this->top38_sensor_) this->top38_sensor_->publish_state(PanasonicDecode::getByteMinus1Times200(bytes[196]));
      if (this->top39_sensor_) this->top39_sensor_->publish_state(PanasonicDecode::getByteMinus1Times200(bytes[195]));
      if (this->top40_sensor_) this->top40_sensor_->publish_state(PanasonicDecode::getByteMinus1Times200(bytes[198]));
      if (this->top41_sensor_) this->top41_sensor_->publish_state(PanasonicDecode::getByteMinus1Times200(bytes[197]));
      if (this->top42_sensor_) this->top42_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[147]));
      if (this->top43_sensor_) this->top43_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[148]));
      if (this->top45_sensor_) this->top45_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[43]));
      if (this->top46_sensor_) this->top46_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[149]));
      if (this->top47_sensor_) this->top47_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[150]));
      if (this->top48_sensor_) this->top48_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[151]));
      if (this->top49_sensor_) this->top49_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[154]));
      if (this->top50_sensor_) this->top50_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[155]));
      if (this->top51_sensor_) this->top51_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[157]));
      if (this->top52_sensor_) this->top52_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[159]));
      if (this->top53_sensor_) this->top53_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[160]));
      if (this->top54_sensor_) this->top54_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[161]));
      if (this->top55_sensor_) this->top55_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[162]));
      if (this->top56_sensor_) this->top56_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[139]));
      if (this->top57_sensor_) this->top57_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[140]));
      if (this->top62_sensor_) this->top62_sensor_->publish_state(PanasonicDecode::getByteMinus1Times10(bytes[173]));
      if (this->top63_sensor_) this->top63_sensor_->publish_state(PanasonicDecode::getByteMinus1Times10(bytes[174]));
      if (this->top64_sensor_) this->top64_sensor_->publish_state(PanasonicDecode::getByteMinus1Div5(bytes[163]));
      if (this->top65_sensor_) this->top65_sensor_->publish_state(PanasonicDecode::getByteMinus1Times50(bytes[171]));
      if (this->top66_sensor_) this->top66_sensor_->publish_state(PanasonicDecode::getByteMinus1Times50(bytes[164]));
      if (this->top67_sensor_) this->top67_sensor_->publish_state(PanasonicDecode::getByteMinus1Div5(bytes[165]));
      if (this->top70_sensor_) this->top70_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[100]));
      if (this->top71_sensor_) this->top71_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[101]));
      if (this->top72_sensor_) this->top72_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[86]));
      if (this->top73_sensor_) this->top73_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[87]));
      if (this->top74_sensor_) this->top74_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[89]));
      if (this->top75_sensor_) this->top75_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[88]));
      if (this->top77_sensor_) this->top77_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[83]));
      if (this->top78_sensor_) this->top78_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[85]));
      if (this->top79_sensor_) this->top79_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[95]));
      if (this->top80_sensor_) this->top80_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[96]));
      if (this->top82_sensor_) this->top82_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[79]));
      if (this->top83_sensor_) this->top83_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[80]));
      if (this->top84_sensor_) this->top84_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[82]));
      if (this->top85_sensor_) this->top85_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[81]));
      if (this->top86_sensor_) this->top86_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[90]));
      if (this->top87_sensor_) this->top87_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[91]));
      if (this->top88_sensor_) this->top88_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[93]));
      if (this->top89_sensor_) this->top89_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[92]));
      if (this->top90_sensor_) this->top90_sensor_->publish_state(PanasonicDecode::getWordMinus1(bytes[185], bytes[186]));
      if (this->top91_sensor_) this->top91_sensor_->publish_state(PanasonicDecode::getWordMinus1(bytes[188], bytes[189]));
      if (this->top93_sensor_) this->top93_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[172]));
      if (this->top95_sensor_) this->top95_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[45]));
      if (this->top96_sensor_) this->top96_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[104]));
      if (this->top97_sensor_) this->top97_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[105]));
      if (this->top98_sensor_) this->top98_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[106]));
      if (this->top102_sensor_) this->top102_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[61]));
      if (this->top103_sensor_) this->top103_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[62]));
      if (this->top104_sensor_) this->top104_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[63]));
      if (this->top105_sensor_) this->top105_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[64]));
      if (this->top113_sensor_) this->top113_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[59]));
      if (this->top115_sensor_) this->top115_sensor_->publish_state(PanasonicDecode::getByteMinus1Div50(bytes[125]));
      if (this->top116_sensor_) this->top116_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[126]));
      if (this->top117_sensor_) this->top117_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[127]));
      if (this->top118_sensor_) this->top118_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[128]));
      if (this->top127_sensor_) this->top127_sensor_->publish_state(PanasonicDecode::getByteMinus1Div2(bytes[177]));
      if (this->top128_sensor_) this->top128_sensor_->publish_state(PanasonicDecode::getByteMinus1Div2(bytes[178]));
      if (this->top131_sensor_) this->top131_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[65]));
      if (this->top134_sensor_) this->top134_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[66]));
      if (this->top135_sensor_) this->top135_sensor_->publish_state(PanasonicDecode::getByteMinus128(bytes[68]));
      if (this->top136_sensor_) this->top136_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[67]));
      if (this->top137_sensor_) this->top137_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[69]));
      if (this->top138_sensor_) this->top138_sensor_->publish_state(PanasonicDecode::getByteMinus1(bytes[70]));
#endif
    }

    void PanasonicHeatpumpComponent::publish_binary_sensor(std::vector<uint8_t> bytes)
    {
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
    }

    void PanasonicHeatpumpComponent::publish_text_sensor(std::vector<uint8_t> bytes)
    {
#ifdef USE_TEXT_SENSOR
      if (this->top4_text_sensor_) this->top4_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::OpModeDesc, PanasonicDecode::getOpMode(bytes[6])));
      if (this->top17_text_sensor_) this->top17_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Powerfulmode, PanasonicDecode::getBit6and7and8(bytes[7])));
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
      if (this->top111_text_sensor_) this->top111_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ZonesSensorType, PanasonicDecode::getLowNibbleMinus1(bytes[22])));
      if (this->top112_text_sensor_) this->top112_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ZonesSensorType, PanasonicDecode::getHighNibbleMinus1(bytes[22])));
      if (this->top114_text_sensor_) this->top114_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ExtPadHeaterType, PanasonicDecode::getBit3and4(bytes[25])));
      if (this->top125_text_sensor_) this->top125_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Valve2, PanasonicDecode::getBit5and6(bytes[116])));
      if (this->top126_text_sensor_) this->top126_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Valve, PanasonicDecode::getBit7and8(bytes[116])));
      if (this->top130_text_sensor_) this->top130_text_sensor_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Bivalent, PanasonicDecode::getBit5and6(bytes[26])));
#endif
    }

    void PanasonicHeatpumpComponent::publish_number(std::vector<uint8_t> bytes)
    {
#ifdef USE_NUMBER
      if (this->set11_number_) this->set11_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[42]));
      if (this->set20_number_) this->set20_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[99]));
      if (this->set18_number_) this->set18_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[84]));
      if (this->set19_number_) this->set19_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[94]));
      if (this->set5_number_) this->set5_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[38]));
      if (this->set6_number_) this->set6_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[39]));
      if (this->set16_1_number_) this->set16_1_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[75]));
      if (this->set16_2_number_) this->set16_2_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[76]));
      if (this->set16_4_number_) this->set16_4_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[78]));
      if (this->set16_3_number_) this->set16_3_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[77]));
      if (this->set7_number_) this->set7_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[40]));
      if (this->set8_number_) this->set8_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[41]));
      if (this->set16_9_number_) this->set16_9_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[86]));
      if (this->set16_10_number_) this->set16_10_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[87]));
      if (this->set16_12_number_) this->set16_12_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[89]));
      if (this->set16_11_number_) this->set16_11_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[88]));
      if (this->set29_number_) this->set29_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[83]));
      if (this->set16_5_number_) this->set16_5_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[79]));
      if (this->set16_6_number_) this->set16_6_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[80]));
      if (this->set16_8_number_) this->set16_8_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[82]));
      if (this->set16_7_number_) this->set16_7_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[81]));
      if (this->set16_13_number_) this->set16_13_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[90]));
      if (this->set16_14_number_) this->set16_14_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[91]));
      if (this->set16_16_number_) this->set16_16_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[93]));
      if (this->set16_15_number_) this->set16_15_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[92]));
      if (this->set15_number_) this->set15_number_->publish_state(PanasonicDecode::getByteMinus1(bytes[45]));
      if (this->set21_number_) this->set21_number_->publish_state(PanasonicDecode::getByteMinus1(bytes[104]));
      if (this->set22_number_) this->set22_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[105]));
      if (this->set23_number_) this->set23_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[106]));
      if (this->set27_number_) this->set27_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[59]));
      if (this->set36_number_) this->set36_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[65]));
      if (this->set37_number_) this->set37_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[66]));
      if (this->set38_number_) this->set38_number_->publish_state(PanasonicDecode::getByteMinus128(bytes[68]));
#endif
    }

    void PanasonicHeatpumpComponent::publish_select(std::vector<uint8_t> bytes)
    {
#ifdef USE_SELECT
      if (this->set9_select_) this->set9_select_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::OpModeDesc, PanasonicDecode::getOpMode(bytes[6])));
      if (this->set4_select_) this->set4_select_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Powerfulmode, PanasonicDecode::getBit6and7and8(bytes[7])));
      if (this->set3_select_) this->set3_select_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Quietmode, PanasonicDecode::getBit3and4and5(bytes[7])));
      if (this->set2_select_) this->set2_select_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::HolidayState, PanasonicDecode::getBit3and4(bytes[5])));
      if (this->set17_select_) this->set17_select_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ZonesState, PanasonicDecode::getBit1and2(bytes[6])));
      if (this->set26_select_) this->set26_select_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::ExtPadHeaterType, PanasonicDecode::getBit3and4(bytes[25])));
      if (this->set35_select_) this->set35_select_->publish_state(PanasonicDecode::getTextState(PanasonicDecode::Bivalent, PanasonicDecode::getBit5and6(bytes[26])));
#endif
    }

    void PanasonicHeatpumpComponent::publish_switch(std::vector<uint8_t> bytes)
    {
#ifdef USE_SWITCH
      if (this->set1_switch_) this->set1_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[4])));
      if (this->set10_switch_) this->set10_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[4])));
      if (this->set24_switch_) this->set24_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[5])));
      if (this->set12_switch_) this->set12_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[111])));
      if (this->set13_switch_) this->set13_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[117])));
      if (this->set28_switch_) this->set28_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[24])));
      if (this->set30_switch_) this->set30_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[23])));
      if (this->set33_switch_) this->set33_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit5and6(bytes[23])));
      if (this->set31_switch_) this->set31_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit3and4(bytes[23])));
      if (this->set32_switch_) this->set32_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit1and2(bytes[23])));
      if (this->set34_switch_) this->set34_switch_->publish_state(PanasonicDecode::getBinaryState(PanasonicDecode::getBit7and8(bytes[26])));
#endif
    }


#ifdef USE_NUMBER
    void PanasonicHeatpumpComponent::control_number(number::Number* object, float value)
    {
      if (object == this->set5_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 38);
      else if (object == this->set6_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 39);
      else if (object == this->set7_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 40);
      else if (object == this->set8_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 41);
      else if (object == this->set11_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 42);
      else if (object == this->set15_number_) this->set_command_byte(PanasonicCommand::setPlus1(value), 45);
      else if (object == this->set16_1_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 75);
      else if (object == this->set16_2_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 76);
      else if (object == this->set16_3_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 77);
      else if (object == this->set16_4_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 78);
      else if (object == this->set16_5_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 79);
      else if (object == this->set16_6_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 80);
      else if (object == this->set16_7_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 81);
      else if (object == this->set16_8_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 82);
      else if (object == this->set16_9_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 86);
      else if (object == this->set16_10_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 87);
      else if (object == this->set16_11_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 88);
      else if (object == this->set16_12_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 89);
      else if (object == this->set16_13_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 90);
      else if (object == this->set16_14_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 91);
      else if (object == this->set16_15_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 92);
      else if (object == this->set16_16_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 93);
      else if (object == this->set18_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 84);
      else if (object == this->set19_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 94);
      else if (object == this->set20_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 99);
      else if (object == this->set21_number_) this->set_command_byte(PanasonicCommand::setPlus1(value), 104);
      else if (object == this->set22_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 105);
      else if (object == this->set23_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 106);
      else if (object == this->set27_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 59);
      else if (object == this->set29_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 83);
      else if (object == this->set36_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 65);
      else if (object == this->set37_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 66);
      else if (object == this->set38_number_) this->set_command_byte(PanasonicCommand::setPlus128(value), 68);
    }
#endif

#ifdef USE_SELECT
    void PanasonicHeatpumpComponent::control_select(select::Select* object, size_t value)
    {
      if (object == this->set2_select_) this->set_command_byte(PanasonicCommand::setPlus1Multiply16(value), 5);
      else if (object == this->set3_select_) this->set_command_byte(PanasonicCommand::setPlus1Multiply8(value), 7);
      else if (object == this->set4_select_) this->set_command_byte(PanasonicCommand::setPlus73(value), 7);
      else if (object == this->set9_select_) this->set_command_byte(PanasonicCommand::setOperationMode(value), 6);
      else if (object == this->set17_select_) this->set_command_byte(PanasonicCommand::setPlus1Multiply64(value), 6);
      else if (object == this->set26_select_) this->set_command_byte(PanasonicCommand::setPlus1Multiply16(value), 25);
      else if (object == this->set35_select_) this->set_command_byte(PanasonicCommand::setPlus1Multiply4(value), 26);
    }
#endif

#ifdef USE_SWITCH
    void PanasonicHeatpumpComponent::control_switch(switch_::Switch* object, size_t value)
    {
      if (object == this->set1_switch_) this->set_command_byte(PanasonicCommand::setPlus1(value), 4);
      else if (object == this->set10_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply64(value), 4);
      else if (object == this->set12_switch_) this->set_command_byte(PanasonicCommand::setMultiply2(value), 8);
      else if (object == this->set13_switch_) this->set_command_byte(PanasonicCommand::setMultiply4(value), 8);
      else if (object == this->set14_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply16(value), 4);
      else if (object == this->set24_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply64(value), 5);
      else if (object == this->set25_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply16(value), 20);
      else if (object == this->set28_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply4(value), 24);
      else if (object == this->set30_switch_) this->set_command_byte(PanasonicCommand::setPlus1(value), 23);
      else if (object == this->set31_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply16(value), 23);
      else if (object == this->set32_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply64(value), 23);
      else if (object == this->set33_switch_) this->set_command_byte(PanasonicCommand::setPlus1Multiply4(value), 23);
      else if (object == this->set34_switch_) this->set_command_byte(PanasonicCommand::setPlus1(value), 26);
    }
#endif
  }  // namespace panasonic_heatpump
}  // namespace esphome
