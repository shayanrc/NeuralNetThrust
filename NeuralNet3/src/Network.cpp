/*
 * Network.cpp
 *
 *  Created on: 11-Dec-2013
 *      Author: xion
 */

#include "Network.h"
#include "OutputLayer.h"
#include "StockDataTrainingSet.h"
#include "EntityInputLayer.h"


//Remove training set initialization from here -> Need a better approach
Network::Network(int layerCount, int inputCount, int outputCount, double learningRate, double momentum, TrainingSet *trainingSet)
{
no_of_layers=layerCount;
no_of_outputs=outputCount;
no_of_inputs=inputCount;
trainingset=trainingSet;
//layers=std::vector<Layer>(layerCount,Layer(inputCount,outputCount,learningRate,momentum));
//Layer inputLayer(inputCount,inputCount);

/*if(layerCount>1)
{
	layers=std::vector<Layer *>(layerCount-1,Layer(outputCount,outputCount));
}*/
//layers.insert(layers.begin(),inputLayer);
//layers.push_back(&inputLayer);

//Generate and insert all layers
for(int i=layerCount-1;i>0;i--)
{
	layers.push_back(new Layer(inputCount,inputCount,learningRate,momentum));
}

//OutputLayer *outputLayer =new OutputLayer(trainingSet,inputCount,outputCount);
//layers.push_back(outputLayer);

layers.push_back(new OutputLayer(trainingSet,inputCount,outputCount));



}

void Network::randomizeWeights()
{
	for(int layerIndex=0;layerIndex<layers.size();layerIndex++)
	{
		//std::cout<<"layer :"<<layerIndex<<" Randomize Weights\n";
		layers[layerIndex]->randomizeWeights();
	}
}

void Network::insertLayer(Layer *layer, int index)
{
//	Layer* layerPtr=&layer;

	layers[index]=layer;

	//std::cout<<"Inserting layer "<<layers[index]->name<<" at "<<index<<"\n";

}

