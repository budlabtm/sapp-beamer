#ifndef SAPP_BEAMER_MODEL_H
#define SAPP_BEAMER_MODEL_H

#include <string>
#include <vector>

#include "beamer/proto/beamer-cfg.pb.h"

namespace budlab::beamer {

struct FrameData {
  std::string source;
  double value;

  FrameData(std::string source_, double value_)
      : source(source_), value(value_) {}
};

struct Frame {
  double value;
  FrameConfiguration *cfg;

  Frame(double value_, FrameConfiguration *cfg_) : value(value_), cfg(cfg_) {}
};

struct Result {
  double em_h;
  double em_v;
  double dep;

  Reslut(double em_h_, double em_v_, double dep_)
      : em_h(em_h_), em_v(em_v_), dep(dep_) {}
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_MODEL_H