/*
 * utils.h
 *
 *  Created on: 28-Dec-2013
 *      Author: xion
 */

#ifndef UTILS_H_
#define UTILS_H_


#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <vector>

//helper functions to print vectors
void printVector(std::vector<double> vec);
void printVector(std::vector<double> vec, std::string separator);


//helper functions to print host & device vectors
void printVector(thrust::host_vector<double> vec);
void printVector(thrust::device_vector<double> vec);



#endif /* UTILS_H_ */
