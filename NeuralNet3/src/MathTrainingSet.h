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
#include "TrainingSet.h"

class MathTrainingSet: public TrainingSet {
	std::vector<double> input1;
	std::vector<double> input2;
	std::vector<double> input3;
	std::vector<double> desiredoutput1;
	std::vector<double> desiredoutput2;
	std::vector<double> desiredoutput3;
	//struct gen_rand;
public:
    //bool next();
	MathTrainingSet(int no_of_patterns);
	//virtual ~MathTrainingSet();
    std::vector<double> getInputSet();
    std::vector<double> getDesiredOutputSet();
};

#endif /* MATHTRAININGSET_H_ */
