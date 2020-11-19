#include "gtest/gtest.h"

#include <memory>
#include <filesystem>
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

static size_t FoldLengths(std::string key, std::string val, size_t so_far) {
  return so_far + val.length();
}

TEST(KegProcessTest, FoldTest) {
  auto dir = "target/test";
  auto k = new KeyDir(dir);
  auto keg = KegProcess(std::shared_ptr<KeyDir> (k));

  // put keys
  keg.Put("hello", "goodbye");
  keg.Put("noon", "cowboy");

  KeyDir::FoldFn<size_t> fn = std::function(FoldLengths);
  auto folded = keg.Fold<size_t>(fn, 0);

  ASSERT_EQ(13, folded);

  // cleanup
  std::filesystem::remove_all(dir);
}

} // namespace bitkeg

