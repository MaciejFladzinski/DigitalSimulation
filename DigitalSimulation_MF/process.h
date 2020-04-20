#ifndef PROCESS_H_
#define PROCESS_H_

#include <vector>

class Process;

class Event
{
public:
  double schedule_time_;
  Process* packet_process_ptr_;
  Event(Process* ptr) : schedule_time_(-1.0), packet_process_ptr_(ptr) {}
};

class Process
{
public:
  Process(std::vector<Event*>* events_ptr, size_t* clock)
    : phase_(0), is_terminated_(false), events_(events_ptr), clock_(clock)
  {
    event_ = new Event(this);
  }

  ~Process()
  {
    events_ = NULL;
    clock_ = NULL;
    delete event_;
  }

  // functions
  virtual void Execute() {};

  void Activ(size_t time) //function (process activation time)
  {
    event_->schedule_time_ = (*clock_) + time;
  }

  double time()
  {
    return event_->schedule_time_;
  }

  //get
  std::vector<Event*> GetEvents() { return *events_; }
  inline int GetPhase() { return phase_; }
  inline size_t GetClock() { return *clock_; }

  //set
  void SetEvents(std::vector<Event*>* events) { events_ = events; }
  void SetPhase(unsigned int phase) { phase_ = phase; }
  void SetClock(size_t *clock) { *clock_ = *clock; }

protected:
  bool is_terminated_;

private:
  std::vector<Event*>* events_;
  unsigned int phase_;
  size_t* clock_;
  Event* event_;
};
#endif