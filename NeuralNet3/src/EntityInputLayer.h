/*
 * EntityInputLayer.h
 *
 *  Created on: 09-Apr-2014
 *      Author: xion
 */

#ifndef ENTITYINPUTLAYER_H_
#define ENTITYINPUTLAYER_H_

#include "Layer.h"
#include "EntityNeuron.h"
#include  "StockDataTrainingSet.h"

class EntityInputLayer : public Layer {

	std::vector<EntityNeuron> neurons;

	int no_of_entities;
	int no_of_attributes;
	StockDataTrainingSet *trainingSet; //TODO convert this to a pointer of type TrainingSet, so it can hold classes derived from TrainingSet
	vector<string> entityNamesList;

public:
	//EntityInputLayer(std::vector<std::string> entityNamesList, int attributeCount);
	EntityInputLayer(StockDataTrainingSet *stockDataTrainingSet);
	void setEntityInput(std::string entityName, std::vector<double> inputs);
	void setEntityInputset(StockDataTrainingSet *entityInputSet); //TODO replace this with a more generic setTrainingSet
	void nextInput(); //TODO implement this in input layer base class Layer
	void feedForward();
	void modifyweights();
	void identify();
	virtual ~EntityInputLayer();
};

#endif /* ENTITYINPUTLAYER_H_ */
