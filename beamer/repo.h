#ifndef SAPP_BEAMER_REPO_H
#define SAPP_BEAMER_REPO_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QSettings>
#include <unordered_map>
#include <string>

#include "fitter.h"
#include "beamer/proto/beamer-cfg.pb.h"
#include "msg/consumer.h"
#include "msg/producer.h"

using budlab::msg::Record;

namespace budlab::beamer {

class Repo : public QObject {
  Q_OBJECT

 private:
  Fitter fitter_;
  BeamerConfiguration cfg_;
  QTimer timer_;
  QSettings db_{"budlab", "beamer"};

  std::unique_ptr<budlab::msg::Consumer> mqtt_con_;
  std::unique_ptr<budlab::msg::Consumer> vcas_con_;
  std::unique_ptr<budlab::msg::Producer> mqtt_prod_;

  std::unordered_map<std::string, double> data_;

 public slots:
  void OnConfiguration(Record record);
  void OnData(Record record);
  void OnTimeout();
  void Save();

 public:
  Repo(budlab::msg::IClient *vcas, budlab::msg::IClient *mqtt);
  virtual ~Repo() {}
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_REPO_H