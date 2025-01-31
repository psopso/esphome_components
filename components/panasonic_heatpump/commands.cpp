#include "commands.h"

#define REQUEST_DATA_SIZE 111
#define REQUEST_INITIAL_SIZE 8
#define REQUEST_OPTIONAL_SIZE 20

#define OPTIONALPCBQUERYTIME 1000   // send optional pcb query each second
#define OPTIONALPCBSAVETIME 300     // save each 5 minutes the current optional pcb state into flash to have valid values during reboot


namespace esphome
{
  namespace panasonic_heatpump
  {
    // ToDo: Use vector<unit8_t> instead of byte[]
    static uint8_t temp_command[REQUEST_DATA_SIZE] = { 0 };
    static uint8_t temp_command_optional[REQUEST_OPTIONAL_SIZE] = {
      0xF1, 0x11, 0x01, 0x50, 0x00, 0x00, 0x40, 0xFF, 0xFF, 0xE5, 0xFF, 0xFF, 0x00, 0xFF, 0xEB,
      0xFF, 0xFF, 0x00, 0x00, 0x00
    };

    static const uint8_t InitialRequest[REQUEST_INITIAL_SIZE] = {
      0x31, 0x05, 0x10, 0x01, 0x00, 0x00, 0x00, 0xB9
    };
    static const uint8_t PeriodicalRequest[REQUEST_DATA_SIZE] = {
      0x71, 0x6C, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x12
    };
    static const uint8_t CommandRequest[REQUEST_DATA_SIZE] = {
      0xF1, 0x6C, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x92
    };


    std::vector<uint8_t> PanasonicCommand::setCommand(uint8_t index, uint8_t newValue)
    {
      // initialize the command
      memcpy(temp_command, CommandRequest, sizeof(CommandRequest));
      // set command byte
      temp_command[index] = newValue;
      // calculate and set set checksum
      temp_command[REQUEST_DATA_SIZE - 1] = calcChecksum(temp_command, REQUEST_DATA_SIZE - 1);

      // convert to vector and return
      return std::vector<uint8_t>(temp_command, temp_command + REQUEST_DATA_SIZE);
    }

    std::vector<uint8_t> PanasonicCommand::setOptionalCommand(uint8_t index, uint8_t newValue)
    {
      // set command byte
      temp_command_optional[index] = newValue;
      // calculate and set set checksum
      temp_command_optional[REQUEST_OPTIONAL_SIZE - 1] = calcChecksum(temp_command_optional, REQUEST_OPTIONAL_SIZE - 1);

      // convert to vector and return
      return std::vector<uint8_t>(temp_command_optional, temp_command_optional + REQUEST_OPTIONAL_SIZE);
    }

    uint8_t PanasonicCommand::calcChecksum(uint8_t *command, int length)
    {
      uint8_t chk = 0;
      for (int i = 0; i < length; i++)
      {
        chk += command[i];
      }
      chk = (chk ^ 0xFF) + 01;
      return chk;
    }


    uint8_t PanasonicCommand::setMultiply2(unsigned int input)
    {
      return input * 2;
    }

    uint8_t PanasonicCommand::setMultiply4(unsigned int input)
    {
      return input * 4;
    }

    uint8_t PanasonicCommand::setPlus1Multiply4(unsigned int input)
    {
      return (input + 1) * 4;
    }

    uint8_t PanasonicCommand::setPlus1Multiply8(unsigned int input)
    {
      return (input + 1) * 8;
    }

    uint8_t PanasonicCommand::setPlus1Multiply16(unsigned int input)
    {
      return (input + 1) * 16;
    }

    uint8_t PanasonicCommand::setPlus1Multiply64(unsigned int input)
    {
      return (input + 1) * 64;
    }

    uint8_t PanasonicCommand::setPlus1(unsigned int input)
    {
      return input + 1;
    }

    uint8_t PanasonicCommand::setPlus73(unsigned int input)
    {
      return input + 73;
    }

    uint8_t PanasonicCommand::setPlus128(unsigned int input)
    {
      return input + 128;
    }

    uint8_t PanasonicCommand::setOperationMode(unsigned int input)
    {
      switch (input)
      {
        case 0: return 18;
        case 1: return 19;
        case 2: return 24;
        case 3: return 33;
        case 4: return 34;
        case 5: return 35;
        case 6: return 40;
      }
      return 0;
    }

    uint8_t PanasonicCommand::setBivalentMode(unsigned int input)
    {
      switch (input)
      {
        case 0: return 101;
        case 1: return 102;
        case 2: return 104;
        case 3: return 105;
        case 4: return 108;
        case 5: return 109;
      }
      return 0;
    }

    //start of optional pcb commands

    uint8_t PanasonicCommand::temp2hex(float temp)
    {
      int hextemp = 0;
      if (temp > 120)
      {
        hextemp = 0;
      }
      else if (temp < -78)
      {
        hextemp = 255;
      }
      else
      {
        uint8_t Uref = 255;
        int constant = 3695;
        int R25 = 6340;
        uint8_t T25 = 25;
        int Rf = 6480;
        float K = 273.15;
        float RT = R25 * exp(constant * (1 / (temp + K) - 1 / (T25 + K)));
        hextemp = Uref * (RT / (Rf + RT));
      }

      return hextemp;
    }

    uint8_t PanasonicCommand::setByte6(int val, int base, int bit)
    {
      return (temp_command_optional[6] & ~(base << bit)) | (val << bit);
    }

    uint8_t PanasonicCommand::setDemandControl(unsigned int input)
    {
      switch (input)
      {
        case 0: return 0xEB;
        case 1: return 0xB8;
        case 2: return 0x85;
        case 3: return 0x52;
        case 4: return 0x2B;
      }
      return 0;
    }

    std::string PanasonicCommand::toHexString(std::vector<uint8_t> &data)
    {
      char cmdArr[400];

      //ESP_LOGD("custom", "############ CMD: %s", to_hex_string(vec, REQUEST_DATA_SIZE));
      for (int i = 0; i < 10; i++)
      {
        if (i == 0) sprintf(cmdArr, "0x");
        if (i > 0) sprintf(cmdArr, "%s-", cmdArr);
        sprintf(cmdArr, "%s-%02X", cmdArr, data[i]);
      }
      std::string cmdStr = cmdArr;
      return cmdStr;
    }
  }  // namespace panasonic_heatpump
}  // namespace esphome