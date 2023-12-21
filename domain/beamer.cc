#include "beamer.h"
#include "QtCore/QDateTime"

using namespace budlab::sapp::beamer;

Beamer::Beamer() {
  timer_.setInterval(2000);

  connect(&client_, SIGNAL(Consumed(Record)), this, SLOT(OnRecord(Record)));
  connect(&timer_, SIGNAL(timeout()), this, SLOT(OnTimeout()));
}

Beamer::~Beamer() {}

void Beamer::start() { client_.Connect(); }

void Beamer::OnClientConnected() { timer_.start(); }

void Beamer::OnClientDisconnected() { timer_.stop(); }

void Beamer::OnRecord(Record record) {
  if (record.topic_ == cfg_.cfg().source())
    return;

  double value = std::stod(record.message_); // Parse logic instead
  current_.insert_or_assign(record.topic_, value);
}

void Beamer::OnTimeout() {
  if (current_.size() < 16)
    return;

  std::vector<FrameData> frames;

  for (auto &frame : cfg_.cfg().frames())
    frames.push_back(FrameData{current_.at(frame.source()), frame});

  BeamerResult result = fit_.fit(frames);
  Record record{cfg_.cfg().output(), result.SerializeAsString(),
                static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch())};
  client_.Publish(record);
}
