#ifndef SAPP_BEAMER_CONFIGURATION_H
#define SAPP_BEAMER_CONFIGURATION_H

#include "QtCore/QObject"
#include "QtCore/QSettings"
#include "message-client.h"
#include "proto/beamer-cfg.pb.h"
#include "record.h"

namespace budlab::sapp::beamer {

class Configuration : public QObject {
  Q_OBJECT

private:
  BeamerConfiguration cfg_;
  QSettings settings_{"budlab", "beamer"};
  std::shared_ptr<MessageClient> client_;

public:
  Configuration(MessageClient *client);
  ~Configuration();

  const BeamerConfiguration &cfg() { return cfg_; }

public slots:
  void OnClientConnected();
  void OnRecord(Record record);
};

} // namespace budlab::sapp::beamer

#endif // SAPP_BEAMER_CONFIGURATION_H