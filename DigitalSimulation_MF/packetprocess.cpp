#include "packetprocess.h"

void PacketProcess::Execute()
{
  bool active = true;

  while(active)
  {
    switch(state_)
    {
      // before all break: set active = true/false + Activ(time) if it's required
    case State::Begin:
      // Begin operations
      break;

    case State::Medium:
      // Medium operations
      break;

    case State::End:
      // End operations
      break;

    default:
      // assert or exeption (error)
      break;
    }
  }
}
