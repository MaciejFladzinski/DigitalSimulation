#include "channel.h"

Channel::Channel()
{

}

Channel::~Channel()
{
  
}

void Channel::CheckingChannel(Logger* logger)
{
  if (GetChannelOccupancy() == false)
  {
    // Add: checking every 0,5ms (increment checking time by 0,5ms)
    // if (checking time > DIFS (4ms) { return true; }
    // else { checking time = 0; }
  }
}
