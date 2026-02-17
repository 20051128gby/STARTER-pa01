// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include <iostream>
#include <string>
#include "card.h"
class CardList {

public:
    CardList();
    ~CardList();

    void insert(const Card& c);
    void remove(const Card& c);
    bool contains(const Card& c) const;
    void print() const;


private:
    struct Node {
        Card card;
        Node* left;
        Node* right;

        Node(const Card& c) : card(c), left(nullptr), right(nullptr) {}
    };

    Node* head;

    void insert(Node*& node, const Card& c);
    void remove(Node*& node, const Card& c);
    bool contains(Node* node, const Card& c) const;
    void print(Node* node) const;
    void clear(Node* node);

};



#endif
