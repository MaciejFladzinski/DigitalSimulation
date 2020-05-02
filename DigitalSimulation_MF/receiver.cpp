#include "receiver.h"

Receiver::Receiver(unsigned int id_, Logger* logger)
{
  receiver_id_ = id_;
  logger_ = logger;
  logger->Info("Create receiver nr: " + std::to_string(receiver_id_));
}

Receiver::~Receiver()
{
  logger_->Info("Remove receiver nr: " + std::to_string(receiver_id_));
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
