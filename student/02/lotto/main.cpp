#include <iostream>

using namespace std;
void kertoma (int balls, int draw) {

    unsigned long int n = balls;
    unsigned long int p = draw;

    for (int i = balls-1; i > 0 ; --i ){
        n = n*i;
    }
    for (int i = draw-1 ; i > 0; --i){
        p = p*i;
    }
    unsigned long int np = (balls-draw);
    for (int luku = (balls-draw)-1; luku > 0 ; --luku ){
        np = np*luku;
    }

    if (balls < 0) {
        cout << "The number of balls must be a positive number. "<< endl;
    } else if (draw > balls ) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    } else if (draw == balls) {
        cout << "The probability of guessing all "<<balls <<" balls correctly is 1/1" <<endl;
    } else if (balls > 0) {
        unsigned long int prob = (n / (np*p));
        //cout << n << " " << np << " " << p <<endl;
        cout << "The probability of guessing all "<< draw <<" balls correctly is 1/"<<prob<<endl;
    }
}

int main()
{
    std::cout << "Enter the total number of lottery balls: ";
    int balls = 0;
    std::cin >> balls;
    std::cout << "Enter the number of drawn balls: ";
    int draw = 0;
    std::cin >> draw;
    kertoma(balls,draw);
    return 0;
}
