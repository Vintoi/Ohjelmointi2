#include <iostream>
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1

using namespace std;

int main()
{
    int r_value = 0;
    string key, teksti, uusi_teksti;
    string aakkoset = "abcdefghijklmnopqrstuvwxyz";

    cout << "Enter the encryption key: " ;
    cin >> key;

    string::size_type pituus = 0;
    pituus = key.length();

    char kirjain;
    bool iso = false;
    string::size_type kohta = 0;
    string temp = aakkoset;
    int aakkosia = 0;
    for(unsigned int i = 0; i < key.length();  ++i){
        kirjain = key.at(i);
        kohta = temp.find(key.at(i));
        if(isupper(kirjain)){
            iso = true;
        }
        if (kohta != string::npos) {
            aakkosia += 1;
            temp.erase(kohta,1);
        }
    }
    if(pituus != 26){
        cout << "Error! The encryption key must contain 26 characters."<<endl;
        r_value = 1;
    }
    else if (iso == true){
        cout << "Error! The encryption key must contain only lower case characters" << endl;
        r_value = 1;
    } else if (aakkosia !=26){
        cout << "Error! The encryption key must contain all alphabets a-z." <<endl;
        r_value = 1;
    }

    if (r_value == 0){
        cout << "Enter the text to be encrypted: ";
        cin >> teksti;
        char old_c, new_c;
        int char_pos;
        for(unsigned int i = 0; i < teksti.length();++i){
            old_c = teksti.at(i);
            char_pos = aakkoset.find(old_c);
            new_c = key.at(char_pos);
            uusi_teksti += new_c;
        }
        cout <<  "Encrypted text: " << uusi_teksti <<endl;
        r_value = 0;
    }


    return r_value;
}
