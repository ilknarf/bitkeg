#include <map>
#include <string>
#include <vector>
#include <memory>
#include "../include/bitkeg.h"

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

// Bitkeg implementations
Bitkeg::Bitkeg() : open_kegs(new map<string, shared_ptr<KegInstance>>) {}

shared_ptr<KegInstance> Bitkeg::Open(string dir) {
  if (open_kegs.count(dir) > 0) {
    return open_kegs[dir];
  } else {

  }
}

// BitkegInstance implementations
template<typename Acc>
Acc BitkegInstance::Fold(Acc (*fn)(string key, string val, Acc so_far), acc0) {
  for (auto key : ListKeys() ) {
    auto val = Get(key)l
    acc0 = fn(key, val, acc0);
  }

  return acc0;
}

void BitkegInstance::Put(string key, string val) {

}

string BitkegInstance::GetDir() {
  return dir;
}

