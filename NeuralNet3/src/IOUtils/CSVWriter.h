/*
 * CSVWriter.h
 *
 *  Created on: 18-Jan-2014
 *      Author: xion
 *      Class to write vector in CSV format to file
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

#ifndef CSVWRITER_H_
#define CSVWRITER_H_


class CSVWriter {
	std::ofstream CSVFile;

	/*std::string convertToString()
	{

	}
*/
public:
	CSVWriter(std::string fileName);

	/*template <class T>
	bool write(std::vector<T> vec);*/

	template <class T>
	bool write(std::vector<T> data)
	{
		std::cout<<"write called!!";
		bool writeSuccesfull=true;
		//std::ostringstream stringStream;

		for (unsigned i = 0; i < data.size(); i++) {
			//stringStream<<data.at(i)<< ",";

			//CSVFile<<i<<",";
			//CSVFile<<stringStream.str();
			CSVFile <<data.at(i)<< ",";
			//CSVFile<< std::fixed << std::setprecision(5) << data.at(i)<< ",";
			}
		//std::cout<<"stringStream :"<<stringStream.str();
		CSVFile<<"\n";
		return writeSuccesfull;
	}



	template <class T>
	bool write(thrust::host_vector<T> data)
	{
		bool writeSuccesfull=true;

		for (unsigned i = 0; i < data.size(); i++) {
				CSVFile << data.at(i) << ",";
			}
		CSVFile<<"\n";
		return writeSuccesfull;
	}


	template <class T>
	bool write(thrust::device_vector<T> data)
	{
		bool writeSuccesfull=true;

		for (unsigned i = 0; i < data.size(); i++) {
				CSVFile <<data.at(i) << ",";
			}
		CSVFile<<"\n";
		return writeSuccesfull;
	}

	~CSVWriter();

};
//template class CSVWriter::write<double>()
#endif /* CSVWRITER_H_ */
