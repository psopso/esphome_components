#include "maidsite_desk.h"

#define BUTTON_UNIT       "unit"
#define BUTTON_STEP_UP    "step_up"
#define BUTTON_STEP_DOWN  "step_down"
#define BUTTON_STOP       "stop"
#define BUTTON_GOTO_MAX   "goto_max"
#define BUTTON_GOTO_MIN   "goto_min"
#define BUTTON_GOTO_M1    "goto_m1"
#define BUTTON_GOTO_M2    "goto_m2"
#define BUTTON_GOTO_M3    "goto_m3"
#define BUTTON_GOTO_M4    "goto_m4"
#define BUTTON_SAVE_M1    "save_m1"
#define BUTTON_SAVE_M2    "save_m2"
#define BUTTON_SAVE_M3    "save_m3"
#define BUTTON_SAVE_M4    "save_m4"

#define NUMBER_HEIGHT_ABS "height_abs"
#define NUMBER_HEIGHT_PCT "height_pct"


namespace esphome
{
  namespace maidsite_desk
  {
    static const char *const TAG = "maidsite_desk";

    void MaidsiteDeskComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "Maidsite Desk");

#ifdef USE_SENSOR
      LOG_SENSOR("", "Maidsite Desk Sensor", this->unit_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->height_abs_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->height_pct_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->height_min_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->height_max_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->position_m1_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->position_m2_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->position_m3_sensor_);
      LOG_SENSOR("", "Maidsite Desk Sensor", this->position_m4_sensor_);
#endif
#ifdef USE_BUTTON
      LOG_BUTTON("", "Maidsite Desk Button", this->unit_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->step_up_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->step_down_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->stop_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->goto_max_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->goto_min_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->goto_m1_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->goto_m2_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->goto_m3_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->goto_m4_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->save_m1_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->save_m2_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->save_m3_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->save_m4_button_);
      LOG_BUTTON("", "Maidsite Desk Button", this->save_m4_button_);
#endif
#ifdef USE_NUMBER
      LOG_NUMBER("", "Maidsite Desk Number", this->height_abs_number_);
      LOG_NUMBER("", "Maidsite Desk Number", this->height_pct_number_);
#endif
    }

    void MaidsiteDeskComponent::setup()
    {
      ESP_LOGCONFIG(TAG, "Setting up maidsite Desk ...");
      delay(10);

      height_abs_number_->traits.set_min_value(0);
      height_abs_number_->traits.set_max_value(120);
      height_abs_number_->traits.set_step(.2);
      height_pct_number_->traits.set_min_value(0);
      height_pct_number_->traits.set_max_value(120);
      height_pct_number_->traits.set_step(.1);

      request_physical_limits();
      request_limits();
      request_settings();
    }

    void MaidsiteDeskComponent::loop()
    {
      // This is a very simple method of receiving messages from the desk.
      // It will fail on messages that contain the value 0x7E in their payload.
      // But it is super simple and works for the messages we care about.
      // Read message:
      // format: 0xF2 0xF2 [command] [param_count] [[param] ...] [checksum] 0x7E
      // checksum: sum of [command], [param_count] and all [param]s

      uint8_t oneByte;
      while (this->available())
      {
        this->read_byte(&oneByte);

        // Message shall start with 0xF2, if not skip this byte
        if (!this->response_receiving_)
        {
          if (oneByte != 0xF2)
            continue;
          this->response_receiving_ = true;
        }
        // Add current byte to message buffer
        this->response_message_.push_back(oneByte);

        // Discard message if 2. byte is not 0xF2
        if (this->response_message_.size() == 2 && oneByte != 0xF2)
        {
          ESP_LOGW(TAG, "Invalid response message: 2. byte is 0x%02X but expexted is 0xF2", oneByte);
          delay(10);
          this->response_message_.clear();
          this->response_receiving_ = false;
          continue;
        }
        // Discard message if it is too long
        if (this->response_message_.size() > 10)
        {
          ESP_LOGW(TAG, "Response message too long: expected not more than 10 bytes");
          delay(10);
          this->response_message_.clear();
          this->response_receiving_ = false;
          continue;
        }

        // Decode message if message is complete (last byte shall be 0x7E)
        if (oneByte == 0x7E)
        {
          this->log_uart_hex("<<<", this->response_message_, ',');
          this->decode_response(this->response_message_);
          this->response_message_.clear();
          this->response_receiving_ = false;
        }
      }
    }

    void MaidsiteDeskComponent::log_uart_hex(std::string prefix, std::vector<uint8_t> bytes, uint8_t separator)
    {
      std::string logStr;
      logStr = "[" + std::to_string(bytes.size()) + "]";
      ESP_LOGD(TAG, "%s %s", prefix.c_str(), logStr.c_str());
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
        ESP_LOGD(TAG, "%s %s", prefix.c_str(), logStr.substr(i, chunkSize).c_str());
        delay(10);
      }
    }

    void MaidsiteDeskComponent::decode_response(std::vector<uint8_t> message)
    {
      // ToDo: Add checksum check

      switch (message[2])
      {
      case 0x01:
        ESP_LOGD(TAG, "set height 0x%0X%0X", message[4], message[5]);
        delay(10);

        float new_height;
        new_height = byte2float(message[4], message[5]);
        if (new_height == this->current_height_)
          return;
        this->current_height_ = new_height;
        if (this->height_abs_sensor_ != nullptr)
          this->height_abs_sensor_->publish_state(this->current_height_);
        if (this->height_abs_number_ != nullptr)
          this->height_abs_number_->publish_state(this->current_height_);

        if (this->height_pct_sensor_ != nullptr && limit_max_ != 0)
          this->height_pct_sensor_->publish_state((this->current_height_ - this->limit_min_) / (this->limit_max_ - this->limit_min_) * 100);
        if (this->height_pct_number_ != nullptr && limit_max_ != 0)
          this->height_pct_number_->publish_state(roundf((this->current_height_ - this->limit_min_) / (this->limit_max_ - this->limit_min_) * 1000) / 10);
        break;

      case 0x20:
        ESP_LOGD(TAG, "set limits 0x%0X  max %i min %i", message[4], (message[5] & 1), (message[4] >> 4));
        delay(10);

        if ((message[4] & 1) == 0)
        { // low nibble 0 -> no max limit, use physical_max_
          this->limit_max_ = this->physical_max_;
          if (this->height_max_sensor_ != nullptr)
            this->height_max_sensor_->publish_state(this->limit_max_);
          if (height_abs_number_ != nullptr)
            this->height_abs_number_->traits.set_max_value(this->limit_max_);
        }
        if ((message[4] >> 4) == 0)
        { // high nibble 0 -> no min limit, use physical_min_
          this->limit_min_ = this->physical_min_;
          if (this->height_min_sensor_ != nullptr)
            this->height_min_sensor_->publish_state(limit_min_);
          if (height_abs_number_ != nullptr)
            this->height_abs_number_->traits.set_min_value(limit_min_);
        }
        break;

      case 0x07:
        ESP_LOGD(TAG, "set physical limits 0x%02X%02X 0x%02X%02X", message[4], message[5], message[6], message[7]);
        delay(10);

        this->physical_max_ = this->byte2float(message[4], message[5]);
        this->physical_min_ = this->byte2float(message[6], message[7]);
        break;

      case 0x21:
        ESP_LOGD(TAG, "set height max 0x%02X%02X", message[4], message[5]);
        delay(10);

        this->limit_max_ = this->byte2float(message[4], message[5]);
        if (this->height_max_sensor_ != nullptr)
          this->height_max_sensor_->publish_state(limit_max_);
        if (height_abs_number_ != nullptr)
          this->height_abs_number_->traits.set_max_value(limit_max_);
        break;

      case 0x22:
        ESP_LOGD(TAG, "set height min 0x%02X%02X", message[4], message[5]);
        delay(10);

        this->limit_min_ = this->byte2float(message[4], message[5]);
        if (this->height_min_sensor_ != nullptr)
          this->height_min_sensor_->publish_state(limit_min_);
        if (height_abs_number_ != nullptr)
          this->height_abs_number_->traits.set_min_value(limit_min_);
        break;

      case 0x25:
        ESP_LOGD(TAG, "set position m1 0x%02X%02X", message[4], message[5]);
        delay(10);

        if (this->position_m1_sensor_ != nullptr)
          this->position_m1_sensor_->publish_state(this->byte2float(message[4], message[5]));
        break;

      case 0x26:
        ESP_LOGD(TAG, "set position m2 0x%02X%02X", message[4], message[5]);
        delay(10);

        if (this->position_m2_sensor_ != nullptr)
          this->position_m2_sensor_->publish_state(this->byte2float(message[4], message[5]));
        break;

      case 0x27:
        ESP_LOGD(TAG, "set position m3 0x%02X%02X", message[4], message[5]);
        delay(10);

        if (this->position_m3_sensor_ != nullptr)
          this->position_m3_sensor_->publish_state(this->byte2float(message[4], message[5]));
        break;

      case 0x28:
        ESP_LOGD(TAG, "set position m4 0x%02X%02X", message[4], message[5]);
        delay(10);

        if (this->position_m4_sensor_ != nullptr)
          this->position_m4_sensor_->publish_state(this->byte2float(message[4], message[5]));
        break;

      // case 0x0E:
      //   ESP_LOGD(TAG, "units 0x%02X", message[4]);
      //   if (units != nullptr)
      //     units->publish_state(byte2float(message[4], message[5]));
      //   break;

      default:
        ESP_LOGD(TAG, "Received unknown message");
        delay(10);
      }
    }

    float MaidsiteDeskComponent::byte2float(int high, int low)
    {
      return static_cast<float>((high << 8) + low) / 10;
    }

    // Write message:
    // format: 0xF1 0xF1 [command] [param_count] [[param] ...] [checksum] 0x7E
    // checksum: sum of [command], [param_count] and all [param]s
    void MaidsiteDeskComponent::send_simple_command(unsigned char cmd)
    {
      this->request_message_.clear();
      this->request_message_.insert(this->request_message_.end(), { 0xF1, 0xF1, cmd, 0x00, cmd, 0x7E });
      this->write_array(this->request_message_);
      this->log_uart_hex(">>>", this->request_message_, ',');
      delay(100);  // NOLINT
    }

    void MaidsiteDeskComponent::send_2byte_command(unsigned char cmd, unsigned char high_byte, unsigned char low_byte)
    {
      unsigned char checksum = cmd + 2 + high_byte + low_byte;
      this->request_message_.clear();
      this->request_message_.insert(this->request_message_.end(), { 0xF1, 0xF1, cmd, 0x02, high_byte, low_byte, checksum, 0x7E });
      this->write_array(this->request_message_);
      this->log_uart_hex(">>>", this->request_message_, ',');
      delay(100);  // NOLINT
    }

    void MaidsiteDeskComponent::step_up()
    {
      this->send_simple_command(0x01);
    }

    void MaidsiteDeskComponent::step_down()
    {
      this->send_simple_command(0x02);
    }

    void MaidsiteDeskComponent::stop()
    {
      this->send_simple_command(0x2B);
    }

    void MaidsiteDeskComponent::goto_mem_position(int pos)
    {
      switch (pos)
      {
      case 1:
        this->send_simple_command(0x05);
        break;
      case 2:
        this->send_simple_command(0x06);
        break;
      case 3:
        this->send_simple_command(0x27);
        break;
      case 4:
        this->send_simple_command(0x28);
        break;
      }
    }

    void MaidsiteDeskComponent::save_mem_position(int pos)
    {
      switch (pos)
      {
      case 1:
        this->send_simple_command(0x03);
        break;
      case 2:
        this->send_simple_command(0x04);
        break;
      case 3:
        this->send_simple_command(0x25);
        break;
      case 4:
        this->send_simple_command(0x26);
        break;
      }
    }

    void MaidsiteDeskComponent::request_physical_limits()
    {
      this->send_simple_command(0x0C);
    }

    void MaidsiteDeskComponent::request_limits()
    {
      this->send_simple_command(0x20);
    }

    void MaidsiteDeskComponent::request_settings()
    {
      this->send_simple_command(0x07);
    }

    void MaidsiteDeskComponent::request_move_to()
    {
      this->send_simple_command(0x1B);
    }

    void MaidsiteDeskComponent::goto_max_position()
    {
      this->goto_height(limit_max_);
    }

    void MaidsiteDeskComponent::goto_min_position()
    {
      this->goto_height(limit_min_);
    }

    void MaidsiteDeskComponent::goto_height(float height)
    {
      unsigned char high_byte = ((int)height * 10) >> 8;
      unsigned char low_byte = ((int)height * 10) & 0xFF;

      this->send_2byte_command(0x80, high_byte, low_byte);
      this->request_move_to();
    }

    void MaidsiteDeskComponent::button_press_action(button::Button* object)
    {
      ESP_LOGD(TAG, "button %s pressed", object->get_name());
      delay(10);

      if (object == step_up_button_)
        this->step_up();
      else if (object == step_down_button_)
        this->step_down();
      else if (object == stop_button_)
        this->stop();
      else if (object == goto_max_button_)
        this->goto_max_position();
      else if (object == goto_min_button_)
        this->goto_min_position();
      else if (object == goto_m1_button_)
        this->goto_mem_position(1);
      else if (object == goto_m2_button_)
        this->goto_mem_position(2);
      else if (object == goto_m3_button_)
        this->goto_mem_position(3);
      else if (object == goto_m4_button_)
        this->goto_mem_position(4);
      else if (object == save_m1_button_)
      {
        this->save_mem_position(1);
        this->request_settings();
      }
      else if (object == save_m2_button_)
      {
        this->save_mem_position(2);
        this->request_settings();
      }
      else if (object == save_m3_button_)
      {
        this->save_mem_position(3);
        this->request_settings();
      }
      else if (object == save_m4_button_)
      {
        this->save_mem_position(4);
        this->request_settings();
      }
    }

    void MaidsiteDeskComponent::number_control(number::Number* object, float value)
    {
      ESP_LOGD(TAG, "number %s controlled", object->get_name());
      delay(10);

      if (object == height_abs_number_)
        this->goto_height(value);
      else if (object == height_pct_number_)
        if (limit_max_ > 0 && limit_max_ > limit_min_)
          this->goto_height((limit_max_ - limit_min_) * value / 100 + limit_min_);
    }
  } // namespace maidsite_desk
} // namespace esphome
