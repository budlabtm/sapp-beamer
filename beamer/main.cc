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

  mqtt.Configure(Credentials("localhost", "hfr-v-client", "mxlinux"));
  vcas.Configure(Credentials("localhost", 12345));

  Repo r(&vcas, &mqtt);

  return app.exec();
}