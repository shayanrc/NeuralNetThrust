/*
 * Network.cpp
 *
 *  Created on: 11-Dec-2013
 *      Author: xion
 */

#include "Network.h"


//Remove training set initialization from here -> Need a better approach
Network::Network(int layerCount, int inputCount, int outputCount, double learningRate, double momentum)
:trainingset(100)
{
no_of_layers=layerCount;
//layers=std::vector<Layer>(layerCount,Layer(inputCount,outputCount,learningRate,momentum));
Layer inputLayer(inputCount,outputCount);
if(layerCount>1)
{
	layers=std::vector<Layer>(layerCount-1,Layer(outputCount,outputCount));
}
layers.insert(layers.begin(),inputLayer);

}

void Network::randomizeWeights()
{
	for(int layerIndex=0;layerIndex<layers.size();layerIndex++)
	{
		//std::cout<<"layer :"<<layerIndex<<" Randomize Weights\n";
		layers[layerIndex].randomizeWeights();
	}
}



void Network::train()
{

	CSVWriter outcsv("OutPut.csv");
	std::string headerArr[]=	 {"input1","input2","input3","Output1","Output2","Output3","desiredOutput1","desiredOutput2","desiredOutput3","Error1","Error2","Error3"};
	std::vector<std::string> headerVector(headerArr,headerArr+12);
	outcsv.write(headerVector);
	std::vector<double> loggerVec;
	std::vector<double> outputVec;
	std::vector<double> desiredOutputVec;
	std::vector<double> errorVec;
	//Main training loop
	//REplace with while(trainingset.next())
	for(int i=0;i<trainingset.getPatternCount();trainingset.next(),i++)
	{
		std::cout<<"\nTraining set : "<<i+1<<"\n";
		std::vector<double> inputs=trainingset.getInputSet();
		std::vector<double> desiredOutputs=trainingset.getDesiredOutputSet();

		//Set inputs to the input (first) layer
		layers.front().setInputs(inputs);

		std::cout<<"\nInputs :\n";
		std::copy(inputs.begin(), inputs.end(), std::ostream_iterator<double>(std::cout, " "));

		//Set DesiredOutputs to the DesiredOutputs (last) layer
		layers.back().setDesiredOutputs(desiredOutputs);

		std::cout<<"\ndesiredOutputs :\n";
		std::copy(desiredOutputs.begin(), desiredOutputs.end(), std::ostream_iterator<double>(std::cout, " "));

		int activeLayer=0;

		std::cout<<"\nno_of_layers:"<<no_of_layers<<"\n";

		//Forward propagation loop
		while(activeLayer<no_of_layers)
		{
			std::cout<<"\nFeedforward in layer "<<activeLayer<<"\n";
			layers[activeLayer].feedForward();


			//Check for output layer
			if(activeLayer==no_of_layers-1)
			{
				std::cout<<"Calculate error in pattern "<<i<<"\n";
				layers[activeLayer].calculateError();
				outputVec=layers[activeLayer].getOutputs();
				std::cout<<"Output : \n";
				printVector(outputVec);
				std::cout<<"Desired Output : ";
				//desiredOutputVec=layers[activeLayer].getDesiredOutputs();
				desiredOutputVec=trainingset.getOutputSet();
				printVector(desiredOutputVec);
				std::cout<<"\nError: ";
				errorVec=layers[activeLayer].getError();
				printVector(errorVec);
				loggerVec.clear();
				loggerVec.insert(loggerVec.begin(),inputs.begin(),inputs.end());
				loggerVec.insert(loggerVec.end(),outputVec.begin(),outputVec.end());
				loggerVec.insert(loggerVec.end(),desiredOutputVec.begin(),desiredOutputVec.end());
				loggerVec.insert(loggerVec.end(),errorVec.begin(),errorVec.end());
				outcsv.write(loggerVec);
			}
			else
			{
				std::cout<<"Propagate to layer "<<activeLayer+1;
				//set the outputs of active layer as the inputs of the next layer
				layers[activeLayer].propagateOutput(layers[activeLayer+1]);

			}

			cudaDeviceSynchronize();
			activeLayer++;
		}



		//Backpropagation loop
		while (--activeLayer >= 0)
		{
			std::cout<<"\nModify Weight in Layer "<<activeLayer<<"\n";
			layers[activeLayer].modifyweights();

			//propagate the weight change back if it is not the input layer
			if(activeLayer!=0)
				{

					std::cout<<"propagateBack in Layer "<<activeLayer<<"\n";
					layers[activeLayer].propagateBack(layers[activeLayer-1]);
				}

		}

	}
	return;
}


int Network::getNoOfInputs() const {
	return no_of_inputs;
}

int Network::getNoOfLayers() const {
	return no_of_layers;
}

int Network::getNoOfOutputs() const {
	return no_of_outputs;
}

MathTrainingSet Network::getTrainingset() const {
	return trainingset;
}

void Network::setTrainingset(MathTrainingSet trainingset) {
	this->trainingset = trainingset;
}



