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
#include "IOUtils/utils.h"
#include "Network.h"
#include "IOUtils/CSVWriter.h"


class Network {
	int no_of_layers;
	int no_of_inputs;
	int no_of_outputs;
	std::vector<Layer> layers;
	MathTrainingSet trainingset;


public:
	Network(int layerCount, int inputCount, int outputCount, double learningRate, double momentum);

	void randomizeWeights();

	void train();

	int getNoOfInputs() const ;

	int getNoOfLayers() const ;

	int getNoOfOutputs() const ;

	MathTrainingSet getTrainingset() const ;

	void setTrainingset(MathTrainingSet trainingset) ;
	
};

#endif /* NETWORK_H_ */

