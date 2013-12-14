/*
 * TrainingSet.h
 *
 *  Created on: 08-Dec-2013
 *      Author: xion
 */


#ifndef TRAININGSET_H_
#define TRAININGSET_H_

#include <vector>

class TrainingSet {

protected:
	int iteratorPosition;
    int patternCount;
public:
	TrainingSet(int no_of_patterns);
	virtual ~TrainingSet();
	virtual bool next();
	virtual std::vector<double> getInputSet()=0;
	virtual std::vector<double> getDesiredOutputSet()=0;
    int getPatternCount();
    int getIndexofCurrentPattern();
    
};

#endif /* TRAININGSET_H_ */
