// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>

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
  std::ofstream saveAverageOfLRInSystem("SaveAverageOfLRInSystem.txt");


  int wireless_network_seed = 123;

  Logger* logger = new Logger();
  logger->set_level();

  printf("Set max simulation time:\n");
  size_t max_simulation_time;
  std::cin >> max_simulation_time;
  printf("\n");

  printf("Choose a set of seeds from 1-10:\n");
  int seed_key;
  std::cin >> seed_key;

  switch (seed_key)
  {
  case 1:
    break;
  case 2:
    wireless_network_seed += 10;
    break;
  case 3:
    wireless_network_seed += 20;
    break;
  case 4:
    wireless_network_seed += 30;
    break;
  case 5:
    wireless_network_seed += 40;
    break;
  case 6:
    wireless_network_seed += 50;
    break;
  case 7:
    wireless_network_seed += 60;
    break;
  case 8:
    wireless_network_seed += 70;
    break;
  case 9:
    wireless_network_seed += 80;
    break;
  case 10:
    wireless_network_seed += 90;
    break;
  default:
    printf("Wrong number! Seed was choosed automaticly.\n");
  }
  printf("\n");

  WirelessNetwork* wireless_network = new WirelessNetwork(logger, wireless_network_seed);

  auto simulation = new Simulation(logger, wireless_network);

  simulation->RunM4(logger, max_simulation_time);

  wireless_network->TransmittersStatistic(logger);
  wireless_network->TotalStatistics(logger);

  printf("\n\n");
  delete simulation;
  delete wireless_network;
  delete logger;

  return 0;
}