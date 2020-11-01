#include "../include/bitkeg.h"

// Bitkeg implementations
Bitkeg::Bitkeg() : open_kegs_() {}

KegProcess* Bitkeg::Open(string dir) {
  if (open_kegs_.count(dir) > 0) {
    return new KegProcess(open_kegs_.at(dir));
  } else {
    auto new_keg_instance = std::make_shared<KeyDir>(dir);
    open_kegs_.insert(pair<string, shared_ptr<KeyDir> >(dir, new_keg_instance));

    return new KegProcess(new_keg_instance);
  }
}

// KeyDir implementations
KeyDir::KeyDir(string dir) : dir_(dir) {}

template<typename Acc>
Acc KeyDir::Fold(Acc (*fn)(string key, string val, Acc so_far), Acc acc0) {
  for (auto key : ListKeys() ) {
    auto val = Get(key);
    acc0 = fn(key, val, acc0);
  }

  return acc0;
}

BitkegEntry KeyDir::Get(string key) {
  return BitkegEntry{};
}

void KeyDir::Put(string key, BitkegEntry val) {
  entry_map_.insert(pair<string, BitkegEntry>(key, val));
}

vector<string> KeyDir::ListKeys() {
  vector<string> v;
  for (auto p : entry_map_) {
    v.push_back(p.first);
  }

  return v;
}

const string KeyDir::Dir() {
  return dir_;
}

//KegProcess implementations
KegProcess::KegProcess(shared_ptr<KeyDir> k) : key_dir_(*k), current_file_() {
  string filepath = RandomString();
  if (std::filesystem::exists(filepath)) {
    throw 1;
  }
  current_file_.open(filepath, std::ios::binary);
}

vector<string> KegProcess::ListKeys() {
  return key_dir_.ListKeys();
}

void KegProcess::Put(string key, string value) {
  auto t = time(nullptr);
  auto b = BitkegEntry{
      .file_id = "",
      .value_sz = 0,
      .value_pos = 0,
      .t_stamp = t,
  };

  key_dir_.Put(key, b);
}

// STUB for random string function
string RandomString() {
  return "hello";
}

// exception implementation
const char *FileExistsException::what() noexcept {
  return "File already exists";
}
