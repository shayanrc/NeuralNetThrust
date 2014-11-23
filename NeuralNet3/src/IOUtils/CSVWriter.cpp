/*
 * CSVWriter.cpp
 *
 *  Created on: 18-Jan-2014
 *      Author: xion
 */

#include "CSVWriter.h"

CSVWriter::CSVWriter(std::string CSVFileName)
{
 CSVFile.open(CSVFileName.c_str(),std::ios::out);
}


/*template <class T>
bool CSVWriter::write(std::vector<T> data)
{
	bool writeSuccesfull=true;

	for (unsigned i = 0; i < data.size(); i++) {
			CSVFile << data.at(i) << ",";
		}
	CSVFile<<"\n";
	return writeSuccesfull;
}*/

CSVWriter::~CSVWriter()
{
	CSVFile.close();
}
