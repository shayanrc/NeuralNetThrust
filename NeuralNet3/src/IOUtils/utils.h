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

void printVector(std::vector<double> vec);

void printVector(thrust::host_vector<double> vec);
void printVector(thrust::device_vector<double> vec);



#endif /* UTILS_H_ */
