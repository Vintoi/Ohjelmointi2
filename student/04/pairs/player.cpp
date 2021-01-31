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
    name_(name),parit_(0)
{
}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{

    return parit_;
}

void Player::add_card(Card &card)
{
    kortit.push_back(card);
    parit_ += 1;
}

void Player::print() const
{
    std::cout<< "*** "<< name_ << " has "<< number_of_pairs() << " pair(s)." <<std::endl;
}


