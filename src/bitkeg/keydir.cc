#include "bitkeg/keydir.h"

namespace bitkeg {

KeyDir::KeyDir(std::string dir) : dir_(dir) {
  std::filesystem::create_directories(dir);
}

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

  // get pair
  auto entry = entry_map_.at(key);

  return entry;
}

bool KeyDir::Contains(std::string key) {
  // get read latch
  std::shared_lock shared(rw_latch_);

  auto it = entry_map_.find(key);

  return it != entry_map_.end();
}

void KeyDir::Put(const std::string key, BitkegEntry val) {
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

std::string KeyDir::Dir() {
  // get read latch
  std::shared_lock shared(rw_latch_);
  return dir_.string();
}

} // namespace bitkeg