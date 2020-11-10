#include "gtest/gtest.h"

#include "bitkeg/keydir.h"

namespace bitkeg {
// Check whether insertion is stored in map.
TEST(KeyDirTest, SuccessfulInsertionTest) {
  auto key_dir = new KeyDir("hello");
  key_dir->Put("hello", BitkegEntry{});

  auto l = key_dir->ListKeys().size();
  EXPECT_EQ(1, l);
}

TEST(KeyDirTest, SomethingTest) {
  EXPECT_EQ(0, 0);
}

} // namespace bitkeg