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
  template<typename Acc>
  using FoldFn = std::function<Acc(std::string, std::string, Acc)>;
  explicit KegProcess(std::shared_ptr<KeyDir> k);
  // Fold over K-V pairs
  template<typename Acc>
  Acc Fold(FoldFn<Acc> fn, Acc acc0) {
    // get read latch
    std::shared_lock shared(key_dir_->rw_latch_);
    for (auto key : ListKeys()) {
      auto val = Get(key);
      acc0 = fn(key, val, acc0);
    }

    return acc0;
  }
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
