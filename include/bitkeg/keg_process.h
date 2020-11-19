#ifndef BITKEG_INCLUDE_KEG_PROCESS_H_
#define BITKEG_INCLUDE_KEG_PROCESS_H_

#include <string>
#include <fstream>
#include <filesystem>
#include <memory>
#include <time.h>

#include "keydir.h"
#include "bitkeg/bitkeg_entry.h"

namespace bitkeg {

class KegProcess {
 public:
  explicit KegProcess(std::shared_ptr<KeyDir> k);
  // fold value
  template<typename Acc>
  Acc Fold(std::function<Acc(std::string, std::string, Acc)> fn, Acc acc0);
  // put key-value
  void Put(std::string key, std::string value);
  // get value
  std::string Get(std::string key);
  // delete key
  void Delete(std::string key);
  // check contains key
  bool Contains(std::string key);
  // list all keys
  std::vector<std::string> ListKeys();
  // get current filename
  std::string CurrentFilename();
 protected:
  void OpenNewFile();
  std::shared_ptr<KeyDir> key_dir_;
  std::string current_filename_;
  std::ofstream current_file_;
};

} // namespace bitkeg

#endif //BITKEG_INCLUDE_KEG_PROCESS_H_
