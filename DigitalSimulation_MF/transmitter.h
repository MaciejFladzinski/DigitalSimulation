#ifndef TRANSMITTER_H
#define TRANSMITTER_H

class Transmitter
{
public:
  Transmitter(unsigned int id_); //constructor(id number)
  ~Transmitter();

  unsigned int transmitter_id;  // transmitter number
  unsigned _int64 time_of_channel_occupancy_;  // time of channel occupancy
  unsigned _int64 time_of_start_transmission_; // time of start transmission
  unsigned _int64 time_crp;  // random time after which retransmissions can be made
  //unsigned const _int64 time_of_ctiz_;  // ACK transmission time
  bool correct_reception_ack_;  // true - ACK take back in less time than (CGPk + CTIZ)
  bool transmission_permission_;  // true - permission to transmit the packet
  unsigned int packages_successfully_sent_;  // number of packages successfully sent
  unsigned int packages_lost_; // number of packages lost
};

#endif