#include "gtest/gtest.h"

#include <string>
#include "util/crc8.h"

namespace crc8 {
// test check value for crc8
TEST(CRC8Test, CheckValueTest) {
  std::string s = "123456789";
  uint8_t expected = 0xf7;

  CRC8 crc;
  crc.Add(s);

  EXPECT_EQ(crc.Sum(), expected);
}

TEST(CRC8Test, AddStringTest) {
  std::string s = "\xbe\xef";
  uint8_t expected = 0x92;

  CRC8 crc;
  crc.Add(s);

  EXPECT_EQ(crc.Sum(), expected);
}

TEST(CRC8Test, AddCharTest) {
  char c = '\0';
  uint8_t expected = 0xac;

  CRC8 crc;
  crc.Add((uint8_t) c);

  EXPECT_EQ(crc.Sum(), expected);
}

TEST(CRC8Test, AddIntTest) {
  uint16_t l = (0xbe << 8) + 0xef;
  uint8_t expected = 0x92;

  CRC8 crc;
  crc.Add(l);

  EXPECT_EQ(crc.Sum(), expected);
}

} // namespace crc8