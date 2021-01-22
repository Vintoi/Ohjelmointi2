#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include <iostream>
#include <date.hh>

using namespace std;

class Book
{
public:

    Book();
    Book(string tekija, string nimi);
    ~Book();
    void print();
    void loan(Date paiva);
    void renew();
    void give_back();

private:
    string tekija_;
    string nimi_;
    bool lainassa_;
    Date lainauspaiva;
    Date palautuspaiva;
};
#endif // BOOK_HH
