#ifndef RECEIVER_H_
#define RECEIVER_H_

class Receiver
{
public:
  Receiver();
  ~Receiver();

  // get
  inline bool GetErrorTransmission() { return error_transmission_; }
  inline bool GetSendAcknowledgment() { return send_acknowledgment_; }
  // set
  inline void SetErrorTransmission(bool error_transmission)
  { this->error_transmission_ = error_transmission; }
  inline void SetSetAcknowledgment(bool send_acknowledgment)
  { this->send_acknowledgment_ = send_acknowledgment; }

private:
  bool error_transmission_;  // true - transmission error occurred (TER)
  bool send_acknowledgment_; // true - permission to send ACK
};

#endif