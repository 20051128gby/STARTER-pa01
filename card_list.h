// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include "card.h"

class CardList {
private:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c, Node* p) : card(c), left(nullptr), right(nullptr), parent(p) {}
    };

    Node* head;

    void clear(Node* node);
    void print(Node* node) const;

    void insert(Node*& node, Node* parent, const Card& c);
    void remove(Node*& node, const Card& c);
    bool contains(Node* node, const Card& c) const;

    static Node* leftmost(Node* n);
    static Node* rightmost(Node* n);
    static Node* successor(Node* n);
    static Node* predecessor(Node* n);

public:
    CardList();
    ~CardList();

    void insert(const Card& c);
    void remove(const Card& c);
    bool contains(const Card& c) const;
    void print() const;

    class Iterator {
    private:
        Node* curr;
        const CardList* owner;
    public:
        Iterator(Node* c = nullptr, const CardList* o = nullptr) : curr(c), owner(o) {}

        const Card& operator*() const { return curr->card; }
        const Card* operator->() const { return &(curr->card); }

        Iterator& operator++();
        Iterator& operator--();

        bool operator==(const Iterator& rhs) const { return curr == rhs.curr; }
        bool operator!=(const Iterator& rhs) const { return curr != rhs.curr; }
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

void playGame(CardList& alice, CardList& bob);

#endif
