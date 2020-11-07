#ifndef BITKEG_BITKEG_H
#define BITKEG_BITKEG_H

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <ctime>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <exception>

#include "../include/keydir.h"

namespace bitkeg {

class KegProcess {
 public:
  KegProcess(std::shared_ptr<KeyDir> k);
  ~KegProcess();
  void Put(std::string key, std::string value);
  std::vector<std::string> ListKeys();
 protected:
  void OpenNewFile();
  std::shared_ptr<KeyDir> key_dir_;
  std::ofstream current_file_;
};

class Bitkeg {
 public:
  Bitkeg();
  KegProcess Open(std::string dir);
 protected:
  std::unordered_map<std::string, std::shared_ptr<KeyDir> > open_kegs_;
};

std::string RandomString();

class FileExistsException : virtual public std::exception {
  const char *what() noexcept;
};

} // namespace bitkeg
#endif //BITKEG_BITKEG_H
