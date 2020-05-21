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

  /*
  int number_of_rands = 100000;

  // Create random generator with arbitrary seed
  int seed = 50;
  auto uniform_generator = Generators(seed);
  std::vector<double> numbers;

  for (int i = 0; i < number_of_rands; ++i)
  {
    numbers.push_back(uniform_generator.Rand());
  }

  // Save data to file
  std::ofstream output_file("./example.txt");
  std::ostream_iterator<double> output_iterator(output_file, "\n");
  std::copy(numbers.begin(), numbers.end(), output_iterator);
  */

  int wireless_network_seed = 123;

  Logger* logger = new Logger();
  logger->set_level();

  printf("Set max simulation time:\n");
  size_t max_simulation_time;
  std::cin >> max_simulation_time;
  printf("\n");

  WirelessNetwork* wireless_network = new WirelessNetwork(logger, wireless_network_seed);

  auto simulation = new Simulation(logger, wireless_network);

  simulation->RunM4(logger, max_simulation_time);

  wireless_network->TotalStatistics(logger);

  printf("\n");
  delete simulation;
  delete wireless_network;
  delete logger;
  return 0;
}