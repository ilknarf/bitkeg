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

} // namespace bitkeg
