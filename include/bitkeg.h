#ifndef BITKEG_BITKEG_H
#define BITKEG_BITKEG_H

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <ctime>

using std::string;
using std::map;
using std::shared_ptr;
using std::vector;
using std::time_t;

class Bitkeg {
 public:
  Bitkeg();
  shared_ptr<BitkegInstance> Open(string dir);
 private:
  map<string, shared_ptr<BitkegInstance>> open_kegs{};
};

class BitkegInstance {
 public:
  BitkegInstance(string dir);
  string Get(string key);
  void Put(string key, string val);
  vector<string> ListKeys();
  template<typename Acc>
  Acc Fold(Acc (*fn)(string key, string val, Acc so_far), Acc acc0);
  string GetDir();
 private:
  string dir;
  map<string, BitkegEntry> entry_map;
};

struct BitkegEntry {
  string file_id;
  int value_sz;
  long value_pos;
  time_t tstamp;
};

#endif //BITKEG_BITKEG_H
