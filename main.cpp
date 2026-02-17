#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "card.h"
#include "card_list.h"

using namespace std;

static bool parseCard(const string& line, Card& out) {
    string s, r;
    stringstream ss(line);
    ss >> s >> r;
    if (!ss) return false;

    char suit = s[0];
    int rank = 0;

    if (r.size() == 1) {
        char c = r[0];
        if (c == 'a' || c == 'A') rank = 1;
        else if (c == 'j' || c == 'J') rank = 11;
        else if (c == 'q' || c == 'Q') rank = 12;
        else if (c == 'k' || c == 'K') rank = 13;
        else if (c >= '2' && c <= '9') rank = c - '0';
        else return false;
    } else {
        rank = stoi(r);
    }

    out = Card(suit, rank);
    return true;
}

static void readFile(const char* name, CardList& hand) {
    ifstream in(name);
    string line;
    while (getline(in, line) && line.length() > 0) {
        Card c;
        if (parseCard(line, c)) hand.insert(c);
    }
}

int main(int argv, char** argc) {
    if (argv < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream a(argc[1]), b(argc[2]);
    if (a.fail() || b.fail()) {
        cout << "Could not open file " << (a.fail() ? argc[1] : argc[2]) << endl;
        return 1;
    }
    a.close();
    b.close();

    CardList alice, bob;
    readFile(argc[1], alice);
    readFile(argc[2], bob);

    playGame(alice, bob);

    cout << "\nAlice's cards:\n";
    alice.print();
    cout << "\nBob's cards:\n";
    bob.print();

    return 0;
}
