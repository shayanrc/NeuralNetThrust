/**
 * Copyright 1993-2012 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 */

#include "Network.h"
#include "StockDataTrainingSet.h"
#include "EntityInputLayer.h"
#include "Layer.h"

int main()
{

	//init training set
	static const int arr[] = {2,3,4,5,6,7,8,9};//index of columns we want
	std::vector<int> requiredColumn(arr, arr + sizeof(arr) / sizeof(arr[0]) );//vector containing index of columns we want
	Time startDate=makeDate(9,1,2013);
	Time endDate=makeDate(9,1,2014);
	StockDataTrainingSet *test = new StockDataTrainingSet("/home/xion/Data2/",requiredColumn,startDate,endDate);


	int no_of_ent=test->getNoOfEntities();
	int no_of_outputs=no_of_ent;

	//init network
	Network stockDataNetwork(3,no_of_ent,no_of_outputs,1,0,test);


	EntityInputLayer *inputLayer= new EntityInputLayer(test);

	stockDataNetwork.insertLayer(inputLayer,0);	//TODO replace with setInputLayer

	stockDataNetwork.train();



}
