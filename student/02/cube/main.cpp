#include <iostream>

using namespace std;

int main()
{
    int sivu = 0;
    std::cout << "Enter a number: ";
    std::cin>> sivu;
    if (sivu == 0) {
        cout << "The cube of 0 is 0." << endl;
    } else {
        int kuutio = sivu*sivu*sivu;
        if(kuutio / sivu / sivu != sivu){
            cout << "Error! The cube of "<<sivu<<" is not " << kuutio << "." <<endl;
        } else {
            cout << "The cube of " << sivu << " is " << kuutio <<"."<< endl;
        }
    }
    return 0;
}
