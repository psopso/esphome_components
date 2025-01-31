#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicCommand
    {
    public:
      PanasonicCommand() = delete;

      static std::vector<uint8_t> setCommand(uint8_t index, uint8_t newValue);
      static std::vector<uint8_t> setOptionalCommand(uint8_t index, uint8_t newValue);
      static uint8_t calcChecksum(uint8_t *command, int length);
      static uint8_t setMultiply2(unsigned int input);
      static uint8_t setMultiply4(unsigned int input);
      static uint8_t setPlus1Multiply4(unsigned int input);
      static uint8_t setPlus1Multiply8(unsigned int input);
      static uint8_t setPlus1Multiply16(unsigned int input);
      static uint8_t setPlus1Multiply64(unsigned int input);
      static uint8_t setPlus1(unsigned int input);
      static uint8_t setPlus73(unsigned int input);
      static uint8_t setPlus128(unsigned int input);
      static uint8_t setOperationMode(unsigned int input);
      static uint8_t setBivalentMode(unsigned int input);
      static uint8_t temp2hex(float temp);
      static uint8_t setByte6(int val, int base, int bit);
      static uint8_t setDemandControl(unsigned int input);
      static std::string toHexString(std::vector<uint8_t> &data);
    };
  }  // namespace panasonic_heatpump
}  // namespace esphome
