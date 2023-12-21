#ifndef SAPP_BEAMER_H
#define SAPP_BEAMER_H

#include "QtCore/QObject"
#include "QtCore/QTimer"
#include "core/core.h"
#include "datasource/configuration.h"
#include "datasource/message-client.h"
#include <unordered_map>

namespace budlab::sapp::beamer {

class Beamer : public QObject {
  Q_OBJECT

private:
  std::unordered_map<std::string, double> current_;

  Fit fit_;
  MessageClient client_;
  Configuration cfg_{&client_};
  QTimer timer_;

public:
  Beamer();
  ~Beamer();

  void start();

public slots:
  void OnClientConnected();
  void OnClientDisconnected();
  void OnRecord(Record record);
  void OnTimeout();
};

} // namespace budlab::sapp::beamer

#endif // SAPP_BEAMER_H