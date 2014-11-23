/*
 * CSVWriter.h
 *
 *  Created on: 18-Jan-2014
 *      Author: xion
 */


#include <iostream>
#include <fstream>
#include <vector>

#ifndef CSVWRITER_H_
#define CSVWRITER_H_


class CSVWriter {
	std::ofstream CSVFile;
public:
	CSVWriter(std::string fileName);

/*	template <class T>
	bool write(std::vector<T> vec);*/

	template <class T>
	bool write(std::vector<T> data)
	{
		bool writeSuccesfull=true;

		for (unsigned i = 0; i < data.size(); i++) {
				CSVFile << data.at(i) << ",";
			}
		CSVFile<<"\n";
		return writeSuccesfull;
	}

	~CSVWriter();

};
//template class CSVWriter::write<double>()
#endif /* CSVWRITER_H_ */
