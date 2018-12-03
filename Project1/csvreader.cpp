#include"csvreader.h"

/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
std::vector<std::vector<std::string> > CSVReader::getData()
{
    std::ifstream file(fileName);

    std::vector<std::vector<std::string> > dataList;

    std::string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        std::istringstream ss(line);
        std::string token;

        while(std::getline(ss, token, ',')) {
            std::cout << token << '\n';
            if(token == "x")
            {
                std::cout << "token" << '\n';
            }
        }
    }
    // Close the File
    file.close();

    return dataList;
}
