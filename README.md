# Digital Simulation

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info
The application is a simulation of a wireless network using the method of process interaction. The network operates according to the CSMA (Carrier Sense Multiple Access) protocol with forcing transmission with a probability of 1. In the application, random values are generated using pseudorandom generators. The created network simulation is an example of a stable network with an acceptable average error rate of 5-8%. 

There is one elaborate process in the simulation: Package.
Process phases:
* appearance in the system,
* listening to the channel,
* transmission,
* collision,
* receiving the package,
* retransmission,
* permission to send ACK confirmation,
* acknowledgment of ACK,
* removal from the system. 

## Technologies
* C++.

## Setup
Program calling parameters:
* selection of displayed information (debug, info, error).
* selection of simulation debugging (stepwise, continuously).
* setting the maximum simulation time (1 time unit corresponds to 0.1 ms).
* setting the end of the initial phase depending on the number of packets sent and lost in system.

Fixed parameters (modifiable in the code):
* TER = 30% - chance for an error during packet transmission,
* Lambda parameter - the intensity determining the random CGPk time with the exponential distribution. 
