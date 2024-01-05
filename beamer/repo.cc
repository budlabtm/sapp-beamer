#include <QtCore/QCoreApplication>
#include <unordered_set>
#include <chrono>

#include "repo.h"

using namespace std;
using namespace std::chrono;
using namespace budlab::msg;
using namespace budlab::beamer;

Repo::Repo(IClient *vcas, IClient *mqtt) {
  mqtt_con_.reset(new Consumer(mqtt));
  vcas_con_.reset(new Consumer(vcas));
  mqtt_prod_.reset(new Producer(mqtt));

  if (db_.contains("cfg"))
    cfg_.ParseFromString(db_.value("cfg").toString().toStdString());
  else
    cfg_.set_source("/budlab/beamer/cfg");

  mqtt_con_->Subscribe(cfg_.source());

  connect(mqtt_con_.get(), SIGNAL(Consumed(Record)), this,
          SLOT(OnConfiguration(Record)));
  connect(vcas_con_.get(), SIGNAL(Consumed(Record)), this,
          SLOT(OnData(Record)));
  connect(&timer_, SIGNAL(timeout()), this, SLOT(OnTimeout()));
  connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(Save()));

  timer_.setInterval(2000);
  timer_.start();
}

void Repo::OnConfiguration(Record record) {
  BeamerConfiguration n;

  if (!n.ParseFromString(record.message)) return;
  if (n.source() != cfg_.source()) {
    mqtt_con_->Unsubscribe(cfg_.source());
    mqtt_con_->Subscribe(n.source());
  }

  unordered_set<string> ex;

  for (auto &frame : n.frames()) {
    bool e = false;

    for (int i = 0; i < cfg_.frames_size() && !e; i++)
      if (cfg_.frames()[i].source() == frame.source()) e = true;

    if (e)
      ex.insert(frame.source());
    else
      vcas_con_->Subscribe(frame.source());
  }

  for (auto &frame : cfg_.frames())
    if (!ex.count(frame.source())) {
      vcas_con_->Unsubscribe(frame.source());
      data_.extract(frame.source());
    }

  cfg_ = n;
}

void Repo::OnData(Record record) {
  data_.insert_or_assign(record.topic, stod(record.message));
}

void Repo::OnTimeout() {
  vector<Frame> frames;

  if (cfg_.frames_size() == 0) return;
  for (auto &frame : cfg_.frames())
    if (data_.count(frame.source()))
      frames.push_back(Frame(data_[frame.source()], &frame));
    else
      return;

  BeamerResult res = fitter_.fit(frames);
  unsigned long time =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();

  mqtt_prod_->Send(Record("/budlab/beamer", res.SerializeAsString(), time));
}

void Repo::Save() {
  db_.setValue("cfg", QString::fromStdString(cfg_.SerializeAsString()));
}