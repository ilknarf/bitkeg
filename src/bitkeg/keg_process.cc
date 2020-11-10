#include "bitkeg/keg_process.h"

namespace bitkeg {

// exception header
class FileExistsException : virtual public std::exception {
  const char *what() noexcept;
};

std::string RandomString();

//KegProcess implementations
KegProcess::KegProcess(std::shared_ptr<KeyDir> k) {
  key_dir_ = k;

  std::string filepath = RandomString();
  while (std::filesystem::exists(filepath)) {
    filepath = RandomString();
  }

  current_file_ = std::ofstream (filepath, std::ios::binary);
}

std::vector<std::string> KegProcess::ListKeys() {
  return key_dir_->ListKeys();
}

void KegProcess::Put(std::string key, std::string val) {
  auto t = std::time(nullptr);
  auto val_sz = (uint32_t) val.length();
  auto key_sz = (uint8_t) key.length();

  // write to file
  current_file_ << 5;
  current_file_ << t << key_sz << val_sz;
  current_file_ << key;

  auto val_pos = current_file_.tellp();
  current_file_ << val;

  auto b = BitkegEntry{
      .file_id = CurrentFilename(),
      .value_sz = val_sz, // value length in bytes
      .value_pos = val_pos, // current write location
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
