#pragma once
#include <cmath>
#include <vector>

#define REQUEST_INIT_MSG_SIZE 8
#define REQUEST_DATA_MSG_SIZE 111
#define REQUEST_OPTIONAL_MSG_SIZE 20


namespace esphome
{
  namespace panasonic_heatpump
  {
    class PanasonicCommand
    {
    public:
      PanasonicCommand() = delete;

      static uint8_t calcChecksum(std::vector<uint8_t>& data, int length);
      static uint8_t setMultiply2(size_t input);
      static uint8_t setMultiply4(size_t input);
      static uint8_t setPlus1Multiply4(size_t input);
      static uint8_t setPlus1Multiply8(size_t input);
      static uint8_t setPlus1Multiply16(size_t input);
      static uint8_t setPlus1Multiply64(size_t input);
      static uint8_t setPlus1(size_t input);
      static uint8_t setPlus73(size_t input);
      static uint8_t setPlus128(size_t input);
      static uint8_t setOperationMode(size_t input);
      static uint8_t temp2hex(float temp);
      static uint8_t setByte6(uint8_t byte6, int val, int base, int bit);
      static uint8_t setDemandControl(size_t input);

      static const uint8_t InitialMessage[REQUEST_INIT_MSG_SIZE];
      static const uint8_t PeriodicalMessage[REQUEST_DATA_MSG_SIZE];
      static const uint8_t CommandMessage[REQUEST_DATA_MSG_SIZE];
    };
  }  // namespace panasonic_heatpump
}  // namespace esphome
