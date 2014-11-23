/*
 * CSVReader.h
 *
 *  Created on: 05-Sep-2013
 *      Author: xion
 */

#ifndef CSVREADER_H_
#define CSVREADER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

	class CSVReader {

    //vector<string> lines;
    vector<string> columnHeader;
    vector<vector<string> > columns;
    int no_of_lines;
    int no_of_cols;
    bool fileOpenSuccess;

    public:
    CSVReader();
    CSVReader(string inputFile, bool hasHeader);
    vector<string> getColumn(int columnIndex);
    string getLine(int rowIndex);
    string getLineByValueAtColumn(string value, int column);
    int getLineNoByValueAtColumn(string value, int columnIndex);
    string getHeader(int columnIndex);
    int getColumnCount();
    int getRowCount();
    vector<string> getRow(int rowIndex);
    vector<string> getRowByValueAtColumn(string value, int columnIndex);
    bool isFileOpen();
	};
#endif /* CSVREADER_H_ */
