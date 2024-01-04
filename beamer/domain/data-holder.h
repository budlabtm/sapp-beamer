#ifndef SAPP_BEAMER_DATA_HOLDER_H
#define SAPP_BEAMER_DATA_HOLDER_H

#include "beamer/proto/beamer-cfg.pb.h"

namespace budlab::beamer {

struct Frame {
  double value;
  FrameConfiguration *cfg;

  Frame(double value_, FrameConfiguration *cfg_) : value(value_), cfg(cfg_) {}
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_DATA_HOLDER_H