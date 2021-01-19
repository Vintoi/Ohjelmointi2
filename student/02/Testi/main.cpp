#include <iostream>

using namespace std;

int main()
{
    string hello = "Hello World!";
    string::size_type kohta = 0;
    kohta = hello.find("e");


    for (unsigned int i = 0; i < hello.length(); ++i){
        cout << hello.at(i) << endl;
        kohta = hello.find(hello.at(i));
        if(kohta != string::npos){
            cout << kohta << endl;
        }

    }
    return 0;
}
