// card_list.cpp
// Author: Your name
// Implementation of the classes defined in card_list.h

#include "card_list.h"

CardList::CardList() : head(nullptr) {}
CardList::~CardList() {
    clear(head);
    head = nullptr;
}

void CardList::insert(const Card& c) {
    insert(head, c);
}

void CardList::remove(const Card& c) {
    remove(head, c);
}

bool CardList::contains(const Card& c) const {
    return contains(head, c);
}

void CardList::print() const {
    print(head);
}

void CardList::insert(Node*& node, const Card& c) {
    if (node == nullptr) {
        node = new Node(c);
    } else if (c < node->card) {
        insert(node->left, c);
    } else if (node->card < c) {
        insert(node->right, c);
    }
}

void CardList::remove(Node*& node, const Card& c) {
    if (node == nullptr) return;

    if (c < node->card) {
        remove(node->left, c);
    } else if (node->card < c) {
        remove(node->right, c);
    } else {
        if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->card = temp->card;
            remove(node->right, temp->card);
        }
    }
}

bool CardList::contains(Node* node, const Card& c) const {
    if (node == nullptr) return false;

    if (c < node->card) {
        return contains(node->left, c);
    } else if (node->card < c) {
        return contains(node->right, c);
    } else {
        return true;
    }
}

void CardList::print(Node* node) const {
    if (node != nullptr) {
        print(node->left);
        std::cout << node->card << std::endl;
        print(node->right);
    }
}

void CardList::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}