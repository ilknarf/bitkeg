#include "gtest/gtest.h"

#include "bitkeg.h"

TEST(KeyDir, SuccessfulInsertion) {
  auto key_dir = new KeyDir("hello");
  key_dir->Put("hello", BitkegEntry{});

  auto l = key_dir->ListKeys().size();
  EXPECT_EQ(1, l);
}

TEST(Nothing, Something) {
  EXPECT_EQ(0, 0);
}