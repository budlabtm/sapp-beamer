#include "beamer/repo/configuration-repo.h"

using namespace std;
using namespace budlab::beamer;
using namespace budlab::msg;

ConfigurationRepo::ConfigurationRepo(IClient *mqtt_client) {
  consumer_.reset(new Consumer(mqtt_client));

  connect(consumer_.get(), SIGNAL(Consumed(Record)), this,
          SLOT(OnConsumed(Record)));

  if (local_.contains("cfg"))
    cfg_.ParseFromString(local_.value("cfg").toString().toStdString());
  else
    cfg_.set_cfg_source("/budlab/cfg/beamer");

  consumer_->Subscribe(cfg_.cfg_source());
}

const BeamerConfiguration &ConfigurationRepo::Get() { return cfg_; }

void ConfigurationRepo::Terminate() {
  local_.setValue("cfg", QString::fromStdString(cfg_.SerializeAsString()));
}

void ConfigurationRepo::OnConsumed(budlab::msg::Record record) {
  vector<string> o;
  vector<string> n;
  string cfgs = cfg_.cfg_source();

  for (auto &frame : cfg_.frames()) o.push_back(frame.data_source());
  if (!cfg_.ParseFromString(record.message)) return;
  for (auto &frame : cfg_.frames()) n.push_back(frame.data_source());

  consumer_->Unsubscribe(cfgs);
  consumer_->Subscribe(cfg_.cfg_source());

  emit SourcesChanged(o, n);
}