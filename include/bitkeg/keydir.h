#ifndef BITKEG_SRC_KEYDIR_H_
#define BITKEG_SRC_KEYDIR_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <fstream>
#include <filesystem>
#include <functional>

#include "bitkeg/bitkeg_entry.h"

namespace bitkeg {

class KeyDir {
 public:
  // default constructor
  KeyDir(std::string dir);
  // Fold over K-V pairs
  template<typename Acc>
  Acc Fold(std::function<Acc(std::string, std::string, Acc)> fn, Acc acc0);
  // Get value entry
  BitkegEntry Get(std::string key);
  // Delete key
  void Delete(std::string key);
  // Contains key
  bool Contains(std::string key);
  // List all keys
  std::vector<std::string> ListKeys();
  // Put keys
  void Put(std::string key, BitkegEntry val);
  // Merge keg
  void Merge();
  // Get working directory
  std::string Dir();

 protected:
  const std::filesystem::path dir_;
  std::shared_mutex rw_latch_;

  std::unordered_map<std::string, BitkegEntry> entry_map_;
};

} // namespace bitkeg

#endif //BITKEG_SRC_KEYDIR_H_
