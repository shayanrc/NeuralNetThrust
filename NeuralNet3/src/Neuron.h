/*
 * Neuron.h
 *
 *  Created on: 01-Dec-2013
 *      Author: xion
 */

#ifndef NEURON_H_
#define NEURON_H_


#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <ctime>




	class Neuron {

	protected:
		int inputCount;

	public:
		thrust::device_vector<double> d_weightVector;
		thrust::host_vector<double> h_weightVector;
		thrust::device_vector<double> d_momentum;
		thrust::host_vector<double> h_momentum;
		Neuron(int no_of_inputs);

		void randomizeWeights();
		int getInputCount();
		virtual ~Neuron();
	};

#endif /* NEURON_H_ */
