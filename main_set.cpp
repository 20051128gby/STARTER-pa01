// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"
#include <sstream>
using namespace std;
int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  } 
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;
  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
set<Card> alice;
set<Card> bob;
char suit;
string rankStr;
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    stringstream ss(line);
    ss >> suit >> rankStr;
    int rank;
    if (rankStr == "a") rank = 1;
    else if (rankStr == "j") rank = 11;
    else if (rankStr == "q") rank = 12;
    else if (rankStr == "k") rank = 13;
    else rank = stoi(rankStr);
    bob.insert(Card(suit, rank));
  }
  cardFile1.close();
  while (getline (cardFile2, line) && (line.length() > 0)){
    stringstream ss(line);
    ss >> suit >> rankStr;
    int rank;
    if (rankStr == "a") rank = 1;
    else if (rankStr == "j") rank = 11;
    else if (rankStr == "q") rank = 12;
    else if (rankStr == "k") rank = 13;
    else rank = stoi(rankStr);
    alice.insert(Card(suit, rank));
  }
  cardFile2.close();
    while (true) {
        bool alicePicked = false;
        bool bobPicked = false;
        //Alice
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            auto Picked = bob.find(*it);
            if (Picked != bob.end()) {
                cout << "Alice picked matching card " << *it << endl; 
                Card matched = *it;
                alice.erase(it);
                bob.erase(Picked);
                alicePicked = true;
                break;
            }
        }
        //Bob
        for (auto rit = bob.rbegin(); rit != bob.rend(); ++rit) {
            auto Picked = alice.find(*rit);
            if (Picked != alice.end()) {
                cout << "Bob picked matching card " << *rit << endl; 
                Card matched = *rit;
                bob.erase(matched);
                alice.erase(Picked);
                bobPicked = true;
                break;
            }
        }
        if (!alicePicked && !bobPicked) break;
    }
    cout << endl;
    cout << "Alice's cards:" << endl;
    for (const auto& c : alice) cout << c << endl;
    cout << "Bob's cards:" << endl;
    for (const auto& c : bob) cout << c << endl;
    return 0;
}
