#ifndef BUFFER_H_
#define BUFFER_H_

#include <queue>

#include "package.h"

class Buffer
{
public:
  Buffer(unsigned int id_); // constructor (transmitter id)
  ~Buffer();

  // get
  inline unsigned int GetTransmitterId() { return transmitter_id_; }

  // set
  inline void SetTransmitterId(unsigned int transmitter_id) { this->transmitter_id_ = transmitter_id; }

private:
  unsigned int transmitter_id_; // number of transmitter to which buffer belongs

  std::queue<Package*> packages_in_buffer; // queue of packages in buffer
};

#endif