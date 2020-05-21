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

  void RunM4(Logger* logger, int time);

  void StepInto();
  bool SelectMode(int mode);

  size_t GetStartTimeStatistics();
  void SetStartTimeStatistics(size_t initial_phase);

private:
  size_t clock_ = 0;
  size_t start_time_statistics_ = 0;

  Generators* generators_ = nullptr;
  WirelessNetwork* wireless_network_ = nullptr;
  Logger* logger_ = nullptr;
};
#endif