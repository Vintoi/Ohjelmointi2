#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <iostream>

using namespace std;

class Player
{
public:
    Player();
    Player(string name);
    ~Player();
    string get_name();
    void add_points(int points);
    int get_points();
    bool has_won();

private:
    string name;
    int pisteet;
};

#endif // PLAYER_HH
