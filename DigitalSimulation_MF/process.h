#ifndef PROCESS_H_
#define PROCESS_H_

class Process
{
public:
  Process(size_t time);
  ~Process();

  virtual void Execute() = 0; // process activation
  
  // enum class (representation of states)
  
  void Activ(size_t time); //function (process activation time)

protected:
  bool is_terminated_ = false;
  size_t time_ = 0; //time after which the process will start
};

#endif
