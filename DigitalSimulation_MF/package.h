#ifndef PACKAGE_H
#define PACKAGE_H

class Package
{
public:
  Package();
  ~Package();

  //unsigned const _int64 k_time_ctpk_; // random packet generation time (CTPk)
  unsigned int number_of_LR_; // packet retransmission number
};

#endif