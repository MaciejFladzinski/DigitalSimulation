// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <ctime>
#include <ostream>


#include "logger.h"
#include "simulation.h"
#include "wirelessNetwork.h"

int main()
{
  // generate random value in simulation by function "rand()"
  std::srand(time(NULL));

  Logger* logger = new Logger();
  logger->set_level();

  WirelessNetwork* wireless_network = new WirelessNetwork(logger);

  auto simulation = new Simulation(logger, wireless_network);

  simulation->RunM4(logger, 2000);

  printf("\n");
  delete simulation;
  delete wireless_network;
  delete logger;
  return 0;
}
