/*
 * MathTrainingSet.cpp
 *
 *  Created on: 08-Dec-2013
 *      Author: xion
 */

#define MAX 10
#include "MathTrainingSet.h"

struct gen_rand {
    double range;
public:
    gen_rand(double r=1.0) : range(r) {}
    double operator()() {
        return (rand()%(int)MAX) * range;
    }
};

MathTrainingSet::MathTrainingSet(int no_of_patterns):TrainingSet(no_of_patterns)
{
    //Alloc inputs
    input1=std::vector<double>(patternCount);
    input2=std::vector<double>(patternCount);
    input3=std::vector<double>(patternCount);
    
    //Alloc desiredoutput
    desiredoutput1=std::vector<double>(patternCount);
    desiredoutput2=std::vector<double>(patternCount);
    desiredoutput3=std::vector<double>(patternCount);
    
    //Fill input vetors with random input
	std::generate(input1.begin(),input1.end(),gen_rand());
	std::generate(input2.begin(),input2.end(),gen_rand());
	std::generate(input3.begin(),input3.end(),gen_rand());
    
    for (int i=0; i<patternCount; i++) {
        desiredoutput1[i]=input1[i]*input1[i]+input2[i]/input3[i];
        desiredoutput2[i]=3*input1[i]*input1[i]+4*input3[i];
        desiredoutput3[i]=5*input1[i]+3*input2[i]*input3[i]+7;
    }

    
}

void standardize(double *data, int dataSize)
{
	double mean=0;
	double standardDev;
	double temp=0;
	double temp2=0;

	//Calculate mean
	for(int i=0;i<dataSize;i++)
	{
		temp+=data[i];
	}
	mean=temp/dataSize;

	temp=0;

	//Calculate variance: sum of (mean-value)^2
	for(int i=0;i<dataSize;i++)
	{
		temp2=mean-data[i];
		temp+=temp2*temp2;
	}

	//Calculate variance
	standardDev=sqrt(temp/dataSize);

	//Actual standardization occurs here
	for(int i=0;i<dataSize;i++)
	{
		data[i]=(data[i]-mean)/standardDev;
	}



}



std::vector<double> MathTrainingSet::getInputSet()
{
    std::vector<double> inputSet(3);
    
    inputSet[0]=input1[iteratorPosition];
    inputSet[1]=input2[iteratorPosition];
    inputSet[2]=input3[iteratorPosition];
    standardize(&inputSet[0],inputSet.size());
    return inputSet;
    
}
std::vector<double> MathTrainingSet::getDesiredOutputSet()
{
    std::vector<double> desiredOutputSet(3);
    
    desiredOutputSet[0]=desiredoutput1[iteratorPosition];
    desiredOutputSet[1]=desiredoutput2[iteratorPosition];
    desiredOutputSet[2]=desiredoutput3[iteratorPosition];
    standardize(&desiredOutputSet[0],desiredOutputSet.size());
    return desiredOutputSet;
}

MathTrainingSet::~MathTrainingSet(){}

