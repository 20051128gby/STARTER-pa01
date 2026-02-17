// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h

#include "card.h"

Card::Card() : suit('c'), rank(1) {}
Card::Card(char s, int r) : suit(s), rank(r) {}

char Card::getSuit() const { return suit; }
int Card::getRank() const { return rank; }

int Card::suitOrder() const {
    switch (suit) {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
        default:  return -1;
    }
}

bool Card::operator<(const Card& rhs) const {
    int a = suitOrder(), b = rhs.suitOrder();
    if (a != b) return a < b;
    return rank < rhs.rank;
}

bool Card::operator==(const Card& rhs) const {
    return suit == rhs.suit && rank == rhs.rank;
}

bool Card::operator>(const Card& rhs) const {
    return rhs < *this;
}

std::ostream& operator<<(std::ostream& out, const Card& c) {
    out << c.getSuit() << " ";
    int r = c.getRank();
    if (r == 1) out << "a";
    else if (r == 11) out << "j";
    else if (r == 12) out << "q";
    else if (r == 13) out << "k";
    else out << r;
    return out;
}
