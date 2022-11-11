/* Mastermind
 * Program author
 * Name: Mai Nguyen
 * Student number: 50358236
 * UserID: ddmang
 * E-Mail: mai.n.nguyen@tuni.fi
 * */
#include "colors.hh"
#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Colors::Colors(vector <char> color_series) :
    series_(color_series) {
}


string Colors::print_series() const {
    string printed = "";
    for (unsigned i = 0; i < series_.size(); ++i)
    {
        char character = toupper(series_[i]);
        printed = printed + ' ' + character;
    }
    return printed;
}

vector <char> Colors::get_series() {
    return series_;
}



