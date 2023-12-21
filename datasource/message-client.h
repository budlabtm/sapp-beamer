#ifndef SAPP_BEAMER_MESSAGE_CLIENT_H
#define SAPP_BEAMER_MESSAGE_CLIENT_H

#define HOST "localhost"
#define USERNAME "hfr-v-client"
#define PASSWORD "mxlinux"

#include "QtCore/QObject"
#include "mqtt/async_client.h"
#include "record.h"
#include <string>
#include <unordered_set>

namespace budlab::sapp::beamer {

class MessageClient : public QObject, mqtt::callback {
  Q_OBJECT

private:
  std::unique_ptr<mqtt::async_client> client_ = nullptr;

public:
  MessageClient();
  ~MessageClient();

  void Connect();
  void Publish(const Record &record);
  void Subscribe(const std::string &topic);
  void Unsibscribe(const std::string &topic);

  // Callback
  void connected(const std::string &cause) override;
  void connection_lost(const std::string &cause) override;
  void message_arrived(mqtt::const_message_ptr msg) override;

signals:
  void Connected();
  void Disconnected();
  void Consumed(Record record);
};

} // namespace budlab::sapp::beamer

#endif // SAPP_BEAMER_MESSAGE_CLIENT_H