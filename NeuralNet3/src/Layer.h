/*
  * Layer.h
 *
 *  Created on: 04-Dec-2013
 *      Author: xion
 */

#ifndef LAYER_H_
#define LAYER_H_



#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include "IOUtils/utils.h"
#include <vector>
#include <string>

#include "Neuron.h"


class Layer {

protected:
	int no_of_inputs;
	int no_of_neurons;

	double learningRate;
	double momentumConstant;

	thrust::device_vector<double> d_inputs;
	thrust::device_vector<double> d_outputs;
	thrust::device_vector<double> d_desired_outputs;
	thrust::device_vector<double> d_dW;

	std::vector<Neuron> neurons;

	void init(int input_size, int output_size);

public:

	Layer();
	Layer(int input_size, int output_size);
	Layer(int input_size, int output_size,double _learningRate,double _momentumConstant);

	virtual void identify();
	void randomizeWeights();

	thrust::host_vector<double> h_inputs;
	thrust::host_vector<double> h_outputs;
	thrust::host_vector<double> h_desired_outputs; //TODO Move these to OutputLayer class
	thrust::host_vector<double> h_dW;


	double getLearningRate() const;
	void setLearningRate(double learningRate);
	double getMomentumConstant() const;
	void setMomentumConstant(double momentumConstant);
	int getNoOfInputs() const;
	int getNoOfNeurons() const;


	virtual void feedForward();
	void propagateOutput(Layer *layer);
	void calculateError();//TODO Move these to OutputLayer class
	void propagateBack(Layer *layer);
	virtual void modifyweights();

	void setInputs(std::vector<double> inputs);
	void setInputs(thrust::host_vector<double> inputs);
	void setDesiredOutputs(std::vector<double> outputs); //TODO Move these to OutputLayer class


	std::vector<double> getDesiredOutputs(); //TODO Move these to OutputLayer class
	std::vector<double> getOutputs();
	std::vector<double> getinputs();
	std::vector<double> getError(); //TODO Move these to OutputLayer class

};

#endif /* LAYER_H_ */
