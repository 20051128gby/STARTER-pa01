// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card {
public:
    Card();
    Card(char s, int r);

    char getSuit() const;
    int getRank() const;

    bool operator<(const Card& rhs) const;
    bool operator==(const Card& rhs) const;
    bool operator>(const Card& rhs) const;

private:
    char suit;
    int rank;

    int suitOrder() const;
};

std::ostream& operator<<(std::ostream& out, const Card& c);

#endif
