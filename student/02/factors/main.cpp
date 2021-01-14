#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int num = 0;
    std::cin >> num;
    int eka = 0;
    //int toka = 2;
    if(num % 2 == 0) {
        eka = num / 2;
    }


    if(num <= 0){
        cout << "Only positive numbers accepted" << endl;
    } else {
        cout << num <<" = " << eka << " * "<< 2 << endl;
    }
    return 0;
}
