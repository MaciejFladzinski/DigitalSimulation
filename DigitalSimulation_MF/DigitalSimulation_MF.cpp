// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <iostream>

#include "packetprocess.h"
#include "logger.h"
#include "wirelessNetwork.h"

int main()
{
  Logger logger = Logger();

  // user will choose the logger type, but for now this option will not be called
  int logger_type = 0;

  while (logger_type == 1 || logger_type == 2 || logger_type == 3)
  {
    printf("Choose: 1. Info, 2. Error, 3. Info & Error");
    std::cin >> logger_type;
    std::cout << std::endl;
  }

  switch(logger_type)
  {
  case 1:
    logger.set_level(Logger::Level::Info);
    break;
  case 2:
    logger.set_level(Logger::Level::Error);
    break;
  case 3:
    logger.set_level(Logger::Level::Debug);
    break;
  }

  // Test 0
  WirelessNetwork* wireles_network = new WirelessNetwork();
  Package* package = new Package(0);

  logger.set_level(Logger::Level::Debug);

  std::vector<PacketProcess*> events;

  events.push_back(new PacketProcess(12, &logger, wireles_network));

  // Test 1
  std::cout << "Test 1: \n";
  try
  {
    events.at(0)->Execute();
  }
  catch (...)
  {
    logger.Error("Index out of bounds");
  }

  // Test 2
  std::cout << "Test 2: \n";
  try
  {
    events.at(1)->Execute();
  }
  catch (...)
  {
    logger.Error("Index out of bounds");
  }

  return 0;
}
