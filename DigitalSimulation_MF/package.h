#ifndef PACKAGE_H_
#define PACKAGE_H_

class Package
{
public:
  Package();
  ~Package();

  // const... = 0 -> it's only for definition const variable, it will be changed soon...
  unsigned const __int64 k_time_ctpk_ = 0; // random packet generation time (CTPk)

  // get
  inline unsigned int GetNumberOfLR() { return number_of_LR_; }

  // set
  inline void SetNumberOfLR(unsigned int number_of_LR) { this->number_of_LR_ = number_of_LR; }

private:
  unsigned int number_of_LR_; // packet retransmission number
};

#endif