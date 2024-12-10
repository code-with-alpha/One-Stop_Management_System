#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

class ConfigReader
{
private:
    string defaultSortingAlgorithm;
    string defaultSearchingAlgorithm;
    int threshold;

public:
    ConfigReader();
    void loadConfig(const string &filename);
    string getDefaultSortingAlgorithm() const;
    string getDefaultSearchingAlgorithm() const;
    int getThreshold() const;
};

ConfigReader::ConfigReader() : threshold(50) {}

void ConfigReader::loadConfig(const string &filename)
{
    ifstream configFile(filename);
    if (!configFile.is_open())
    {
        cerr << "Unable to open config file. Using default settings.\n";
        return;
    }

    try
    {
        string line;
        while (getline(configFile, line))
        {
            if (line.find("default_sorting_algorithm=") == 0)
            {
                defaultSortingAlgorithm = line.substr(line.find('=') + 1);
            }
            else if (line.find("default_searching_algorithm=") == 0)
            {
                defaultSearchingAlgorithm = line.substr(line.find('=') + 1);
            }
            else if (line.find("threshold=") == 0)
            {
                threshold = stoi(line.substr(line.find('=') + 1));
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Error reading config file: " << e.what() << '\n';
    }

    configFile.close();
}

string ConfigReader::getDefaultSortingAlgorithm() const
{
    return defaultSortingAlgorithm;
}

string ConfigReader::getDefaultSearchingAlgorithm() const
{
    return defaultSearchingAlgorithm;
}
int ConfigReader::getThreshold() const
{
    return threshold;
}