// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <iostream>

#include "channel.h"
#include "package.h"
#include "wirelessNetwork.h"

int main()
{
  // start simulation
  std::cout << "Simulation \n";

  // TEST
  WirelessNetwork* wireless_network = new WirelessNetwork();
  Channel* channel = new Channel();
  Package* package = new Package();

  return 0;
}
