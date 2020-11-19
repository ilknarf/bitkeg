#include "gtest/gtest.h"

#include <memory>
#include <filesystem>
#include <functional>
#include "bitkeg/keydir.h"
#include "bitkeg/keg_process.h"

namespace bitkeg {

TEST(KegProcessTest, WriteKeyTest) {
  auto dir = "target/test";
  auto k = new KeyDir(dir);
  auto keg = KegProcess(std::shared_ptr<KeyDir> (k));

  // put keys
  keg.Put("hello", "goodbye");
  keg.Put("noon", "cowboy");

  ASSERT_EQ(keg.Get("hello"), "goodbye");
  ASSERT_EQ(keg.Get("noon"), "cowboy");

  // overwritten key
  keg.Put("hello", "not goodbye");
  ASSERT_EQ(keg.Get("hello"), "not goodbye");

  // cleanup
  std::filesystem::remove_all(dir);
}

TEST(KegProcessTest, DeleteKeyTest) {
  auto dir = "target/test";
  auto k = new KeyDir(dir);
  auto keg = KegProcess(std::shared_ptr<KeyDir> (k));

  // put keys
  keg.Put("hello", "goodbye");
  keg.Put("noon", "cowboy");

  ASSERT_EQ(keg.Get("hello"), "goodbye");
  ASSERT_EQ(keg.Get("noon"), "cowboy");

  // cleanup
  std::filesystem::remove_all(dir);
}

TEST(KegProcessTest, FoldTest) {
  auto dir = "target/test";
  auto k = new KeyDir(dir);
  auto keg = KegProcess(std::shared_ptr<KeyDir> (k));

  // put keys
  keg.Put("hello", "goodbye");
  keg.Put("noon", "cowboy");

  auto folded = keg.Fold<size_t>([](std::string key, std::string val, size_t so_far) -> auto {
        return val.length() + so_far;
        }, 0);

  ASSERT_EQ(13, folded);

  // cleanup
  std::filesystem::remove_all(dir);
}

} // namespace bitkeg

