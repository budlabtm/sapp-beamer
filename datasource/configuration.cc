#include "configuration.h"

using namespace budlab::sapp::beamer;

Configuration::Configuration(MessageClient *client) {
  client_.reset(client);

  connect(client, SIGNAL(Connected()), this, SLOT(OnClientConnected()));
  connect(client, SIGNAL(Consumed(Record)), this, SLOT(OnRecord(Record)));

  if (settings_.contains("configuration"))
    cfg_.ParseFromString(
        settings_.value(QString::fromStdString("configuration"))
            .toString()
            .toStdString());
  else
    cfg_.set_source("/budlab/cfg/beamer");
}

Configuration::~Configuration() {
  settings_.setValue("configuration",
                     QString::fromStdString(cfg_.SerializeAsString()));
}

void Configuration::OnClientConnected() {
  client_->Subscribe(cfg_.source());

  for (auto &frame : cfg_.frames())
    client_->Subscribe(frame.source());
}

void Configuration::OnRecord(Record record) {
  if (record.topic_ != cfg_.source())
    return;

  BeamerConfiguration old = cfg_;

  cfg_.ParseFromString(record.message_);

  if (old.source() != cfg_.source()) {
    client_->Unsibscribe(old.source());
    client_->Subscribe(cfg_.source());
  }

  for (decltype(cfg_.frames().size()) i = 0; i < cfg_.frames().size(); i++)
    if (cfg_.frames()[i].source() != old.frames()[i].source()) {
      client_->Unsibscribe(old.frames()[i].source());
      client_->Subscribe(cfg_.frames()[i].source());
    }
}