#ifndef SAPP_BEAMER_FRAME_H
#define SAPP_BEAMER_FRAME_H

#include "beamer/proto/beamer-cfg.pb.h"

namespace budlab::beamer {

struct Frame {
  double value;
  FrameConfiguration *cfg;
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_FRAME_H