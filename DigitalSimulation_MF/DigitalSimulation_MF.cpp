// DigitalSimulation_MF.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* M4 (Process Interaction)
   A6d (CSMA 1-persistent, DIFS = 4ms)
   10 (K)
   10 (LR) */

#include <iostream>

#include "channel.h"
#include "package.h"
#include "receiver.h"
#include "transmitter.h"
#include "wirelessNetwork.h"

int main()
{
  // start simulation
  std::cout << "Simulation \n";

  // TEST
  WirelessNetwork* wireless_network = new WirelessNetwork();
  Transmitter* transmitter = new Transmitter(5);
  Channel* channel = new Channel();
  Package* package = new Package();
  Receiver* receiver = new Receiver();

  return 0;
}
