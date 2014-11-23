/*
 * EntityNeuron.h
 *
 *  Created on: 19-Mar-2014
 *      Author: xion
 */

#ifndef ENTITYNEURON_H_
#define ENTITYNEURON_H_

#include "Neuron.h"
#include "IOUtils/utils.h"

class EntityNeuron : public Neuron {
	std::string entityName;
	std::vector<double> inputs;
	double learnigRate;
	double momentumConstant;
	/*double activiation(double x);
	double deactiviation(double x);*/
public:
	EntityNeuron(std::string entiyName,int no_of_inputs);
	void setInputs(std::vector<double> entityInputs);
	void setLearnigRate(double rate);
	std::string getName();
	double feedForward();
	void modifyweights(double dW);
	virtual ~EntityNeuron();

};

#endif /* ENTITYNEURON_H_ */
