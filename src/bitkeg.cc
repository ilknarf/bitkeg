#include "../include/bitkeg.h"

namespace bitkeg {
// Bitkeg implementations
Bitkeg::Bitkeg() : open_kegs_() {}

KegProcess Bitkeg::Open(std::string dir) {
  if (open_kegs_.count(dir) > 0) {
    return KegProcess(open_kegs_.at(dir));
  } else {
    auto new_keg_instance = std::make_shared<KeyDir>(dir);
    open_kegs_[dir] = new_keg_instance;

    return KegProcess(new_keg_instance);
  }
}

//KegProcess implementations
KegProcess::KegProcess(std::shared_ptr<KeyDir> k) {
  key_dir_ = k;

  std::string filepath = RandomString();
  while (std::filesystem::exists(filepath)) {
    filepath = RandomString();
  }

  current_file_.open(filepath, std::ios::binary);
}

std::vector<std::string> KegProcess::ListKeys() {
  return key_dir_->ListKeys();
}

void KegProcess::Put(std::string key, std::string value) {
  auto t = time(nullptr);
  auto b = BitkegEntry();

  key_dir_->Put(key, b);
}
KegProcess::~KegProcess() {
  delete (&current_file_);
}
void KegProcess::OpenNewFile() {
  current_file_.close();
  current_file_ = std::ofstream();

  std::string filepath = RandomString();
  while (std::filesystem::exists(filepath)) {
    filepath = RandomString();
  }

  current_file_.open(filepath, std::ios::binary);
}

// STUB for random string function
std::string RandomString() {
  return "hello";
}

// exception implementation
const char *FileExistsException::what() noexcept {
  return "File already exists";
}

} // namespace bitkeg
