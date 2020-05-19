#include "transmitter.h"

#include <fstream>
#include <iostream>

Transmitter::Transmitter(unsigned int id_, Logger* logger)
{
  transmitter_id_ = id_;
  logger_ = logger;
  generator_ = new Generators(123 * id_ + 1);
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
  unsigned int R = GetGenerators()->Rand(0, max_value);
  size_t crp_time = ctpk * R * 10;

  SetTimeCrp(crp_time);
  logger->Info("CRP time: " + std::to_string(GetTimeCrp()));
}

void Transmitter::AddPackageSuccessfullySent(Logger* logger)
{
  logger_ = logger;
  ++packages_successfully_sent_;

  double package_error_rate = (double) packages_lost_ / packages_successfully_sent_;

  logger->Info("Packages successfully sent: " + std::to_string(GetPackagesSuccessfullySent()) +
    ", by transmitter: " + std::to_string(GetTransmitterId()));

  logger->Info("Actual package error rate: " + std::to_string(package_error_rate) +
    ", in transmitter: " + std::to_string(GetTransmitterId()));
}

void Transmitter::AddPackageLost(Logger* logger)
{
  logger_ = logger;
  ++packages_lost_;

  double package_error_rate = (double) packages_lost_ / packages_successfully_sent_;

  logger->Info("Packages lost: " + std::to_string(GetPackagesLost()) +
    ", by transmitter: " + std::to_string(GetTransmitterId()));

  logger->Info("Actual package error rate: " + std::to_string(package_error_rate) +
    ", in transmitter: " + std::to_string(GetTransmitterId()));
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

Generators* Transmitter::GetGenerators()
{
  return generator_;
}


void Transmitter::AddPackageInTX(Package* package)
{
  return packages_in_TX_.push(package);
}