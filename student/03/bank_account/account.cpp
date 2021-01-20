#include "account.hh"
#include <iostream>
#include <string>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit), saldo_(0), credit_limit_(0)
{
    generate_iban();
}


// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int raha){
    if (has_credit_ == true){
    credit_limit_ = credit_limit_ -raha;
    } else {
        cout << "Cannot set credit limit: the account has no credit card" <<endl;
    }
}

void Account::print() const{
    cout << "" << owner_ << " : " << iban_ << " : " << saldo_ << " euros" << endl;
    cout << "credit limit: " << credit_limit_ << endl;
}

void Account::save_money(int raha){
    saldo_ += raha;
}

void Account::take_money(int raha){
    if (this->credit_limit_ == true && saldo_-raha < credit_limit_ ){
        cout <<"Cannot take money: credit limit overflow" <<endl;
        cout << "Transfer from " << iban_ << " failed" <<endl;
    } else if (has_credit_ == true && saldo_-raha > credit_limit_){
        saldo_ -= raha;
    } else if (credit_limit_ == false){
        if(saldo_-raha < 0) {
            cout << "Cannot take money: balance underflow" << endl;
        } else {
            saldo_ -= raha;
            cout << raha << " euros taken: new balance of " << iban_ << " is "<<saldo_ << endl;
        }
    }
}

void Account::transfer_to(Account &acc, int raha){
    if(has_credit_ == true && saldo_-raha < credit_limit_){
        this->take_money(raha);
    } else if (has_credit_ == true && saldo_-raha >credit_limit_){
        this->take_money(raha);
        acc.saldo_ += raha;

    } else if (has_credit_ ==false){
        if(saldo_-raha < 0){
            cout << "Cannot take money: credit limit overflow" <<endl;
            cout << "Transfer from " << iban_ << " failed" << endl;
        } else {
            this->take_money(raha);
            acc.saldo_ += raha;
        }
    }
}
