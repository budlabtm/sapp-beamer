#ifndef SAPP_BEAMER_SWITCH_H
#define SAPP_BEAMER_SWITCH_H

#include <QtCore/QObject>

#include "msg/producer.h"

namespace budlab::beamer {

struct Result {
  double em_h;
  double em_v;
  double dep;

  Result(double em_h_, double em_v_, double dep_)
      : em_h(em_h_), em_v(em_v_), dep(dep_) {}
};

class Switch : public QObject {
  Q_OBJECT

 private:
  std::unique_ptr<budlab::msg::Producer> vcas_prod_;
  std::unique_ptr<budlab::msg::Producer> mqtt_prod_;

 public:
  Switch(budlab::msg::IClient *vcas_client, budlab::msg::IClient *mqtt_client);
  virtual ~Switch() {}

 public slots:
  void OnResult(const Result &result);
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_SWITCH_H