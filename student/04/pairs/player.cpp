#include "player.hh"
#include "card.hh"
#include <string>
#include <vector>
#include <iostream>

// Lisää luokan toteutus tähän.
// Kuhunkin julkiseen metodiin pitäisi riittää 1-2 koodiriviä.

// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.

Player::Player(const std::string &name):
    name_(name),parit_(kortit.size())
{

}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return kortit.size();
}

void Player::add_card(Card &card)
{
    kortit.push_back(card);
}

void Player::print() const
{
    std::cout<< "*** "<< name_ << " has "<< parit_ << " pair(s)" <<std::endl;
}


