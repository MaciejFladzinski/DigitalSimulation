#ifndef PACKAGE_H_
#define PACKAGE_H_

class Package
{
public:
  Package(unsigned __int64 time_);
  ~Package();

  // get
  inline unsigned int GetNumberOfLR() { return number_of_LR_; }
  inline unsigned int GetTimeCTPk() { return time_ctpk_; }

  // set
  inline void SetNumberOfLR(unsigned int number_of_LR) { this->number_of_LR_ = number_of_LR; }
  inline void SetTimeCTPk(unsigned int time_ctpk) { this->time_ctpk_ = time_ctpk; }

private:
  unsigned int number_of_LR_; // packet retransmission number
  unsigned __int64 time_ctpk_; // random packet generation time (CTPk)
};
#endif