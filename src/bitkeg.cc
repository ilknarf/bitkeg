#include <map>
#include <string>
#include <vector>
#include <functional>
#include "../include/bitkeg.h"

using std::map;
using std::string;
using std::vector;
using std::less;

class BitKeg {
 public:
  BitKeg() : less() {

  }

  void Open(string dir) {

  }
 private:
  map<string, &KegInstance<string, string>>;
};

class KegInstance {
 public:
  void Merge() {

  }

  template<typename Acc>
  Acc Fold(Acc (*fn)(string, string, Acc), acc0) {
    for (auto key : this->ListKeys() ) {
      auto val = this->Get(key)l
      acc0 = fn(key, val, acc0);
    }
  }

  vector<string> ListKeys() {
    return vector<string>();
  }

  string Get(K key) {
    return "";
  }
};