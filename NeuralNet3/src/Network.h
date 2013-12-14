/*
 * Network.h
 *
 *  Created on: 01-Dec-2013
 *      Author: xion
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "MathTrainingSet.h"
#include "Layer.h"


class Network {
	int no_of_layers;
	int no_of_inputs;
	int no_of_outputs;
	std::vector<Layer> layers;
	MathTrainingSet trainingset;


public:
	Network(int layerCount, int inputCount, int outputCount, double learningRate, double momentum);
	void train();
};

#endif /* NETWORK_H_ */

