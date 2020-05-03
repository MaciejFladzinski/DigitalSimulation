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

void Channel::ChanceForTER(Logger* logger)
{
  logger_ = logger;
  int random_number = rand() % 5 + 1;

  // 5 numbers (draw "1": success, draw other number: TER error)
  if (random_number == 1)
  {
    logger->Info("TER error doesn't occur");
  }
  else
  {
    SetCollision(true);
    logger->Info("TER error occur");
  }
}
