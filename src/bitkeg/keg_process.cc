#include "bitkeg/keg_process.h"

#include "util/crc8.h"
#include "bitkeg/bitkeg.h"

#include <iostream>

namespace bitkeg {

// exception header
class FileExistsException : virtual public std::exception {
  const char *what() noexcept;
};

std::string RandomString();

//KegProcess implementations
KegProcess::KegProcess(std::shared_ptr<KeyDir> k) {
  key_dir_ = k;

  auto dir = k->Dir();

  std::filesystem::path filepath(dir);
  filepath.append(RandomString());

  while (std::filesystem::exists(filepath)) {
    filepath = std::filesystem::path(dir);
    filepath.append(RandomString());
  }

  current_file_ = std::ofstream (filepath, std::ios::binary);
  current_filename_ = filepath.generic_string();
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

  // add time_t
  for (int i = sizeof(t) - 1; i >= 0; i--) {
    char next = (t >> (i * 8)) & 0xff;
    current_file_ << next;
  }

  // add key_sz
  for (int i = sizeof(key_sz) - 1; i >= 0; i--) {
    char next = (key_sz >> (i * 8)) & 0xff;  // NOLINT
    current_file_ << next;
  }

  // add val_sz
  for (int i = sizeof(val_sz) - 1; i >= 0; i--) {
    char next = (val_sz >> (i * 8)) & 0xff;  // NOLINT
    current_file_ << next;
  }

  current_file_ << key;
  current_file_ << val;

  // flush to write
  current_file_.flush();

  auto b = BitkegEntry{
      .file_id = CurrentFilename(),
      .value_sz = val_sz,  // value length in bytes
      .value_pos = val_pos,  // current write location
      .t_stamp = t,
  };

  key_dir_->Put(key, b);
}

std::string KegProcess::Get(std::string key) {
  auto entry = key_dir_->Get(key);

  auto filename = entry.file_id;
  auto offset = entry.value_pos;

  std::ifstream f;
  f.open(filename, std::ios::binary);
  f.seekg(offset);

  char checksum;
  f.read(&checksum, 1);
  time_t t = 0;

  time_t t_stamp = 0;
  for (int i = 0; i < sizeof(time_t); i++) {
    char tmp;
    f.read(&tmp, 1);
    // shift left a byte
    t_stamp <<= 8;
    t_stamp += tmp;
  }

  uint16_t key_sz = 0;
  for (int i = 0; i < sizeof(uint16_t); i++) {
    char tmp;
    f.read(&tmp, 1);
    // shift left a byte
    key_sz <<= 8;
    key_sz += tmp;
  }

  uint32_t val_sz = 0;
  for (int i = 0; i < sizeof(uint32_t); i++) {
    char tmp;
    f.read(&tmp, 1);
    // shift left a byte
    val_sz <<= 8;
    val_sz += tmp;
  }

  // checksum
  crc8::CRC8 crc;

  crc.Add((uint8_t) checksum);
  crc.Add(t);
  crc.Add(key_sz);
  crc.Add(val_sz);

  // get key from disk
  char *disk_key = new char[key_sz];
  f.read(disk_key, key_sz);

  for (int i = 0; i < key_sz; i++) {
    crc.Add((uint8_t) disk_key[i]);
  }

  // get value
  char *value = new char[val_sz];
  f.read(value, val_sz);

  std::string val;

  for (int i = 0; i < val_sz; i++) {
    auto next = value[i];
    crc.Add((uint8_t) next);
    val.push_back(next);
  }

  delete[] disk_key;
  delete[] value;

  if (crc.Sum() != checksum) {
    //STUB handle mismatched checksums
  }

  return val;
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
