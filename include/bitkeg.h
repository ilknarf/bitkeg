#ifndef BITKEG_BITKEG_H
#define BITKEG_BITKEG_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <ctime>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <exception>

using std::string;
using std::map;
using std::shared_ptr;
using std::vector;
using std::time_t;
using std::pair;

namespace bitkeg {

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
  const string Dir();
  vector<string> ListKeys();
  void Put(string key, BitkegEntry val);
  void Merge();
 private:
  const string dir_;

  map<string, const BitkegEntry> entry_map_;
};

class KegProcess {
 public:
  KegProcess(shared_ptr<KeyDir> k);
  ~KegProcess();
  void Put(string key, string value);
  vector<string> ListKeys();
 private:
  void OpenNewFile();
  KeyDir key_dir_;
  std::ofstream current_file_;
};

class Bitkeg {
 public:
  Bitkeg();
  KegProcess Open(string dir);
 private:
  map<string, shared_ptr<KeyDir> > open_kegs_;
};

string RandomString();

class FileExistsException : virtual public std::exception {
  const char *what() noexcept;
};

} // namespace bitkeg
#endif //BITKEG_BITKEG_H
