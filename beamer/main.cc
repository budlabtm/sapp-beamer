#include <QtCore/QCoreApplication>
#include "msg/mqtt/mqtt-client.h"
#include "msg/vcas/vcas-client.h"
#include "repo.h"

using namespace budlab::beamer;
using budlab::msg::Credentials;

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  budlab::msg::MqttClient mqtt;
  budlab::msg::VcasClient vcas;

  mqtt.Configure(Credentials("172.16.1.201", "hfr-v-client", "mxlinux"));
  vcas.Configure(Credentials("172.16.1.110", 20041));

  Repo r(&vcas, &mqtt);

  return app.exec();
}