#ifndef BITKEG_BITKEG_H
#define BITKEG_BITKEG_H

#include <unordered_map>

#include "../include/keydir.h"
#include "../include/keg_process.h"

namespace bitkeg {

class Bitkeg {
 public:
  Bitkeg();
  KegProcess Open(std::string dir);
 protected:
  std::unordered_map<std::string, std::shared_ptr<KeyDir> > open_kegs_;
};

} // namespace bitkeg

#endif //BITKEG_BITKEG_H
