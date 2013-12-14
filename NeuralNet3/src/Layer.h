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
#include <vector>
#include "Neuron.h"

class Layer {
	int no_of_inputs;
	int no_of_neurons;

	double learningRate;
	double momentumConstant;

	thrust::device_vector<double> d_inputs;
	thrust::device_vector<double> d_weights;
	thrust::device_vector<double> d_outputs;
	thrust::device_vector<double> d_desired_outputs;
	thrust::device_vector<double> d_dW;

	std::vector<Neuron> neurons;
public:
	Layer(int input_size, int output_size);
	Layer(int input_size, int output_size,double _learningRate,double _momentumConstant);

	thrust::host_vector<double> h_inputs;
	thrust::host_vector<double> h_weights;
	thrust::host_vector<double> h_outputs;
	thrust::host_vector<double> h_desired_outputs;
	thrust::host_vector<double> h_dW;


	double getLearningRate() const;
	void setLearningRate(double learningRate);
	double getMomentumConstant() const;
	void setMomentumConstant(double momentumConstant);
	int getNoOfInputs() const;
	int getNoOfNeurons() const;


	void feedForward();
	void calculateError();
	void propagateBack(thrust::device_vector<double>);
	void modifyweights();
};

#endif /* LAYER_H_ */
