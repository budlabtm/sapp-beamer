#ifndef SAPP_BEAMER_CONFIGURATION_REPO_H
#define SAPP_BEAMER_CONFIGURATION_REPO_H

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <vector>

#include "msg/consumer.h"
#include "beamer/proto/beamer-cfg.pb.h"

namespace budlab::beamer {

struct Mod {
  std::string from;
  std::string to;

  Mod(std::string from_, std::string to_) : from(from_), to(to_) {}
};

class ConfigurationRepo : public QObject {
  Q_OBJECT

 private:
  BeamerConfiguration cfg_;
  QSettings local_{"budlab", "beamer"};
  std::unique_ptr<budlab::msg::Consumer> consumer_;

 public:
  ConfigurationRepo(budlab::msg::IClient *mqtt_client);
  virtual ~ConfigurationRepo() {}

  const BeamerConfiguration &Get();

 signals:
  void SourcesChanged(const std::vector<Mod> &mods);
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_CONFIGURATION_REPO_H