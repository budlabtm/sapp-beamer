#include "message-client.h"

using namespace mqtt;
using budlab::sapp::beamer::MessageClient;
using std::string;

MessageClient::MessageClient() {
  client_.reset(new async_client{HOST, "beamer"});
  client_->set_callback(*this);
}

MessageClient::~MessageClient() {
  if (client_ != nullptr && client_->is_connected())
    client_->disconnect();
}

void MessageClient::Connect() {
  connect_options opts{USERNAME, PASSWORD};
  opts.set_automatic_reconnect(true);
  client_->connect(opts);
}

void MessageClient::Publish(const Record &record) {
  if (!client_->is_connected())
    return;

  client_->publish(record.topic_,
                   record.message_ + "|" + std::to_string(record.time_));
}

void MessageClient::Subscribe(const std::string &topic) {
  if (!client_->is_connected())
    return;

  client_->subscribe(topic, 2);
}

void MessageClient::Unsibscribe(const std::string &topic) {
  if (!client_->is_connected())
    return;

  client_->unsubscribe(topic);
}

void MessageClient::connected(const std::string &cause) { emit Connected(); }

void MessageClient::connection_lost(const std::string &cause) {
  emit Disconnected();
}

void MessageClient::message_arrived(mqtt::const_message_ptr msg) {
  QList<QString> tokens = QString::fromStdString(msg->get_payload()).split("|");

  emit Consumed(
      Record{msg->get_topic(), tokens[0].toStdString(), tokens[1].toUInt()});
}