#include "panasonic_heatpump.h"
#include "esphome/core/application.h"

namespace esphome
{
  namespace panasonic_heatpump {
    static const char* const TAG = "panasonic_heatpump";

    namespace header
    {
      bool is_valid(const std::vector<uint8_t> &frame)
      {
        return frame.size() >= SIZE                                     // is it a complete header?
        && (frame[2] == 0x01 || frame[2] == 0x10)                       // 3. byte shall be 0x01 or 0x10
        && (frame[3] == 0x01 || frame[3] == 0x10 || frame[3] == 0x21);  // 4. byte shall be 0x01, 0x10 or 0x21
      }

      uint8_t get_packet_size(const std::vector<uint8_t> &frame)
      {
        return frame[1] + 3; // three more than stated in the header
      }
    }

    void PanasonicHeatpumpComponent::dump_config() {
      ESP_LOGW(TAG, "*** Panasonic Heatpump Component v%s ***", PANASONIC_HEATPUMP_VERSION);
      //delay(10);  // NOLINT
    }

    void PanasonicHeatpumpComponent::setup() {
      ESP_LOGCONFIG(TAG, "Setting up Panasonic Heatpump ...");
      //delay(10);  // NOLINT
      this->check_uart_settings(9600, 1, uart::UART_CONFIG_PARITY_EVEN, 8);

      ESP_LOGI(TAG, "Setting up Panasonic Heatpump UART component...");
      this->response_queue_handle_ = xQueueCreate(8, sizeof(std::vector<uint8_t> *));
      if (this->response_queue_handle_ == nullptr) {
        ESP_LOGE(TAG, "Failed to create response queue!");
        this->mark_failed();
        return;
      }

      this->command_queue_handle_ = xQueueCreate(8, sizeof(std::vector<uint8_t> *));
      if (this->command_queue_handle_ == nullptr) {
        ESP_LOGE(TAG, "Failed to create command queue!");
        this->mark_failed();
        return;
      }

      // Start task
      xTaskCreatePinnedToCore(
          PanasonicHeatpumpComponent::uart_task_,
          "uart_handler",
          4096,
          this,
          tskIDLE_PRIORITY + 1, // Low priority, important for single-core C3
          &this->uart_task_handle_,
          tskNO_AFFINITY // important for single-core C3
      );

      if (this->uart_client_ != nullptr) {
        xTaskCreatePinnedToCore(
            PanasonicHeatpumpComponent::client_uart_task_,
            "client_uart_handler",
            4096,
            this,
            tskIDLE_PRIORITY + 1,
            &this->client_uart_task_handle_,
            tskNO_AFFINITY
        );
      }
      // Disable any self-initiated traffic if uart_client_timeout_ is used as "disable" criterion.
      if (this->uart_client_ != nullptr && this->uart_client_timeout_ < 100) {
        ESP_LOGI(TAG, "Self polling disabled (uart_client_timeout_ < 100ms). Not sending initial request.");
        return;
      }

      // ?? Initial request stopps response, if extra PCB ist installed.
      //this->queue_request_(message_build(PanasonicCommand::InitialRequest));
    }


