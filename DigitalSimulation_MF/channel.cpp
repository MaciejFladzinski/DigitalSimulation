#include "channel.h"

Channel::Channel(Logger* logger, int uniform_seed)
{
  logger_ = logger;
  uniform_generator_ = new Generators(uniform_seed);

  logger->Info("Create channel");
}

Channel::~Channel()
{
  logger_->Info("Remove channel");
}

Generators* Channel::GetGeneratorTER()
{
  return uniform_generator_;
}

bool Channel::GetChannelOccupancy()
{
  return channel_occupancy_;
}

bool Channel::GetCollision()
{
  return packages_collision_;
}

bool Channel::GetMorePackagesInChannel()
{
  return more_packages_in_channel_;
}

void Channel::SetChannelOccupancy(bool channel_occupancy)
{
  channel_occupancy_ = channel_occupancy;
}

void Channel::SetCollision(bool collision)
{
  packages_collision_ = collision;
}

void Channel::SetMorePackagesInBuffer(bool more_packages_in_channel)
{
  more_packages_in_channel_ = more_packages_in_channel;
}


void Channel::ChanceForTER(Logger* logger)
{
  logger_ = logger;
  int random_number = GetGeneratorTER()->RandZeroOne(0.7);

  if (random_number == 0)
  {
    SetCollision(true);
    logger->Info("TER error occur");
  }
  else
  {
    logger->Info("TER error doesn't occur");
  }
}