#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main()
{
    string input_file = "";
    cout << "Input file :";
    getline(cin, input_file);
    string output_file;
    cout << "Output file :";
    getline(cin, output_file);

    ifstream input_olio;
    ofstream output_olio;

    input_olio.open(input_file);
    if (!input_olio){
        output_olio.close();
        cout << "Error! The File " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        int rivinumero = 1;
        string rivi;
        while(getline(input_olio,rivi)){
            output_olio << rivinumero << " " << rivi <<endl;
            rivinumero++;
        }
    }

    output_olio.close();
    input_olio.close();
    return EXIT_SUCCESS;
}
