#include "bitkeg/keydir.h"

namespace bitkeg {

KeyDir::KeyDir(std::string dir) : dir_(dir) {}

template<typename Acc>
Acc KeyDir::Fold(Acc (*fn)(std::string key, std::string val, Acc so_far), Acc acc0) {
  // get read latch
  std::shared_lock shared(rw_latch_);
  for (auto key : ListKeys()) {
    auto val = Get(key);
    acc0 = fn(key, val, acc0);
  }

  return acc0;
}

BitkegEntry KeyDir::Get(std::string key) {
  // get read latch
  std::shared_lock shared(rw_latch_);

  return BitkegEntry{};
}

void KeyDir::Put(std::string key, BitkegEntry val) {
  // get write latch
  std::lock_guard lck(rw_latch_);

  entry_map_[key] = val;
}

void KeyDir::Merge() {}

std::vector<std::string> KeyDir::ListKeys() {
  // get read latch
  std::shared_lock shared(rw_latch_);

  std::vector<std::string> v;
  for (auto p : entry_map_) {
    v.push_back(p.first);
  }

  return v;
}

const std::string KeyDir::Dir() {
  // get read latch
  std::shared_lock shared(rw_latch_);
  return dir_;
}

} // namespace bitkeg