    void PanasonicHeatpumpComponent::update() {
      // Hard disable: never poll if uart_client_timeout_ < 100ms and a client exists
      if (this->uart_client_ != nullptr && this->uart_client_timeout_ < 100) {
        return;
      }

      if (this->uart_client_ != nullptr && not this->uart_client_timeout_exceeded_)
      {
        if ( millis() - this->last_client_request_time_ > uart_client_timeout_)
          this->uart_client_timeout_exceeded_ = true;
        else
          return;
      }
      ESP_LOGI(TAG, "Timeout1: %s", this->uart_client_timeout_exceeded_ ? "true" : "false");
      //this->queue_request_({std::begin(PanasonicCommand::PollingMessage), std::end(PanasonicCommand::PollingMessage)});
      this->queue_request_(message_build(PanasonicCommand::PollingMessage));
    }


void PanasonicHeatpumpComponent::loop()
    {
      switch (this->loop_state_) {
      case LoopState::CHECK_RESPONSE:
        // check if it is a new response and dequeue it for loop processing
        {
          std::vector<uint8_t> *response_ptr{nullptr};
          if (xQueueReceive(this->response_queue_handle_, &response_ptr, 0) == pdPASS && response_ptr != nullptr)
          {
            ESP_LOGD(TAG, "<< Got response from heatpump");
            if (this->log_uart_msg_)
              PanasonicHelpers::log_uart_hex(UART_LOG_RX, *response_ptr, ',');


            auto current_response = this->check_response_(*response_ptr);
            switch (current_response) {
            case ResponseType::UNKNOWN:
              this->loop_state_ = LoopState::SEND_REQUEST;
              break;
            case ResponseType::STANDARD:
              this->heatpump_default_message_ = std::move(*response_ptr);
              this->loop_state_ = LoopState::PUBLISH_SENSOR;
              break;
            case ResponseType::EXTRA:
              this->heatpump_extra_message_ = std::move(*response_ptr);
              this->loop_state_ = LoopState::PUBLISH_EXTRA_SENSOR;
              break;
            }

            delete response_ptr;
          }
          else
          {
            ESP_LOGI(TAG, "Timeout2: %s", this->uart_client_timeout_exceeded_ ? "true" : "false");
            // no response to process, try to send next request
            this->loop_state_ = LoopState::SEND_REQUEST;
          }
        }
        break;
      case LoopState::PUBLISH_SENSOR:
        for (auto* entity : this->sensors_) {
          entity->publish_new_state(this->heatpump_default_message_);
        }
        this->loop_state_ = LoopState::PUBLISH_BINARY_SENSOR;
        break;
      case LoopState::PUBLISH_BINARY_SENSOR:
        for (auto* entity : this->binary_sensors_) {
          entity->publish_new_state(this->heatpump_default_message_);
        }
        this->loop_state_ = LoopState::PUBLISH_TEXT_SENSOR;
        break;
      case LoopState::PUBLISH_TEXT_SENSOR:
        for (auto* entity : this->text_sensors_) {
          entity->publish_new_state(this->heatpump_default_message_);
        }
        this->loop_state_ = LoopState::PUBLISH_NUMBER;
        break;
      case LoopState::PUBLISH_NUMBER:
        for (auto* entity : this->numbers_) {
          entity->publish_new_state(this->heatpump_default_message_);
        }
        this->loop_state_ = LoopState::PUBLISH_SELECT;
        break;
      case LoopState::PUBLISH_SELECT:
        for (auto* entity : this->selects_) {
          entity->publish_new_state(this->heatpump_default_message_);
        }
        this->loop_state_ = LoopState::PUBLISH_SWITCH;
        break;
      case LoopState::PUBLISH_SWITCH:
        for (auto* entity : this->switches_) {
          entity->publish_new_state(this->heatpump_default_message_);
        }
        this->loop_state_ = LoopState::PUBLISH_CLIMATE;
        break;
      case LoopState::PUBLISH_CLIMATE:
        for (auto* entity : this->climates_) {
          entity->publish_new_state(this->heatpump_default_message_);
        }
        this->loop_state_ = LoopState::SEND_REQUEST;
        break;
      case LoopState::PUBLISH_EXTRA_SENSOR:
        for (auto* entity : this->extra_sensors_) {
          entity->publish_new_state(this->heatpump_extra_message_);
        }
        this->loop_state_ = LoopState::SEND_REQUEST;
        break;
      case LoopState::SEND_REQUEST:
        this->send_next_request_();
        // kein break -> Fallthrough
      default:
        this->loop_state_ = LoopState::CHECK_RESPONSE;
        break;
      };
    }


    void PanasonicHeatpumpComponent::uart_task_(void *pvParameters)
    {
      auto *self = static_cast<PanasonicHeatpumpComponent *>(pvParameters);
      std::vector<uint8_t> rx_buffer;
      rx_buffer.reserve(256);

      while (true) {
        // We process the data from the primary interface
        if (self->receive_from_uart_(self->parent_, rx_buffer))
        {
          auto *response = new std::vector<uint8_t>(rx_buffer);
          if (xQueueSend(self->response_queue_handle_, &response, 0) != pdPASS)
          {
            ESP_LOGW(TAG, "Response queue full, dropping heatpump packet");
            delete response;
          }
          // ... and pass on a copy to CZ-TAW1
          if (self->uart_client_ != nullptr)
          {
            self->uart_client_->write_array(rx_buffer);
          }
        }
        else
          vTaskDelay(pdMS_TO_TICKS(10));
      }
    }


    void PanasonicHeatpumpComponent::client_uart_task_(void *pvParameters)
    {
      auto *self = static_cast<PanasonicHeatpumpComponent *>(pvParameters);
      std::vector<uint8_t> rx_buffer;
      rx_buffer.reserve(256);

      while (true) {
        // We process the data from the client interface
        if (self->receive_from_uart_(self->uart_client_, rx_buffer))
        {
          auto *cmd = new std::vector<uint8_t>(rx_buffer);
          if (xQueueSend(self->command_queue_handle_, &cmd, 0) != pdPASS)
          {
            ESP_LOGW(TAG, "Command queue full, dropping CZ-TAW packet");
            delete cmd;
          }
          self->last_client_request_time_ = millis();
          self->uart_client_timeout_exceeded_ = false;
        }
        else
          vTaskDelay(pdMS_TO_TICKS(10));
      }
    }


