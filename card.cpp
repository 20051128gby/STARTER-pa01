// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h

#include "card.h"

Card::Card() : suit('c'), rank(1) {}

Card::Card(char s, int r) : suit(s), rank(r) {}

char Card::getSuit() const {
    return this->suit;
}

int Card::getRank() const {
    return this->rank;
}

int Card::suitOrder() const {
    // clubs < diamonds < spades < hearts
    switch (suit) {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
        default:  return -1;
    }
}

bool Card::operator<(const Card& rhs) const {


    if (suitOrder() != rhs.suitOrder())
        return suitOrder() < rhs.suitOrder();

    return this->rank < rhs.rank;
}

bool Card::operator==(const Card& rhs) const {
    return this->suit == rhs.suit && this->rank == rhs.rank;
}

std::ostream& operator<<(std::ostream& out, const Card& c) {

    out << c.getSuit() << " ";

    int r = c.getRank();

    if (r == 1) out << "A";
    else if (r == 11) out << "J";
    else if (r == 12) out << "Q";
    else if (r == 13) out << "K";
    else out << r;

    return out;
}
