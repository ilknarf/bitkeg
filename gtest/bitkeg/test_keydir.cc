#include "gtest/gtest.h"

#include "bitkeg/keydir.h"
#include <filesystem>

namespace bitkeg {

// Check whether insertion is stored in map.
TEST(KeyDirTest, SuccessfulInsertionTest) {
  auto dir = "target/test";
  auto key_dir = new KeyDir(dir);
  key_dir->Put("hello", BitkegEntry{});

  auto l = key_dir->ListKeys().size();
  EXPECT_EQ(1, l);

  std::filesystem::remove_all(dir);
}

// Check whether insertion is stored in map.
TEST(KeyDirTest, KeyNotExistsTest) {
  auto dir = "target/test";
  auto key_dir = new KeyDir(dir);
  key_dir->Put("hello", BitkegEntry{});

  auto l = key_dir->ListKeys().size();
  EXPECT_EQ(1, l);

  EXPECT_EQ(key_dir->Contains("non-key"), false);

  std::filesystem::remove_all(dir);
}

} // namespace bitkeg