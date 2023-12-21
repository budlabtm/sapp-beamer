#ifndef SAPP_BEAMER_RECORD_H
#define SAPP_BEAMER_RECORD_H

#include <string>

namespace budlab::sapp::beamer {

struct Record {
  std::string topic_;
  std::string message_;
  unsigned time_ = 0;

  Record(std::string topic, std::string message, unsigned time = 0)
      : topic_(std::move(topic)), message_(std::move(message)), time_(time) {}
};

} // namespace budlab::sapp::beamer

#endif // SAPP_BEAMER_RECORD_H