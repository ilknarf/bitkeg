#ifndef BITKEG_SRC_BITKEG_ENTRY_H_
#define BITKEG_SRC_BITKEG_ENTRY_H_

#include <string>

#include "keydir.h"

namespace bitkeg {

struct BitkegEntry {
  friend class KeyDir;

  std::string file_id;
  int value_sz;
  long value_pos;
  time_t t_stamp;
};

} // namespace bitkeg

#endif //BITKEG_SRC_BITKEG_ENTRY_H_
