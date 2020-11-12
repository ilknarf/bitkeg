#ifndef BITKEG_INCLUDE_UTIL_CRC8_H_
#define BITKEG_INCLUDE_UTIL_CRC8_H_

#include <string>

namespace util {

const uint8_t CRC8_INIT = 0xff;
const uint8_t CRC8_POLY = 0x31;
const size_t SIZE_T_SIZE = sizeof(size_t);

/* CRC-8 Implementation (slow implementation without lookup tables).
 * follows these CRC8 specifications (from https://gist.github.com/bevice/4676232b92a41fb42f62):
 *   Name  : CRC-8
 *   Poly  : 0x31    x^8 + x^5 + x^4 + 1
 *   Init  : 0xFF
 *   Revert: false
 *   XorOut: 0x00
 *   Check : 0xF7 ("123456789")
 *   MaxLen: 15 bytes
 * */
class CRC8{
 public:
  CRC8();
  void Add(uint8_t c);
  void Add(uint16_t l);
  void Add(uint32_t l);
  void Add(time_t t);
  void Add(std::string s);
  uint8_t Sum();
 private:
  uint8_t remainder_;
};

} // namespace crc8

#endif //BITKEG_INCLUDE_UTIL_CRC8_H_
