#include "channel.h"

Channel::Channel(Logger* logger)
{
  logger_ = logger;
  logger->Info("Create channel");
}

Channel::~Channel()
{
  logger_->Info("Remove channel");
}

bool Channel::GetChannelOccupancy()
{
  return channel_occupancy_;
}

bool Channel::GetCollision()
{
  return packages_collision_;
}

Package* Channel::GetTransmittedPackages(int i)
{
  return transmitted_packages_[i];
}

void Channel::SetChannelOccupancy(bool channel_occupancy)
{
  channel_occupancy_ = channel_occupancy;
}

void Channel::SetCollision(bool collision)
{
  packages_collision_ = collision;
}

void Channel::SetTransmittedPackages(Package* package)
{
  return transmitted_packages_.push_back(package);
}