    bool PanasonicHeatpumpComponent::receive_from_uart_(uart::UARTComponent *src, std::vector<uint8_t> &buffer)
    {
      uint8_t start_byte;
      // We are in a separate thread, waiting to receive a byte
      while (not src->available())
        vTaskDelay(pdMS_TO_TICKS(5));

      if ( not src->read_byte(&start_byte) )
        return false;

      // Message shall start with 0x31, 0x71 or 0xF1, if not skip this byte
      if ( start_byte != 0x31 && start_byte != 0x71 && start_byte != 0xF1 )
      {
        return false;
      }

      // packet starts, clear buffer
      buffer.clear();
      buffer.reserve(256); // reserve space for the whole packet
      // read whole header
      buffer.resize(header::SIZE);
      // insert start byte
      buffer[0] = start_byte;
      // read the rest of the header

      if( src->available() < header::SIZE-1 )
        vTaskDelay(pdMS_TO_TICKS(5));

      auto succed = src->read_array(&buffer[1], header::SIZE-1);
      if ( not (succed && header::is_valid(buffer)) ) {
        ESP_LOGD(TAG, "Wrong Packet Header..."); // DEAKTIVIEREN nur ZUM TESTEN
        // timeout, start over
        return false;
      }

      // got header ... read the rest of the packet
      //ESP_LOGD(TAG, "Got Header %s", format_hex_pretty(buffer).c_str());
      size_t total_expected = header::get_packet_size(buffer);
      //ESP_LOGD(TAG, "Got Header, packet %d bytes", total_expected);
      size_t remaining = total_expected - buffer.size();

      while (remaining > 0) {
        size_t current_size = buffer.size();
        size_t to_read = std::min((size_t)8, remaining);
        buffer.resize(current_size + to_read);
        if( src->available() < to_read )
          vTaskDelay(pdMS_TO_TICKS(10));
        //ESP_LOGD(TAG, "to_read: %d of %d", to_read, remaining);
        if ( not src->read_array(&buffer[current_size], to_read) ) {
          // timeout
          return false;
        }
        remaining -= to_read;
      }
      // packet is complete, verify checksum
      uint8_t checksum = 0;
      for (const auto b : buffer)
        checksum += b;

      if ( checksum != 0 ) {
        ESP_LOGW(TAG, "Invalid message: wrong checksum" );
        return false;
      }
      // packet complete
      return true;
    }


    void PanasonicHeatpumpComponent::send_next_request_()
    {
      if ( millis() - request_send_time_ < REQUEST_SEND_INTERVAL)
      {
        // wait until the interval is over
        return;
      }

      std::vector<uint8_t> *cmd_ptr{nullptr};
      if (xQueueReceive(this->command_queue_handle_, &cmd_ptr, 0) != pdPASS || cmd_ptr == nullptr)
      {
        return;  // nothing queued
      }
      ESP_LOGD(TAG, " >> Send request to heatpump");
      // Optional: log before sending
      if (this->log_uart_msg_) {
        PanasonicHelpers::log_uart_hex(UART_LOG_TX, *cmd_ptr, ',');
      }

      // Send vector content over UART (robust API usage)
      this->write_array(cmd_ptr->data(), cmd_ptr->size());
      // !! do not flush !! loop blocked for longer than 30 ms // this->flush();

      delete cmd_ptr;

      request_send_time_ = millis();
    }


    void PanasonicHeatpumpComponent::queue_request_(const std::vector<uint8_t> &message)
    {
      auto *cmd = new std::vector<uint8_t>(message);
      // Check command_queue_handle_, function is caled before setup() initializes it !
      if (this->command_queue_handle_ == nullptr || xQueueSend(this->command_queue_handle_, &cmd, 0) != pdPASS) {
        ESP_LOGW(TAG, "Command queue unavailable or full, dropping packet");
        delete cmd;
      }
    }


    int PanasonicHeatpumpComponent::getResponseByte(const int index) {
      if (this->heatpump_default_message_.size() > index)
        return this->heatpump_default_message_[index];
      return -1;
    }

    int PanasonicHeatpumpComponent::getExtraResponseByte(const int index) {
      if (this->heatpump_extra_message_.size() > index)
        return this->heatpump_extra_message_[index];
      return -1;
    }


