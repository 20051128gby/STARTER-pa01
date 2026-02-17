// card_list.cpp
// Author: Your name
// Implementation of the classes defined in card_list.h

#include "card_list.h"

CardList::CardList() : head(nullptr) {}

CardList::~CardList() {
    clear(head);
    head = nullptr;
}

void CardList::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void CardList::insert(const Card& c) {
    insert(head, nullptr, c);
}

void CardList::insert(Node*& node, Node* parent, const Card& c) {
    if (!node) {
        node = new Node(c, parent);
        return;
    }
    if (c < node->card) insert(node->left, node, c);
    else if (node->card < c) insert(node->right, node, c);
}

bool CardList::contains(const Card& c) const {
    return contains(head, c);
}

bool CardList::contains(Node* node, const Card& c) const {
    if (!node) return false;
    if (c < node->card) return contains(node->left, c);
    if (node->card < c) return contains(node->right, c);
    return true;
}

static void linkParent(CardList::Node* child, CardList::Node* parent) {
    if (child) child->parent = parent;
}

void CardList::remove(const Card& c) {
    remove(head, c);
    if (head) head->parent = nullptr;
}

void CardList::remove(Node*& node, const Card& c) {
    if (!node) return;

    if (c < node->card) {
        remove(node->left, c);
        linkParent(node->left, node);
    } else if (node->card < c) {
        remove(node->right, c);
        linkParent(node->right, node);
    } else {
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (!node->left) {
            Node* t = node;
            node = node->right;
            linkParent(node, t->parent);
            delete t;
        } else if (!node->right) {
            Node* t = node;
            node = node->left;
            linkParent(node, t->parent);
            delete t;
        } else {
            Node* s = leftmost(node->right);
            node->card = s->card;
            remove(node->right, s->card);
            linkParent(node->right, node);
        }
    }
}

void CardList::print() const {
    print(head);
}

void CardList::print(Node* node) const {
    if (!node) return;
    print(node->left);
    std::cout << node->card << std::endl;
    print(node->right);
}

CardList::Node* CardList::leftmost(Node* n) {
    if (!n) return nullptr;
    while (n->left) n = n->left;
    return n;
}

CardList::Node* CardList::rightmost(Node* n) {
    if (!n) return nullptr;
    while (n->right) n = n->right;
    return n;
}

CardList::Node* CardList::successor(Node* n) {
    if (!n) return nullptr;
    if (n->right) return leftmost(n->right);
    Node* p = n->parent;
    while (p && n == p->right) {
        n = p;
        p = p->parent;
    }
    return p;
}

CardList::Node* CardList::predecessor(Node* n) {
    if (!n) return nullptr;
    if (n->left) return rightmost(n->left);
    Node* p = n->parent;
    while (p && n == p->left) {
        n = p;
        p = p->parent;
    }
    return p;
}

CardList::Iterator& CardList::Iterator::operator++() {
    if (curr) curr = CardList::successor(curr);
    return *this;
}

CardList::Iterator& CardList::Iterator::operator--() {
    if (curr) curr = CardList::predecessor(curr);
    return *this;
}

CardList::Iterator CardList::begin() const {
    return Iterator(leftmost(head), this);
}

CardList::Iterator CardList::end() const {
    return Iterator(nullptr, this);
}

CardList::Iterator CardList::rbegin() const {
    return Iterator(rightmost(head), this);
}

CardList::Iterator CardList::rend() const {
    return Iterator(nullptr, this);
}

void playGame(CardList& alice, CardList& bob) {
    while (true) {
        bool ap = false, bp = false;

        for (auto it = alice.begin(); it != alice.end(); ++it) {
            Card c = *it;
            if (bob.contains(c)) {
                std::cout << "Alice picked matching card " << c << std::endl;
                alice.remove(c);
                bob.remove(c);
                ap = true;
                break;
            }
        }

        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            Card c = *it;
            if (alice.contains(c)) {
                std::cout << "Bob picked matching card " << c << std::endl;
                bob.remove(c);
                alice.remove(c);
                bp = true;
                break;
            }
        }

        if (!ap && !bp) break;
    }
}
