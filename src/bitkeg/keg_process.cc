#include "bitkeg/keg_process.h"

#include "util/crc8.h"
#include "bitkeg/bitkeg.h"

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
  uint32_t val_sz = val.length();
  uint16_t key_sz = key.length();

  // compute crc-8
  crc8::CRC8 crc;
  crc.Add(t);
  crc.Add(key_sz);
  crc.Add(val_sz);

  // get val offset
  auto val_pos = current_file_.tellp();

  // write to file
  current_file_ << crc.Sum();
  current_file_ << t << key_sz << val_sz;
  current_file_ << key;

  current_file_ << val;
  current_file_ << '\0';

  auto b = BitkegEntry{
      .file_id = CurrentFilename(),
      .value_sz = val_sz, // value length in bytes
      .value_pos = val_pos, // current write location
      .t_stamp = t,
  };

  key_dir_->Put(key, b);
}

std::string KegProcess::Get(std::string key) {
  auto entry = key_dir_->Get(key);

  auto filename = entry.file_id;
  auto offset = entry.value_pos;

  std::filesystem::path file (key_dir_->Dir());
  file.append(filename);

  std::ifstream f;
  f.open(filename, std::ios::binary);
  f.seekg(offset);

  char *bytes = new char [MAX_ENTRY_SIZE];

  f.getline(bytes, MAX_ENTRY_SIZE, '\0');

  uint8_t checksum = bytes[0];

  crc8::CRC8 crc;

  int i= 1;
  while (bytes[i] != '\0') {
    crc.Add((uint8_t) bytes[i]);
  }

  if (crc.Sum() != checksum) {
    //STUB handle mismatched checksums
    throw 1;
  }

  // checksum + timestamp + 2 (key_length) + 4 (val_length) + key_length
  size_t start_position = 1 + sizeof(time_t) + 6 + key.length();

  // use start_position to get string
  std::string value(&bytes[start_position]);

  // delete buffer
  delete[] bytes;

  return value;
}

bool KegProcess::Contains(std::string key) {
  return key_dir_->Contains(key);
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
