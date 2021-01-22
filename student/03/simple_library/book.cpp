#include "book.hh"
#include "date.hh"

#include <iostream>
#include <string>

using namespace std;

Book::Book(string tekija, string nimi):
    tekija_(tekija),nimi_(nimi),lainassa_(false),lainauspaiva(),palautuspaiva(){
}
Book::~Book()
{
}

void Book::print()
{
    cout << tekija_ << " : "<< nimi_ << endl;
    if (lainassa_ == false){
        cout << "- available" << endl;
    } else {
        cout << "- loaned: ";
        lainauspaiva.print();
        cout << "- to be returned: ";
        palautuspaiva.print();
    }
}

void Book::loan(Date paiva)
{
    if (lainassa_ == true){
        cout << "Already loaned: cannot be loaned" << endl;
    } else {
        lainassa_ = true;
        lainauspaiva = paiva;
        palautuspaiva = paiva;
        palautuspaiva.advance(28);
    }
}

void Book::renew()
{
    if (lainassa_ == true){
        palautuspaiva.advance(28);
    } else {
        cout << "Not loaned: cannot be renewed" << endl;
    }
}

void Book::give_back()
{
    lainassa_ = false;
}


