#ifndef BITKEG_INCLUDE_KEG_PROCESS_H_
#define BITKEG_INCLUDE_KEG_PROCESS_H_

#include <string>
#include <iostream>
#include <filesystem>

#include "keydir.h"

namespace bitkeg {

class KegProcess {
 public:
  explicit KegProcess(std::shared_ptr<KeyDir> k);
  // put key
  void Put(std::string key, std::string value);
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

class FileExistsException : virtual public std::exception {
  const char *what() noexcept;
};

} // namespace bitkeg
#endif //BITKEG_INCLUDE_KEG_PROCESS_H_
