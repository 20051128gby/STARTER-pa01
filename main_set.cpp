// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
    if(argv < 3){
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argc[1]);
    ifstream cardFile2(argc[2]);
    string line;

    if(cardFile1.fail() || cardFile2.fail()){
        cout << "Could not open file " << (cardFile1.fail() ? argc[1] : argc[2]) << endl;
        return 1;
    }

    set<Card> alice;
    set<Card> bob;

    char suit;
    string rankStr;

    while(getline(cardFile1, line) && line.length() > 0){
        stringstream ss(line);
        ss >> suit >> rankStr;
        int rank;
        if(rankStr == "a") rank = 1;
        else if(rankStr == "j") rank = 11;
        else if(rankStr == "q") rank = 12;
        else if(rankStr == "k") rank = 13;
        else rank = stoi(rankStr);
        alice.insert(Card(suit, rank));
    }
    cardFile1.close();

    while(getline(cardFile2, line) && line.length() > 0){
        stringstream ss(line);
        ss >> suit >> rankStr;
        int rank;
        if(rankStr == "a") rank = 1;
        else if(rankStr == "j") rank = 11;
        else if(rankStr == "q") rank = 12;
        else if(rankStr == "k") rank = 13;
        else rank = stoi(rankStr);
        bob.insert(Card(suit, rank));
    }
    cardFile2.close();

    while(true){
        bool alicePicked = false;
        bool bobPicked = false;

        for(auto it = alice.begin(); it != alice.end(); ++it){
            auto picked = bob.find(*it);
            if(picked != bob.end()){
                cout << "Alice picked matching card " << *it << endl;
                Card matched = *it;
                alice.erase(it);
                bob.erase(picked);
                alicePicked = true;
                break;
            }
        }

        for(auto rit = bob.rbegin(); rit != bob.rend(); ++rit){
            auto picked = alice.find(*rit);
            if(picked != alice.end()){
                cout << "Bob picked matching card " << *rit << endl;
                Card matched = *rit;
                bob.erase(matched);
                alice.erase(picked);
                bobPicked = true;
                break;
            }
        }

        if(!alicePicked && !bobPicked) break;
    }

    cout << endl;
    cout << "Alice's cards:" << endl;
    for(const auto& c : alice) cout << c << endl;
    cout << endl;
    cout << "Bob's cards:" << endl;
    for(const auto& c : bob) cout << c << endl;

    return 0;
}
