#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "card.h"
#include "card_list.h"

using namespace std;

static bool parseLine(const string& line, Card& out) {
    string s, r;
    stringstream ss(line);
    ss >> s >> r;
    if (!ss) return false;

    char suit = s[0];
    int rank = 0;

    if (r.size() == 1) {
        char c = r[0];
        if (c == 'A' || c == 'a') rank = 1;
        else if (c == 'J' || c == 'j') rank = 11;
        else if (c == 'Q' || c == 'q') rank = 12;
        else if (c == 'K' || c == 'k') rank = 13;
        else if (c >= '2' && c <= '9') rank = c - '0';
        else return false;
    } else {
        rank = stoi(r);
    }

    out = Card(suit, rank);
    return true;
}

static void readAll(const char* name, CardList& hand, vector<Card>& order) {
    ifstream in(name);
    string line;
    while (getline(in, line) && line.length() > 0) {
        Card c;
        if (parseLine(line, c)) {
            hand.insert(c);
            order.push_back(c);
        }
    }
}

static bool aliceTurn(CardList& alice, CardList& bob, const vector<Card>& order) {
    for (size_t i = 0; i < order.size(); i++) {
        const Card& c = order[i];
        if (alice.contains(c) && bob.contains(c)) {
            cout << "Alice picked matching card " << c << endl;
            alice.remove(c);
            bob.remove(c);
            return true;
        }
    }
    return false;
}

static bool bobTurn(CardList& bob, CardList& alice, const vector<Card>& order) {
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        const Card& c = order[i];
        if (bob.contains(c) && alice.contains(c)) {
            cout << "Bob picked matching card " << c << endl;
            bob.remove(c);
            alice.remove(c);
            return true;
        }
    }
    return false;
}

int main(int argv, char** argc) {
    if (argv < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream f1(argc[1]), f2(argc[2]);
    if (f1.fail() || f2.fail()) {
        cout << "Could not open file " << (f1.fail() ? argc[1] : argc[2]) << endl;
        return 1;
    }
    f1.close();
    f2.close();

    CardList alice, bob;
    vector<Card> aOrder, bOrder;

    readAll(argc[1], alice, aOrder);
    readAll(argc[2], bob, bOrder);

    while (true) {
        bool a = aliceTurn(alice, bob, aOrder);
        bool b = bobTurn(bob, alice, bOrder);
        if (!a && !b) break;
    }

    cout << "\nAlice's cards:\n";
    alice.print();
    cout << "\nBob's cards:\n";
    bob.print();

    return 0;
}
