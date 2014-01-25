/**
 * Copyright 1993-2012 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 */
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/reduce.h>
#include "Network.h"
#include "MathTrainingSet.h"
#include "Layer.h"

int main()
{

	int no_of_layers=3;
	int no_of_inputs=3;
	int no_of_outputs=3;

	double momentum=0;
	double learninRate=1;

	//seed random number generators
	srand(time(NULL));


	//init training set
	MathTrainingSet trainingset(1000);

	trainingset.setDesiredOutputOffset(10);
	//init network
	Network net(no_of_layers,no_of_inputs,no_of_outputs,learninRate,momentum);

	net.randomizeWeights();

	net.setTrainingset(trainingset);


	net.train();



}
