#ifndef TIME_H_
#define TIME_H_

class Time
{
public:
  Time();
  ~Time();

  // const... = 0 -> it's only for definition const variable, it will be changed soon...
  const size_t k_max_time_simulation_ = 0;  // max time of simulation

  // get
  inline size_t GetActualTimeSimulation() { return actual_time_simulation_; }

  // set
  inline void SetActualTimeSimulation(unsigned __int64 actual_time_simulation)
  {
    this->actual_time_simulation_ = actual_time_simulation;
  }

private:
  size_t actual_time_simulation_; // actual time of simulation
};

#endif