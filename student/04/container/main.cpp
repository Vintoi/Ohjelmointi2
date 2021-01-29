#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }

}

// TODO: Implement your solution here
bool same_values(std::vector<int> ints)
{
    bool totuus = false;

    for(unsigned int i = 1; i < ints.size() ; ++i)
    {

        if (ints.at(0) == ints.at(i)){
            totuus = true;

        } else {
            totuus = false;
        }
    }
    return totuus;
}
bool is_ordered_non_strict_ascending(std::vector<int>& ints){
    bool totuus = false;
    for(unsigned int i = 1; i < ints.size() ; ++i)
    {
        if (ints.at(i-1) > ints.at(i)){
            totuus = false;
            break;
        } else {
            totuus = true;
        }
    }
    return totuus;
}
bool is_arithmetic_series(std::vector<int>& ints){
    bool totuus = false;
    int ratio = ints.at(1) - ints.at(0);
    for(unsigned int i = 1; i < ints.size() ; ++i){
        int vertailtava = ints.at(i) - ints.at(i-1);
        if (vertailtava != ratio){
            totuus = false;
        } else {
            totuus = true;
        }
    }
    return totuus;
}

bool is_geometric_series(std::vector<int>& ints){
    bool totuus = false;
    for(unsigned int i = 1; i < ints.size() ; ++i)
    {
        if (ints.at(i-1)+ints.at(i-1) == 0 && ints.at(i) == 0){
            totuus = false;
            break;
        } else if(ints.at(i-1)+ints.at(i-1) == ints.at(i) || same_values(ints)){
            totuus = true;

        } else{
            totuus = false;
        }
    }
    return totuus;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    /*
    for (int i = 0; i < integers.size() ; ++i){
        std::cout<<integers.at(i)<< std::endl;
    }
    */

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
