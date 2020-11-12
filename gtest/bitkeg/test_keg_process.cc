#include "gtest/gtest.h"

#include <memory>
#include <iostream>
#include "bitkeg/keydir.h"
#include "bitkeg/keg_process.h"

namespace bitkeg {

TEST(KegProcessTest, WriteFileTest) {
  auto k = new KeyDir("target/test");
  auto keg = KegProcess(std::shared_ptr<KeyDir> (k));

keg.Put("hello", "goodbye");

ASSERT_EQ(keg.Get("hello"), "goodbye");

}

} // namespace bitkeg

