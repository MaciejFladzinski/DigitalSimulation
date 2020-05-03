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
