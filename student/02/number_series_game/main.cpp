#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int num = 0;
    std::cin >> num;

    for (int i = 1; i <= num; ++i){
        std::cout << i << std::endl;
    }
}
