#ifndef SAPP_BEAMER_DATA_REPO_H
#define SAPP_BEAMER_DATA_REPO_H

#include <QtCore/QObject>

#include "msg/consumer.h"
#include "beamer/repo/configuration-repo.h"

namespace budlab::beamer {

struct FrameData {
  std::string source;
  double value;

  FrameData(std::string source_, double value_)
      : source(source_), value(value_) {}
};

class DataRepo : public QObject {
  Q_OBJECT

 private:
  std::unique_ptr<budlab::msg::Consumer> consumer_;

 public:
  DataRepo(budlab::msg::IClient *vcas_client, ConfigurationRepo *cfg_repo);
  virtual ~DataRepo() {}

 signals:
  void Consumed(const FrameData &data);

 private slots:
  void OnConsumed(budlab::msg::Record record);
  void OnSourcesChanged(const std::vector<std::string> &o,
                        const std::vector<std::string> &n);
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_DATA_REPO_H