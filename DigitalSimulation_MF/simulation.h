#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "logger.h"
#include "wirelessNetwork.h"

class WirelessNetwork;
class Transmitter;

class Simulation
{
public:
  Simulation(Logger* logger, WirelessNetwork* wireless_network);
  ~Simulation();

  void RunM4(Logger* logger, size_t time);

private:
  size_t generate_packet_max_time_ = 10;
  size_t clock_ = 0;

  WirelessNetwork* wireless_network_ = nullptr;
  Logger* logger_ = nullptr;
};
#endif