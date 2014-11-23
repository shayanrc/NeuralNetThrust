#include "utils.h"

void printVector(std::vector<double> vec)
{


	for(std::vector<double>::iterator it=vec.begin();it!=vec.end();it++)
	{
		std::cout<<"["<<*it<<"] ";
	}

	std::cout<<"\n";
}

void printVector(std::vector<double> vec, std::string separator)
{
	for(std::vector<double>::iterator it=vec.begin();it!=vec.end();it++)
	{
		std::cout<<*it<<separator;
	}

	std::cout<<"\n";
}

void printVector(thrust::host_vector<double> vec)
{
		for(thrust::host_vector<double>::iterator it=vec.begin();it!=vec.end();it++)
	{
		std::cout<<"["<<*it<<"] ";
	}

	std::cout<<"\n";
}

void printVector(thrust::device_vector<double> vec)
{
	for(thrust::device_vector<double>::iterator it=vec.begin();it!=vec.end();it++)
	{
		std::cout<<"["<<*it<<"] ";
	}

	std::cout<<"\n";
}
