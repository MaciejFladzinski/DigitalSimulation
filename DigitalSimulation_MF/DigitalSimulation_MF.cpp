// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <ctime>
#include <fstream>

#include "logger.h"
#include "simulation.h"
#include "wirelessNetwork.h"

int main()
{
  // open file: partial data
  std::ofstream saveTimeOfAddedToBuffer("SaveTimeOfAddedToBuffer.txt"); // save time of added package to the buffer
  std::ofstream saveTimeSuccessfullySentPackage("SaveTimeSuccessfullySentPackage.txt"); // save time when package is successfully sent
  std::ofstream saveTimeRemoveFromBuffer("SaveTimeRemoveFromBuffer.txt"); // save time when package is remove from buffer

  // open file: most important files
  std::ofstream savePackagesSent("SavePackagesSent.txt"); // save packages successfully sent and packages lost
  std::ofstream saveNumberOfLR("SaveNumberOfLR.txt"); // save number of LR
  std::ofstream savePackageDelayTime("SavePackageDelayTime.txt"); // save package delay time (TimeSuccessfullySentPackage - TimeOfAddedToBuffer)
  std::ofstream saveWaitingTime("SaveWaitingTime.txt"); // save waiting time (TimeRemoveFromBuffer - TimeOfAddedToBuffer)
  std::ofstream saveSystemThroughput("SaveSystemThroughput.txt"); // save: packages successfully sent / simulation time
  
  // generate random value in simulation by function "rand()"
  std::srand(time(NULL));

  Logger* logger = new Logger();
  logger->set_level();

  WirelessNetwork* wireless_network = new WirelessNetwork(logger);

  auto simulation = new Simulation(logger, wireless_network);

  simulation->RunM4(logger, 1000);

  printf("\n");
  delete simulation;
  delete wireless_network;
  delete logger;
  return 0;
}
