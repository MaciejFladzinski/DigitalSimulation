#ifndef RECEIVER_H
#define RECEIVER_H

class Receiver
{
public:
  Receiver();
  ~Receiver();

  bool error_transmission_;  // true - transmission error occurred (TER)
  bool send_acknowledgment_; // true - permission to send ACK
};

#endif