#include "../include/keg_process.h"

namespace bitkeg {

std::string RandomString();

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
  auto b = BitkegEntry{
      .file_id = CurrentFilename(),
      .value_sz = 0,
      .value_pos = 0,
      .t_stamp = t,
  };

  key_dir_->Put(key, b);
}

std::string KegProcess::CurrentFilename() {
  return current_filename_;
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
