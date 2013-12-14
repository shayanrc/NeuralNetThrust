/*
 * Network.cpp
 *
 *  Created on: 11-Dec-2013
 *      Author: xion
 */

#include "Network.h"


//Remove training set initialization from here -> Need a better approach
Network::Network(int layerCount, int inputCount, int outputCount, double learningRate, double momentum)
:trainingset(100)
{

layers=std::vector<Layer>(layerCount,Layer(inputCount,outputCount,learningRate,momentum));

}



