#include "utils.h"

void printVector(std::vector<double> vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(std::cout, ","));

	std::cout<<"\n";
}

void printVector(thrust::host_vector<double> vec)
{
	thrust::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(std::cout, ","));

	std::cout<<"\n";
}

void printVector(thrust::device_vector<double> vec)
{
	thrust::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(std::cout, ","));

	std::cout<<"\n";
}
