#ifndef BITKEG_BITKEG_H
#define BITKEG_BITKEG_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <ctime>

using std::string;
using std::map;
using std::shared_ptr;
using std::vector;
using std::time_t;
using std::pair;

struct BitkegEntry {
  string file_id;
  int value_sz;
  long value_pos;
  time_t t_stamp;
};

class KeyDir {
 public:
  KeyDir(string dir);

  template<typename Acc>
  Acc Fold(Acc (*fn)(string _key, string _val, Acc _so_far), Acc acc0);
  BitkegEntry Get(string key);
  string Dir();
  vector<string> ListKeys();
  void Put(string key, BitkegEntry val);
  void Merge();
 private:
  const string dir_;

  map<string, const BitkegEntry> entry_map_;
};

class KegProcess {
 public:
  KegProcess(KeyDir k);
  void Put(string key, string value);
  vector<string> ListKeys();
 private:
  KeyDir key_dir_;
};

class Bitkeg {
 public:
  Bitkeg();
  shared_ptr<KeyDir> Open(string dir);
 private:
  map<string, shared_ptr<KeyDir> > open_kegs_;
};

#endif //BITKEG_BITKEG_H
