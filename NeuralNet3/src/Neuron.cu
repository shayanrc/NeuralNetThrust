/*
 * Neuron.cpp
 *
 *  Created on: 01-Dec-2013
 *      Author: xion
 */

#include "Neuron.h"

	Neuron::Neuron(int no_of_inputs)
	{
		d_weightVector=thrust::device_vector<double>(no_of_inputs);
		h_weightVector=thrust::host_vector<double>(no_of_inputs);

		d_momentum=	thrust::device_vector<double>(no_of_inputs,0);
		h_momentum=	thrust::host_vector<double>(no_of_inputs,0);;
	}

	Neuron::~Neuron()
	{
		// TODO Auto-generated destructor stub
	}
