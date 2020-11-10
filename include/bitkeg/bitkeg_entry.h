#ifndef BITKEG_SRC_BITKEG_ENTRY_H_
#define BITKEG_SRC_BITKEG_ENTRY_H_

#include <string>

#include "keydir.h"

namespace bitkeg {

struct BitkegEntry {
  std::string file_id;
  unsigned long value_sz;
  long long value_pos;
  time_t t_stamp;
};

} // namespace bitkeg

#endif //BITKEG_SRC_BITKEG_ENTRY_H_
