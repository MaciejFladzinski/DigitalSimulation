// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <iostream>

#include "logger.h"
#include "simulation.h"
#include "wirelessNetwork.h"

int main()
{
  Logger* logger = new Logger();
  logger->set_level();

  auto simulation = new Simulation(logger);

  delete simulation;
  delete logger;
  return 0;
}
