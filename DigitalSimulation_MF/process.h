#ifndef PROCESS_H_
#define PROCESS_H_

class Process
{
public:
  explicit Process(size_t time);
  ~Process();

  virtual void Execute() {} // process activation
  
  // enum class (representation of states)
  
  void Activ(unsigned __int64 activ_time_) {} //function (process activation time)

protected:
  size_t time_ = 0; //time after which the process will start
};

#endif
