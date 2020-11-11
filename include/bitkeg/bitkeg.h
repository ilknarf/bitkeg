#ifndef BITKEG_BITKEG_H
#define BITKEG_BITKEG_H

#include <unordered_map>

#include "keydir.h"
#include "keg_process.h"

namespace bitkeg {

const int MAX_ENTRY_SIZE = 1024;

class Bitkeg {
 public:
  Bitkeg();
  KegProcess Open(std::string dir);
 protected:
  std::unordered_map<std::string, std::shared_ptr<KeyDir> > open_kegs_;
};

} // namespace bitkeg

#endif //BITKEG_BITKEG_H
