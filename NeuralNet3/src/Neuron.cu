/*
 * Neuron.cpp
 *
 *  Created on: 01-Dec-2013
 *      Author: xion
 */

#include "Neuron.h"


struct randomize
	{
		__host__  void operator()( double &x ) const {
		x=(double) (rand() % 1000000) / 1000000 - 0.5;

	}
};

	Neuron::Neuron(int no_of_inputs)
	{
		d_weightVector=thrust::device_vector<double>(no_of_inputs);
		h_weightVector=thrust::host_vector<double>(no_of_inputs);

		//Init weights to random numbers between 0.5 and -0.5 using the randomize functor
		thrust::for_each(h_weightVector.begin(),h_weightVector.end(),randomize());
		d_weightVector=h_weightVector;
		d_momentum=	thrust::device_vector<double>(no_of_inputs,0);
		h_momentum=	thrust::host_vector<double>(no_of_inputs,0);;
	}

	Neuron::~Neuron()
	{
		// TODO Auto-generated destructor stub
	}
