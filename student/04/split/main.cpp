#include <iostream>
#include <string>
#include <vector>

using namespace std;
// TODO: Implement split function here
// Do not change main function

vector<std::string> split(const std::string mjono, char seper, bool spaces=false)
{
    std::vector<std::string> parts;

    size_t alku = 0;
    size_t loppu = 0;

    while (loppu != mjono.size())
    {
        loppu = mjono.find(seper,alku);
        if (loppu == std::string::npos){
            loppu = mjono.size();
        }

        if(!spaces || alku != loppu)
        {
            parts.push_back(mjono.substr(alku, loppu-alku));
        }

        alku = loppu+1;

    }

    //loppu = mjono.size();
    //parts.push_back(mjono.substr(alku, loppu-alku));


    return parts;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
