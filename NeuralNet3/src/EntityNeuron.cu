/*
 * EntityNeuron.cpp
 *
 *  Created on: 19-Mar-2014
 *      Author: xion
 */

#include "EntityNeuron.h"

EntityNeuron::EntityNeuron(std::string entName,int no_of_inputs):Neuron(no_of_inputs)
{
	std::cout<<"Making EntityNeuron ["<<entName<<"] with "<<no_of_inputs<<" inputs\n";
	entityName=entName;
	inputs=std::vector<double>(no_of_inputs,0);
	learnigRate=1;
	momentumConstant=0;

}

template< typename T >
struct multiplyByConstant
{
    const T constant;

    multiplyByConstant(T _constant) : constant(_constant) {}

    __host__ __device__
        void operator()( T& VecElem) const {
            VecElem=VecElem*constant;
        }
};


double activiation(double x)
{
	return 1/(1+exp(-x));
}

double deactiviation(double x)
{
	return x*(1-x);
}

void EntityNeuron::setInputs(std::vector<double> entityInputs)
{
	inputs=entityInputs;

	//added for bias
	inputs.push_back(1);
}

double EntityNeuron::feedForward()
{
	std::cout<<"EntityNeuron::feedForward : Inputs ("<<entityName<<") :\n";
	printVector(inputs);
	//create device vector and store inputs in it
	thrust::device_vector<double> d_inputs(inputs.size());
	thrust::copy(inputs.begin(),inputs.end(),d_inputs.begin());
	thrust::device_vector<double> WxI(inputCount);
	thrust::transform(d_inputs.begin(),d_inputs.end(),d_weightVector.begin(),WxI.begin(),thrust::multiplies<double>());

	double output=thrust::reduce(WxI.begin(),WxI.end());
	std::cout<<"Output["<<entityName<<"] :"<<output<<"\n";
	return output;
}

void EntityNeuron::setLearnigRate(double rate)
{
	learnigRate=rate;
}

void EntityNeuron::modifyweights(double dw)
{
	thrust::device_vector<double> weightChange(inputs.size());

	//Calculate weightChange
	//weightChange=inputs*dw*learningRate
	thrust::copy(inputs.begin(),inputs.end(),weightChange.begin());
	thrust::for_each(weightChange.begin(),weightChange.end(),multiplyByConstant<double>(learnigRate));
	thrust::for_each(weightChange.begin(),weightChange.end(),multiplyByConstant<double>(dw));

	thrust::transform(weightChange.begin(),weightChange.end(),d_momentum.begin(),weightChange.begin(),thrust::plus<double>());
	thrust::transform(d_weightVector.begin(),d_weightVector.end(),weightChange.begin(),d_weightVector.begin(),thrust::plus<double>());

	//store the change inweight as the next iterations momentum
	d_momentum=weightChange;
	thrust::for_each(d_momentum.begin(),d_momentum.end(),multiplyByConstant<double>(momentumConstant));

}

std::string EntityNeuron::getName()
{
	return entityName;
}

EntityNeuron::~EntityNeuron()
{
	// TODO Auto-generated destructor stub
}

