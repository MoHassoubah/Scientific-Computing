#include"csvreader.h"

/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
std::vector<std::vector<double> > CSVReader::getData()
{
    std::ifstream file(fileName);

    std::vector<std::vector<double> > dataList;

    std::string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        std::istringstream ss(line);
        std::string token;
        std::vector<double> csvRow;

        while(std::getline(ss, token, ','))
        {
            if((token == "x") || (token == "y"))
            {
                //std::cout << "token" << '\n';
                continue;
            }
            csvRow.push_back(std::stod(token));

        }
        dataList.push_back(csvRow);
    }
    std::cout << "dataList size"<< dataList.size() << '\n';
    // Close the File
    file.close();

    return dataList;
}
