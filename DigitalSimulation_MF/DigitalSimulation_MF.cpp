// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <iostream>

#include "packetprocess.h"
#include "logger.h"
#include "process.h"
#include "wirelessNetwork.h"

int main()
{
  Logger logger = Logger();
  logger.set_level(Logger::Level::Debug);

  std::vector<Process*> events;

  events.push_back(new PacketProcess(5, &logger));

  std::cout << "Test 1: \n";
  try
  {
    events.at(0)->Execute();
  }
  catch (...)
  {
    logger.Error("Index out of bounds");
  }

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
