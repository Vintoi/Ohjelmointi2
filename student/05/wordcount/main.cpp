#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}



int main()
{
    map<string, set <int>> tulokset;

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
        string rivi,sana;
        int rivi_nro = 1;
        while (getline(input_olio,rivi)){
            vector<string> rivilta = split(rivi,' ');
            for (int i = 0; i < int(rivilta.size()); i++){
                sana = rivilta.at(i);
                if(tulokset.find(sana) != tulokset.end()){
                    tulokset[sana].insert(rivi_nro);
                } else {
                    tulokset[sana].insert(rivi_nro);
                }
            }
            rivi_nro++;
            rivilta.clear();
        }
    }
    for (auto tulos : tulokset){
        cout << tulos.first << " "<< tulos.second.size() << ": ";
        for (int kerta : tulos.second){
            tulos.second.erase(kerta);
            if (tulos.second.empty()){
                cout << kerta << endl;
            } else {
                cout <<kerta << ", ";
            }
        }
    }
}

