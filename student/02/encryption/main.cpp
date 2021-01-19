#include <iostream>
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1

using namespace std;

int main()
{
    int r_value = 1;
    string key;
    cout << "Enter the encryption key: " ;
    cin >> key;

    string::size_type pituus = 0;
    pituus = key.length();
    if(pituus != 26){
        cout << "Error! The encryption key must contain 26 characters."<<endl;
        r_value = 1;
    }
    char kirjain;
    bool iso = false;
    for(long unsigned int i = 0; i < key.length();  ++i){
        kirjain = key.at(i);
        if(isupper(kirjain)){
            iso = true;
        }

    }
    if (iso == true){
        cout << "Error! The encryption key must contain only lower case characters" << endl;
        r_value = 1;
    }

    return r_value;
}
