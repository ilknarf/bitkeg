#include <unordered_map>
#include <string>
#include "../include/bitkeg.h"

using std::unordered_map;
using std::string;

template<class K, class V>
class BitKeg {
  unordered_map<string, &KegInstance> activeConnections;
};


class KegInstance {
  string kegPath;

  int merge(int (*fn)) {

  }
};