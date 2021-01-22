#include "Player.hh"

Player::Player()
{
}

Player::Player(string name):
name(name),pisteet(0){

}

Player::~Player()
{

}

string Player::get_name()
{
    return name;
}

void Player::add_points(int points)
{
    if (pisteet + points > 50){
        pisteet = 25;
    } else {
        pisteet += points;
    }
}

int Player::get_points()
{
    return pisteet;
}

bool Player::has_won()
{
    if (pisteet == 50){
        return true;
    } else {
        return false;
    }
}



