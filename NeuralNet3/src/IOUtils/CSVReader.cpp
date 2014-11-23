/*
 * CSVReader.cpp
 *
 *  Created on: 05-Sep-2013
 *      Author: xion
 */

#include "CSVReader.h"
#include "algorithm"

CSVReader::CSVReader(string inputFile, bool hasHeader)
{
    //cout<<"CSV reader constructor called with "<<inputFile<<"\n";
   ifstream data(inputFile.c_str(),ios::in);

   if(!data)
   {

	   //LOG(WARNING) << inputFile<<": File could not be opened\n";
	   fileOpenSuccess=false;
	   no_of_lines=0;
	   no_of_cols=0;
   }
   else
   {
	   string line;
	       int line_no=0;
	       int col_no;

	       //Get the first line to get the headers or calculate the no. of columns
	       std::getline(data,line);

	   	std::stringstream  headerStream(line);
	   	std::string        header;

	       if (hasHeader)
	       {
	       	while(std::getline(headerStream,header,','))
	   		{
	   		//Store the column headers
	   		columnHeader.push_back(header);
	   		vector<string> column;
	           columns.push_back(column);
	           //cout<<"Header "<<cell<<"\n";
	         }
	           no_of_cols=(int)columnHeader.size();
	       }
	       else
	       {
	        	//lines.push_back(line);
	           col_no=0;
	           while(std::getline(headerStream,header,','))
	           {
	           vector<string> column;
	           columns.push_back(column);
	           columns[col_no].push_back(header);
	           //cout<<"Header "<<col_no<<":"<<header<<"\n";

	           col_no++;
	           }
	           no_of_cols=col_no;
	           line_no++;
	       }


	       while(std::getline(data,line))
	       {
	           std::stringstream  lineStream(line);
	           std::string        cell;
	           //cout<<"reading line "<<line_no<<"\n";
	           col_no=0;
	           while(std::getline(lineStream,cell,','))
	           {

	              // cout<<"Cell "<<col_no<<":"<<header<<"\n";
	           	columns[col_no].push_back(cell);
	           	col_no++;
	           }

	           line_no++;
	       }
	       no_of_lines=line_no;
	   fileOpenSuccess=true;
	   //return;
   }

}

bool CSVReader::isFileOpen()
{
	return fileOpenSuccess;
}

vector<string> CSVReader::getRow(int rowIndex)
{
	vector<string> row(no_of_cols);
	for(int i=0;i<no_of_cols;i++)
	{
		row[i]=columns.at(i)[rowIndex];

		//cout<<i<<":"<<row[i]<<"\n";
	}
	return row;
}

string CSVReader::getLine(int rowIndex)
{
    string retVal;
    for(int i=0;i<no_of_cols;i++)
    	{
    		retVal.append((columns.at(i)).at(rowIndex));
    		retVal.append(",");
    	}
    return retVal;
}

vector<string> CSVReader::getColumn(int columnIndex)
{
    return columns[columnIndex];
}


string CSVReader::getHeader(int columnIndex)
{
    return columnHeader[columnIndex];
}


string  CSVReader::getLineByValueAtColumn(string value, int columnIndex)
{
	 int index=-1;
	    vector<string> column=columns.at(columnIndex);
	    vector<string>::iterator it;
	    if((it=find(column.begin(),column.end(),value))!=column.end())
	    {
	        index=(int)(it-column.begin());
	        return this->getLine(index);
	    }
	    else
	    {
	    	//cout<<"@getLineByValueAtColumn: not found";
	        return "";
	    }
}

vector<string>  CSVReader::getRowByValueAtColumn(string value, int columnIndex)
{
	 int index=-1;
	 	 vector<string> retVec;
	    vector<string> column=columns.at(columnIndex);
	    vector<string>::iterator it;
	    if((it=find(column.begin(),column.end(),value))!=column.end())
	    {
	        index=(int)(it-column.begin());
	        return this->getRow(index);
	    }
	    else
	    {
	    	//cout<<"@getLineByValueAtColumn: not found";
	        return retVec;
	    }
}

int CSVReader::getLineNoByValueAtColumn(string value, int columnIndex)
{
    int index=-1;
    vector<string> column=columns.at(columnIndex);
    vector<string>::iterator it;
    if((it=find(column.begin(),column.end(),value))!=column.end())
    {
        index=(int)(it-column.begin());

    }

    return index;

}

int CSVReader::getColumnCount()
{
	return no_of_cols;
}

int CSVReader::getRowCount()
{
	return no_of_lines;
}
