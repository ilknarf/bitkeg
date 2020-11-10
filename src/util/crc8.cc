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

  void CRC8::Add(std::string s) {
    for (auto c : s) {
      Add((uint8_t) c);
    }
  }

  uint8_t CRC8::Sum() {
    return remainder_;
  }
}
