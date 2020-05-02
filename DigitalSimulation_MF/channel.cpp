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

void Channel::SetChannelOccupancy(bool channel_occupancy)
{
  channel_occupancy_ = channel_occupancy;
}

void Channel::SetCollision(bool collision)
{
  packages_collision_ = collision;
}