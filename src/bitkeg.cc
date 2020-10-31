#include <map>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include "../include/bitkeg.h"

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;
using std::pair;

// Bitkeg implementations
Bitkeg::Bitkeg() : open_kegs_() {}

shared_ptr<KeyDir> Bitkeg::Open(string dir) {
  if (open_kegs_.count(dir) > 0) {
    return open_kegs_.at(dir);
  } else {
    auto new_keg_instance = std::make_shared<KeyDir>(dir);
    open_kegs_.insert(pair<string, shared_ptr<KeyDir> >(dir, new_keg_instance));

    return new_keg_instance;
  }
}

// KeyDir implementations
KeyDir::KeyDir(string dir) : dir_(dir) {}

template<typename Acc>
Acc KeyDir::Fold(Acc (*fn)(string key, string val, Acc so_far), Acc acc0) {
  for (auto key : ListKeys() ) {
    auto val = Get(key);
    acc0 = fn(key, val, acc0);
  }

  return acc0;
}

BitkegEntry KeyDir::Get(string key) {
  return BitkegEntry{};
}

void KeyDir::Put(string key, BitkegEntry val) {
  entry_map_.insert(pair<string, BitkegEntry>(key, val));
}

vector<string> KeyDir::ListKeys() {
  vector<string> v;
  for (auto pair : entry_map_) {
    v.push_back(pair.first);
  }

  return v;
}

string KeyDir::Dir() {
  return dir_;
}

