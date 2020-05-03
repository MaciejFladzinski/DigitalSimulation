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

unsigned Transmitter::GetPackagesSuccessfullySent()
{
  return packages_successfully_sent_;
}

void Transmitter::Wait(Logger* logger)
{
  logger_ = logger;
  logger->Info("Waiting 0,5ms...");
}

void Transmitter::CRPTime(Logger* logger)
{
  logger_ = logger;
  logger->Info("CRP time");
}

void Transmitter::AddPackageSuccessfullySent(Logger* logger)
{
  logger_ = logger;
  ++packages_successfully_sent_;
}

void Transmitter::AddPackageLost(Logger* logger)
{
  logger_ = logger;
  ++packages_lost_;
}

void Transmitter::IncTimeOfChannelListenning(Logger* logger)
{
  logger_ = logger;
  time_of_channel_listenning_ += 5;
  logger->Info("Time of free channel listenning: " + std::to_string(time_of_channel_listenning_));
}