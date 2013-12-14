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
        return true;
    }
    else
    {
        return false;
    }
}
