#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "logger.h"
#include "wirelessNetwork.h"
#include "transmitter.h"

class Simulation
{
public:
  Simulation(Logger* logger);
  ~Simulation();
};
#endif