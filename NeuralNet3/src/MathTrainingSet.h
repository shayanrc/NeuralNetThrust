/*
 * MathTrainingSet.h
 *
 *  Created on: 08-Dec-2013
 *      Author: xion
 */

#ifndef MATHTRAININGSET_H_
#define MATHTRAININGSET_H_

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "TrainingSet.h"

class MathTrainingSet: public TrainingSet {
	std::vector<double> input1;
	std::vector<double> input2;
	std::vector<double> input3;
	std::vector<double> desiredoutput1;
	std::vector<double> desiredoutput2;
	std::vector<double> desiredoutput3;

public:
    MathTrainingSet(int no_of_patterns);
	virtual ~MathTrainingSet();
    std::vector<double> getInputSet();
    std::vector<double> getDesiredOutputSet();
};


void normalize(std::vector<double>& data);
void standardize(double *data, int dataSize);

#endif /* MATHTRAININGSET_H_ */
