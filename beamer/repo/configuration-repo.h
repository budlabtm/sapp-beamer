#ifndef SAPP_BEAMER_CONFIGURATION_REPO_H
#define SAPP_BEAMER_CONFIGURATION_REPO_H

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <vector>
#include <string>

#include "msg/consumer.h"
#include "beamer/proto/beamer-cfg.pb.h"

namespace budlab::beamer {

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
  void Terminate();

 signals:
  void SourcesChanged(const std::vector<std::string> &o,
                      const std::vector<std::string> &n);

 private slots:
  void OnConsumed(budlab::msg::Record record);
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_CONFIGURATION_REPO_H