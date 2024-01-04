#include "beamer/repo/data-repo.h"

using namespace std;
using namespace budlab::beamer;
using namespace budlab::msg;

DataRepo::DataRepo(IClient *vcas_client, ConfigurationRepo *cfg_repo) {
  consumer_.reset(new Consumer(vcas_client));

  connect(cfg_repo, SIGNAL(SourcesChanged(const vector<Mod> &)), this,
          SLOT(OnSourcesChanged(const vector<Mod> &)));
  connect(consumer_.get(), SIGNAL(Consumed(Record)), this,
          SLOT(OnConsumed(Record)));

  for (auto &frame : cfg_repo->Get().frames())
    consumer_->Subscribe(frame.data_source());
}

void DataRepo::OnConsumed(budlab::msg::Record record) {
  emit Consumed(FrameData(record.topic, std::stod(record.message)));
}

void DataRepo::OnSourcesChanged(const std::vector<std::string> &o,
                                const std::vector<std::string> &n) {
  for (auto &t : o) consumer_->Unsubscribe(t);
  for (auto &t : n) consumer_->Subscribe(t);
}