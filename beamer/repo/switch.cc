#include <chrono>
#include "beamer/repo/switch.h"
#include "beamer/proto/beamer-res.pb.h"

using namespace std;
using namespace std::chrono;
using namespace budlab::beamer;
using namespace budlab::msg;

Switch::Switch(IClient *vcas_client, IClient *mqtt_client) {
  vcas_prod_.reset(new Producer(vcas_client));
  mqtt_prod_.reset(new Producer(mqtt_client));
}

void Switch::OnResult(const Result &result) {
  BeamerResult r;

  r.set_em_h(result.em_h);
  r.set_em_v(result.em_v);
  r.set_dep(result.dep);

  unsigned long time =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();

  mqtt_prod_->Send(
      Record("/budlab/beamer/result", r.SerializeAsString(), time));
}
