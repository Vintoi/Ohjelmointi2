#include <iostream>

using namespace std;

int main()
{
    string key;
    cout << "Enter the encryption key: " ;
    cin >> key;

    string::size_type pituus = 0;
    pituus = key.length();
    if(pituus != 26){
        cout << "Error! The encryption key must contain 26 characters."<<endl;
        return EXIT_FAILURE;
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
        return EXIT_FAILURE;
    }

    return 0;
}
