#include "receiver.h"

Receiver::Receiver(unsigned int id_)
{
  receiver_id_ = id_;
}

Receiver::~Receiver()
{
  
}

void Receiver::GenerateACK(Logger* logger)
{
  // Add: generate ACK when package is in vector transmitted
  // if (GetTransmittedPackages()->size() == 1 && package was sent more than CTPk time ago)
  // {
  //  SetSetAcknowledgment(true); // sent ACK for CTIZ (1ms)
  // }
  // else
  // {
  //  SetErrorTransmission(true);
  // }
}
