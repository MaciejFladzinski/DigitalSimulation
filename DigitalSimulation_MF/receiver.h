#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "logger.h"

class Receiver
{
public:
  Receiver(unsigned int id_, Logger* logger);
  ~Receiver();

  // get
  inline unsigned int GetReceiverId() { return receiver_id_; }
  inline bool GetErrorTransmission() { return error_transmission_; }
  inline bool GetSendAcknowledgment() { return send_acknowledgment_; }

  // set
  inline void SetReceiverId(unsigned int receiver_id)
  {
    this->receiver_id_ = receiver_id;
  }
  inline void SetErrorTransmission(bool error_transmission)
  {
    this->error_transmission_ = error_transmission;
  }
  inline void SetAcknowledgment(bool send_acknowledgment)
  {
    this->send_acknowledgment_ = send_acknowledgment;
  }

private:
  unsigned int receiver_id_;  // receiver number
  bool error_transmission_ = false;  // true - transmission error occurred (TER)
  bool send_acknowledgment_ = false; // true - permission to send ACK

  Logger* logger_ = nullptr;
};

#endif