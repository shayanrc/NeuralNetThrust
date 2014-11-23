/*
 * Network.h
 *
 *  Created on: 01-Dec-2013
 *      Author: xion
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "TrainingSet.h"
#include "StockDataTrainingSet.h"
#include "Layer.h"
#include "IOUtils/utils.h"
#include "IOUtils/CSVWriter.h"
#include <memory>

class Network {

private:
	int no_of_layers;
	int no_of_inputs;
	int no_of_outputs;
	std::vector<Layer * > layers;
	//StockDataTrainingSet *trainingset; //TODO declared as base class pointer, so that any derived class can be used instead
	TrainingSet *trainingset;

public:
	Network(int layerCount, int inputCount, int outputCount,
				double learningRate, double momentum, TrainingSet *trainingSet);
	//Network(int layerCount, int inputCount, int outputCount,double learningRate, double momentum, StockDataTrainingSet *trainingSet);

	void randomizeWeights();

	void train();

	int getNoOfInputs() const;

	int getNoOfLayers() const;

	int getNoOfOutputs() const;

	void insertLayer(Layer *layer, int index);

	bool nextInput();
	//MathTrainingSet getTrainingset() const ;

	void setTrainingset(StockDataTrainingSet *trainingset);
	void setTrainingset(TrainingSet *trainingset);

};

#endif /* NETWORK_H_ */