    ResponseType PanasonicHeatpumpComponent::check_response_(const std::vector<uint8_t>& data) {
      // Read response message:
      // format:          0x71 [payload_length] 0x01 [0x10 || 0x21] [[TOP0 - TOP114] ...] 0x00 [checksum]
      // payload_length:  payload_length + 3 = packet_length
      // checksum:        if (sum(all bytes) & 0xFF == 0) ==> valid packet
      if (data.size() != RESPONSE_MSG_SIZE) {
        ESP_LOGW(TAG, "Invalid response message length: recieved %d - expected %d", data.size(), RESPONSE_MSG_SIZE);
        return ResponseType::UNKNOWN;
      }

      // Get response type and save the response
      auto responseType = ResponseType::UNKNOWN;
      if (data[3] == 0x10) {
        responseType = ResponseType::STANDARD;

        //this->send_extra_request_ = data[3] == 0x10 && data[199] > 0x02 && this->send_extra_request_ == false ? true : false;
        // is an extra request required?
        if (data[199] > 0x02)
        {
          ESP_LOGD(TAG, "queue extra request");
          this->queue_request_(message_build(PanasonicCommand::PollingExtraMessage));
        }

      } else if (data[3] == 0x21) {
        responseType = ResponseType::EXTRA;
      }
      return responseType;
    }


    void PanasonicHeatpumpComponent::set_command_high_nibble(const uint8_t value, const uint8_t index) {
      std::vector<uint8_t> command_message(message_build(PanasonicCommand::CommandMessage));
      uint8_t lowNibble = this->heatpump_default_message_[index] & 0b1111;
      uint8_t highNibble = value << 4;
      // set command byte
      command_message[index] = highNibble + lowNibble;
      // calculate and set set checksum (last element)
      command_message.back() =
          PanasonicCommand::calcChecksum(command_message, command_message.size() - 1);

      ESP_LOGD(TAG, "queue_request set_command_high_nibble");
      this->queue_request_(command_message);
    }

    void PanasonicHeatpumpComponent::set_command_low_nibble(const uint8_t value, const uint8_t index) {
      std::vector<uint8_t> command_message(message_build(PanasonicCommand::CommandMessage));
      uint8_t highNibble = this->heatpump_default_message_[index] & 0b11110000;
      uint8_t lowNibble = value & 0b1111;
      // set command byte
      command_message[index] = highNibble + lowNibble;
      // calculate and set set checksum (last element)
      command_message.back() =
          PanasonicCommand::calcChecksum(command_message, command_message.size() - 1);

      ESP_LOGD(TAG, "queue_request set_command_low_nibble");
      this->queue_request_(command_message);
    }

    void PanasonicHeatpumpComponent::set_command_byte(const uint8_t value, const uint8_t index) {
      std::vector<uint8_t> command_message(message_build(PanasonicCommand::CommandMessage));
      // set command byte
      command_message[index] = value;
      // calculate and set set checksum (last element)
      command_message.back() =
          PanasonicCommand::calcChecksum(command_message, command_message.size() - 1);

      ESP_LOGD(TAG, "queue_request set_command_byte");
      this->queue_request_(command_message);
    }

    void PanasonicHeatpumpComponent::set_command_curve(const uint8_t value, const uint8_t index) {
      std::vector<uint8_t> command_message(message_build(PanasonicCommand::CommandMessage));
      // Set zone 1 curve bytes
      if (index == 75 || index == 76 || index == 77 || index == 78 || index == 86 || index == 87 || index == 88 ||
          index == 89) {
        command_message[75] = this->heatpump_default_message_[75];
        command_message[76] = this->heatpump_default_message_[76];
        command_message[77] = this->heatpump_default_message_[77];
        command_message[78] = this->heatpump_default_message_[78];
        command_message[86] = this->heatpump_default_message_[86];
        command_message[87] = this->heatpump_default_message_[87];
        command_message[88] = this->heatpump_default_message_[88];
        command_message[89] = this->heatpump_default_message_[89];
          }
      // Set zone 2 curve bytes
      if (index == 79 || index == 80 || index == 81 || index == 82 || index == 90 || index == 91 || index == 92 ||
          index == 93) {
        command_message[79] = this->heatpump_default_message_[79];
        command_message[80] = this->heatpump_default_message_[80];
        command_message[81] = this->heatpump_default_message_[81];
        command_message[82] = this->heatpump_default_message_[82];
        command_message[90] = this->heatpump_default_message_[90];
        command_message[91] = this->heatpump_default_message_[91];
        command_message[92] = this->heatpump_default_message_[92];
        command_message[93] = this->heatpump_default_message_[93];
          }

      // set command byte
      command_message[index] = value;
      // calculate and set set checksum (last element)
      command_message.back() =
          PanasonicCommand::calcChecksum(command_message, command_message.size() - 1);

      ESP_LOGD(TAG, "queue_request set_command_curve");
      this->queue_request_(command_message);
    }
  }  // namespace panasonic_heatpump
}  // namespace esphome
