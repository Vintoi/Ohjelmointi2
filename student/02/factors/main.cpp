#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int num = 0;
    std::cin >> num;
    int jakaja = 0;

    int pienin = 1;
    int erotus = num/1 -1;

    if(num <= 0){
        cout << "Only positive numbers accepted" << endl;
    } else {
        for (int i = 1; i <= num; ++i) {
            if(num % i == 0){
                if ((num/i-i) < 0){
                } else if ((num/i -i) < erotus){
                    erotus = num/i - i;
                    pienin = i;
                }
                    //cout << erotus << " " << pienin <<" " << i << endl;
                }

        }
        cout << num <<" = " << num/pienin << " * "<< pienin << endl;
    }

    return 0;
}
