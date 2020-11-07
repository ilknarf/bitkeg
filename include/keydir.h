#ifndef BITKEG_SRC_KEYDIR_H_
#define BITKEG_SRC_KEYDIR_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

#include "../include/bitkeg_entry.h"

namespace bitkeg {

class KeyDir {
 public:
  // default constructor
  KeyDir(std::string dir);
  // Fold over K-V pairs
  template<typename Acc>
  Acc Fold(Acc (*fn)(std::string _key, std::string _val, Acc _so_far), Acc acc0);
  // Get key
  BitkegEntry Get(std::string key);
  // List all keys
  std::vector<std::string> ListKeys();
  // Put keys
  void Put(std::string key, BitkegEntry val);
  // Merge keg
  void Merge();
  // Get working directory
  const std::string Dir();

 protected:
  const std::string dir_;
  std::shared_mutex rw_latch_;

  std::unordered_map<std::string, BitkegEntry> entry_map_;
};

} // namespace bitkeg

#endif //BITKEG_SRC_KEYDIR_H_
