#include "wirelessNetwork.h"

#include <iostream>

#include "transmitter.h"
#include "receiver.h"
#include "channel.h"
#include "time.h"

WirelessNetwork::WirelessNetwork()
{
	printf("Creating a new wireless network...\n");
	auto time = new Time();

	for (int i = 0; i < k_number_of_stations_; i++)
	{
		auto transmitter = new Transmitter(i);
		transmitters_.push_back(transmitter);
		std::cout << "Create transmitter nr: " << i+1 << std::endl;

		auto receiver = new Receiver(i);
		receivers_.push_back(receiver);
		std::cout << "Create receiver nr: " << i+1 << std::endl;
	}
	auto channel = new Channel();
	std::cout << "Create channel nr: 1 \n\n";
}

WirelessNetwork::~WirelessNetwork()
{
  
}
