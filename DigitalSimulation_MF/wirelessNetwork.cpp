#include "wirelessNetwork.h"

#include <iostream>


#include "transmitter.h"
#include "receiver.h"
#include "channel.h"

WirelessNetwork::WirelessNetwork()
{
	for (int i = 0; i < k_number_of_stations_; i++)
	{
		transmitters_->push_back(new Transmitter(i));
		std::cout << "Stworzono nadajnik nr: " + i << std::endl;

		receivers_->push_back(new Receiver(i));
		std::cout << "Stworzono odbiornik nr: " + i << std::endl;

	}
	auto channel = new Channel();
}

WirelessNetwork::~WirelessNetwork()
{
  
}