void Network::train()
{


	CSVWriter outcsv("OutPut.csv");

	StockDataTrainingSet *stockDataTrainingSet=dynamic_cast<StockDataTrainingSet*>(trainingset);
	std::vector<std::string> stringLoggerVector;
	if(stockDataTrainingSet)
	{
		stringLoggerVector=stockDataTrainingSet->getEntityNames();
		stringLoggerVector.insert(stringLoggerVector.begin(),"Training Pattern");
		stringLoggerVector.insert(stringLoggerVector.begin(),"Type ");
		outcsv.write(stringLoggerVector);

	}

	stringLoggerVector.clear();

	//std::string headerArr[]=	 {"input1","input2","input3","Output1","Output2","Output3","desiredOutput1","desiredOutput2","desiredOutput3","Error1","Error2","Error3"};

	//std::vector<std::string> headerVector(headerArr,headerArr+12);
	//outcsv.write(headerVector);
	std::vector<double> loggerVec;
	std::vector<double> outputVec;
	std::vector<double> desiredOutputVec;
	std::vector<double> errorVec;

	std::cout<<"training start:"<<trainingset->getPatternCount();
	//Main training loop
	int patternCount =trainingset->getPatternCount();
	for(int i=0;i<patternCount;trainingset->next(),i++) //TODO REplace with while(trainingset->next())
	{
		std::cout<<"\nTraining set : "<<i+1<<"\n";
		std::vector<double> inputs=trainingset->getInputSet();
		//std::vector<double> desiredOutputs=trainingset->getDesiredOutputSet();

		//Set inputs to the input (first) layer
		//layers.front()->setInputs(inputs);

		//std::cout<<"\nInputs :\n";
		//std::copy(inputs.begin(), inputs.end(), std::ostream_iterator<double>(std::cout, " "));

		//Set DesiredOutputs to the DesiredOutputs (last) layer
		//layers.back()->setDesiredOutputs(desiredOutputs);

		//std::cout<<"\ndesiredOutputs :\n";
		///std::copy(desiredOutputs.begin(), desiredOutputs.end(), std::ostream_iterator<double>(std::cout, " "));

		int activeLayer=0;

		std::cout<<"\nno_of_layers:"<<no_of_layers<<"\n";

		//Forward propagation loop
		while(activeLayer<no_of_layers)
		{
			std::cout<<"\nFeedforward in layer "<<activeLayer<<"\n";
			layers[activeLayer]->feedForward();


			//Check for output layer
			if(activeLayer==no_of_layers-1)
			{

				//OutputLayer *outputLayer=layers[activeLayer];
				std::cout<<"Calculate error in pattern "<<i<<"\n";
				layers[activeLayer]->calculateError();
				outputVec=layers[activeLayer]->getOutputs();
				std::cout<<"Output : \n";
				printVector(outputVec);
				//desiredOutputVec=layers[activeLayer].getDesiredOutputs();
				desiredOutputVec=trainingset->getDesiredOutputSet();

				std::cout<<"Desired Output : ";
				printVector(desiredOutputVec);
				std::cout<<"\nError: ";
				errorVec=layers[activeLayer]->getError();
				printVector(errorVec);

				OutputLayer *outputLayer=dynamic_cast<OutputLayer*>(layers[activeLayer]);
				if(outputLayer)
				{
					//cout<<"Dynamic cat success";
					outputLayer->nextDesiredOutput();
				}
				loggerVec.clear();
				/*loggerVec.insert(loggerVec.begin(),inputs.begin(),inputs.end());
				loggerVec.insert(loggerVec.end(),outputVec.begin(),outputVec.end());
				loggerVec.insert(loggerVec.end(),desiredOutputVec.begin(),desiredOutputVec.end());
				loggerVec.insert(loggerVec.end(),errorVec.begin(),errorVec.end());*/

				//Wrtie Output to output.csv
				std::transform(outputVec.begin(), outputVec.end(), std::back_inserter(stringLoggerVector),
						[](const double x) { return std::to_string(x); });
				stringLoggerVector.insert(stringLoggerVector.begin(),std::to_string(i));
				stringLoggerVector.insert(stringLoggerVector.begin(),"Output");

				outcsv.write(stringLoggerVector);

				stringLoggerVector.clear();


				//Wrtie Desired Output to output.csv
				std::transform(desiredOutputVec.begin(), desiredOutputVec.end(), std::back_inserter(stringLoggerVector),
						[](const double x) { return std::to_string(x); });
				stringLoggerVector.insert(stringLoggerVector.begin(),std::to_string(i));
				stringLoggerVector.insert(stringLoggerVector.begin(),"Desired Output");

				outcsv.write(stringLoggerVector);

				stringLoggerVector.clear();

				//Wrtie Error to output.csv
				std::transform(errorVec.begin(), errorVec.end(), std::back_inserter(stringLoggerVector),
				               [](const double x) { return std::to_string(x); });
				stringLoggerVector.insert(stringLoggerVector.begin(),std::to_string(i));
				stringLoggerVector.insert(stringLoggerVector.begin(),"Error Output");


				outcsv.write(stringLoggerVector);

				stringLoggerVector.clear();


			}
			else
			{
				std::cout<<"Propagate to layer "<<activeLayer+1;
				//set the outputs of active layer as the inputs of the next layer
				layers[activeLayer]->propagateOutput(layers[activeLayer+1]);

			}

			cudaDeviceSynchronize(); //wait for all preceding GPU operations to end
			activeLayer++;
		}



		//Backpropagation loop
		while (--activeLayer >= 0)
		{
			std::cout<<"\nModify Weight in Layer "<<activeLayer<<"\n";
			layers[activeLayer]->modifyweights();

			//propagate the weight change back if it is not the input layer

			if(activeLayer!=0)
				{	Layer* tempLayer=layers.at(activeLayer-1);
					std::cout<<"propagateBack in Layer "<<activeLayer<<"\n";
					layers[activeLayer]->propagateBack(tempLayer);
				}
			else
			{

				//trainingset->next();
				EntityInputLayer *eIL=dynamic_cast<EntityInputLayer*>(layers[activeLayer]);
				if(eIL)
				{
				 //cout<<"Conversion to EntityInputLayer successfull: nextInput()\n";
				 eIL->nextInput();
				}
				else
				{
				 cout<<"Not EntityInputLayer??\n";
				}
			}
		}

		//trainingset->next();
		//layers.front()->nextInput();

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

/*MathTrainingSet Network::getTrainingset() const {
	return trainingset;
}*/

bool Network::nextInput()
{
	trainingset->next();
	
}

void Network::setTrainingset(StockDataTrainingSet *trainingset) {
	this->trainingset = trainingset;
}



