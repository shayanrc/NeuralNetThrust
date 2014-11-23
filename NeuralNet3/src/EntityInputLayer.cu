/*
 * EntityInputLayer.cpp
 *
 *  Created on: 09-Apr-2014
 *      Author: xion
 */

#include "EntityInputLayer.h"
using namespace std;

/*EntityInputLayer::EntityInputLayer(std::vector<std::string> entityNamesList, int attributeCount):Layer(attributeCount,entityNamesList.size())
{
	no_of_entities=entityNamesList.size();
	no_of_attributes=attributeCount;


	cout<<"Making EntityInputLayer with "<<no_of_entities<<" , "<<attributeCount<<" attributes each\n";
	learningRate=1;
	momentumConstant=0;

	for(vector<string>::iterator it=entityNamesList.begin();it!=entityNamesList.end();it++)
	{
		EntityNeuron neuron(*it,attributeCount);
		neuron.randomizeWeights();
		neurons.push_back(neuron);
	}

}*/

EntityInputLayer::EntityInputLayer(StockDataTrainingSet *stockDataTrainingSet):Layer(stockDataTrainingSet->getNoOfAttributes(),stockDataTrainingSet->getNoOfEntities())
{

	trainingSet =stockDataTrainingSet;
	no_of_entities=trainingSet->getNoOfEntities();
	no_of_attributes=trainingSet->getNoOfAttributes();

	std::vector<std::string> entityNamesList=trainingSet->getEntityNames();
	learningRate=1;
	momentumConstant=0;

	//Init each neurons with each entities
	for(vector<string>::iterator it=entityNamesList.begin();it!=entityNamesList.end();it++)
	{
		string entName=*it;
		EntityNeuron neuron(entName,no_of_attributes);
		neuron.randomizeWeights();
		neuron.setInputs(trainingSet->getEntityInputSet(entName));
		neurons.push_back(neuron);

	}





}

void EntityInputLayer::setEntityInput(std::string entityName, std::vector<double> inputs)
{
	for (unsigned int i = 0; i < neurons.size(); ++i)
	{
		if(entityName.compare(neurons[i].getName()))
		{
			cout<<"\nSetting input to EntityNeuron ["<<entityName<<"]\n";
			printVector(inputs);
			neurons[i].setInputs(inputs);
			return;
		}
	}
}

void EntityInputLayer::identify()
{
	cout<<"Entity Layer!!\n";
}

void EntityInputLayer::setEntityInputset(StockDataTrainingSet *entityInputSet)
{


	trainingSet=entityInputSet;
	entityNamesList = trainingSet->getEntityNames();
	string entName;
	//cout<<"#############################Accessing trainingSet at "<<trainingSet;
	for(vector<string>::iterator it=entityNamesList.begin();it!=entityNamesList.end();it++)
	{
		entName=*it;
		cout<<"Setting input "<<entName<<"\n";
		setEntityInput(entName,trainingSet->getEntityInputSet(entName));
	}
}



void EntityInputLayer::nextInput()
{
//	if(trainingSet->next())
//	{
		for(vector<string>::iterator it=entityNamesList.begin();it!=entityNamesList.end();it++)
		{
			string entName=*it;
			cout<<"Next Input: "<<entName<<"!!\n";
			setEntityInput(entName,trainingSet->getEntityInputSet(entName));
		}
//	}
}







void EntityInputLayer::feedForward()
{
	//thrust::transform(neurons.begin(),neurons.end(),d_outputs,mem_fun(&EntityNeuron::feedForward));


	cout<<"Entity Input Layer feed forward with "<<no_of_neurons<<" neurons\n";
	//Execute feedForward on each neuron and store in d_outputs
	for (unsigned int i = 0; i < no_of_neurons; ++i)
	{
		cout<<"Feedforward in EntityNeuron ["<<neurons[i].getName()<<"]\n";
		d_outputs[i]=neurons[i].feedForward();
	}

}

void EntityInputLayer::modifyweights()
{
	for (unsigned int i = 0; i < no_of_neurons; ++i)
	{
		neurons[i].modifyweights(d_dW[i]);
	}
}

EntityInputLayer::~EntityInputLayer()
{
	delete trainingSet;
	// TODO Auto-generated destructor stub
}

