#include "util/crc8.h"

namespace crc8 {
  CRC8::CRC8() : remainder_(CRC8_INIT) {}

  void CRC8::Add(uint8_t c) {
    remainder_ ^= c;

    for (int j = 0; j < 8; j++) {
      if ((remainder_ & 0x80) != 0)
        remainder_ = (uint8_t) ((remainder_ << 1) ^ CRC8_POLY);
      else
        remainder_ <<= 1;
    }
  }

  void CRC8::Add(uint16_t l) {
    uint8_t byte_1 = l >> 8;
    uint8_t byte_2 = l & 0xff;

    Add(byte_1);
    Add(byte_2);
  }

  void CRC8::Add(uint32_t l) {
    uint8_t *bytes = new uint8_t[4];

    for (int i = 0; i < 4; i++) {
      bytes[3 - i] = l & 0xff;
      l >>= 8;
    }

    for (int i = 0; i < 4; i++) {
      Add(bytes[i]);
    }

    delete[] bytes;
  }

  void CRC8::Add(std::string s) {
    for (auto c : s) {
      Add((uint8_t) c);
    }
  }

  void CRC8::Add(time_t t) {
    uint8_t *bytes = new uint8_t[4];
    for (int i = 0; i < SIZE_T_SIZE; i++) {
      bytes[SIZE_T_SIZE - 1 - i] = t & 0xff;
      t >>= 8;
    }

    for (int i = 0; i < SIZE_T_SIZE; i++) {
      Add(bytes[i]);
    }

    delete[] bytes;
  }

  uint8_t CRC8::Sum() {
    return remainder_;
  }
}
