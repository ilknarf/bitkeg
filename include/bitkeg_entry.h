#ifndef BITKEG_SRC_BITKEG_ENTRY_H_
#define BITKEG_SRC_BITKEG_ENTRY_H_

#include <string>
#include <shared_mutex>

#include "keydir.h"

struct BitkegEntry {
  friend class KeyDir;
 protected:
  std::string file_id;
  int value_sz;
  long value_pos;
  time_t t_stamp;
};

#endif //BITKEG_SRC_BITKEG_ENTRY_H_
