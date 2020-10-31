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
Bitkeg::Bitkeg() : open_kegs() {}

shared_ptr<BitkegInstance> Bitkeg::Open(string dir) {
  if (open_kegs.count(dir) > 0) {
    return open_kegs[dir];
  } else {
    auto new_keg_instance = std::make_shared<BitkegInstance>(dir);
    open_kegs.insert(pair<string, shared_ptr<BitkegInstance> >(dir, new_keg_instance));

    return new_keg_instance;
  }
}

BitkegInstance::BitkegInstance(string dir) : dir(dir) {}

// BitkegInstance implementations
template<typename Acc>
Acc BitkegInstance::Fold(Acc (*fn)(string key, string val, Acc so_far), Acc acc0) {
  for (auto key : ListKeys() ) {
    auto val = Get(key);
    acc0 = fn(key, val, acc0);
  }

  return acc0;
}

void BitkegInstance::Put(string key, string val) {

}

string BitkegInstance::GetDir() {
  return dir;
}

