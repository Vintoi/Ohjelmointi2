#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
    map<string, int> tulokset;

    string input_file = "";
    cout << "Input file: ";
    getline(cin, input_file);

    ifstream input_olio;
    //ofstream output_olio;

    input_olio.open(input_file);
    if (not input_olio){
        //output_olio.close();
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        input_olio.close();
        return EXIT_FAILURE;
    } else {
        string rivi,nimi;
        string::size_type katkaisu;
        int pisteet;
        while(getline(input_olio,rivi)){
            katkaisu = rivi.find(":");
            nimi = rivi.substr(0,katkaisu);
            pisteet = stoi(rivi.substr(katkaisu+1));
            if (tulokset.find(nimi) != tulokset.end()){
                tulokset[nimi] = tulokset[nimi] + pisteet;
            } else {
                tulokset.insert({nimi,pisteet});
            }
        }

    }
    cout <<"Final scores: " << endl;
    for (auto tiedot : tulokset){
        cout << tiedot.first << ": " << tiedot.second << endl;
    }

    input_olio.close();
    //output_olio.close();
    return EXIT_SUCCESS;
}
