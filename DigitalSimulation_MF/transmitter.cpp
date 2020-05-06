#include "transmitter.h"

#include <iostream>

Transmitter::Transmitter(unsigned int id_, Logger* logger)
{
  transmitter_id_ = id_;
  logger_ = logger;
  logger->Info("Create transmitter nr: " + std::to_string(id_));
}

Transmitter::~Transmitter()
{
  logger_->Info("Remove transmitter nr: " + std::to_string(transmitter_id_));
}

unsigned int Transmitter::GetPackagesSuccessfullySent()
{
  return packages_successfully_sent_;
}

unsigned int Transmitter::GetPackagesLost()
{
  return packages_lost_;
}


void Transmitter::GenerateCRPTime(Logger* logger, size_t ctpk, unsigned int number_of_LR)
{
  logger_ = logger;

  unsigned int max_value = std::pow(2, number_of_LR);
  unsigned int R = rand() % max_value;
  size_t crp_time = ctpk * R * 10;

  SetTimeCrp(crp_time);
  logger->Info("CRP time: " + std::to_string(GetTimeCrp()));
}

void Transmitter::AddPackageSuccessfullySent(Logger* logger)
{
  logger_ = logger;
  ++packages_successfully_sent_;
  logger->Info("Packages successfully sent: " + std::to_string(GetPackagesSuccessfullySent()));
}

void Transmitter::AddPackageLost(Logger* logger)
{
  logger_ = logger;
  ++packages_lost_;
  logger->Info("Packages lost: " + std::to_string(GetPackagesLost()));
}

void Transmitter::IncTimeOfChannelListenning(Logger* logger)
{
  logger_ = logger;
  this->time_of_channel_listenning_ += 5;
  logger->Info("Time of free channel listenning: " +
    std::to_string(time_of_channel_listenning_ - 5) + ", by transmitter: " +
    std::to_string(GetTransmitterId()));
}

Package* Transmitter::GetFirstPackageInTX()
{
  return packages_in_TX_.front();
}

void Transmitter::AddPackageInTX(Package* package)
{
  return packages_in_TX_.push(package);
}
