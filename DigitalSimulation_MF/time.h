#ifndef TIME_H_
#define TIME_H_

class Time
{
public:
  Time();
  ~Time();

  // const... = 0 -> it's only for definition const variable, it will be changed soon...
  unsigned const _int64 k_max_time_simulation_ = 0;  // max time of simulation

  // get
  inline unsigned _int64 GetActualTimeSimulation() { return actual_time_simulation_; }

  // set
  inline void SetActualTimeSimulation(unsigned _int64 actual_time_simulation)
  {
    this->actual_time_simulation_ = actual_time_simulation;
  }

private:
  unsigned _int64 actual_time_simulation_; // actual time of simulation
};

#endif