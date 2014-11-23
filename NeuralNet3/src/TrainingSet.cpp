//
//  TrainingSet.cpp
//  TrainingSets
//
//  Created by CTB on 10/12/13.
//  Copyright (c) 2013 RC. All rights reserved.
//

#include "TrainingSet.h"

TrainingSet::TrainingSet(int no_of_patterns)
{
		iteratorPosition=0;

        patternCount=no_of_patterns;
}

TrainingSet::~TrainingSet(){}

int TrainingSet::getPatternCount()
{
    return patternCount;
}



int TrainingSet::getIndexofCurrentPattern()
{
    return iteratorPosition;
}

bool TrainingSet::next()
{
    if(++iteratorPosition<patternCount)
    {
    	std::cout<<"Trainingset pattern "<<iteratorPosition<<"\n";
        return true;
    }
    else
    {

    	std::cout<<"Trainingset pattern "<<iteratorPosition<<" exceeded size "<<patternCount;
        return false;
    }
}

/*
std::vector<double> getInputSet()
{

	vector<double> inputSet(1,0);
	return inputSet;
}
*/

/*void printVector(std::vector<std::string> data, std::string separator) {
	//cout << "Writing " << data.size() << endl;
	for (unsigned i = 0; i < data.size(); i++) {
		std::cout << data.at(i) << separator;
	}
	std::cout << "\n";
}*/

/*void printVector(std::vector<double> data, std::string separator) {
	//cout << "Writing " << data.size() << endl;
	for (unsigned i = 0; i < data.size(); i++) {
		std::cout << data.at(i) << separator;
	}
	std::cout << "\n";
}*/
