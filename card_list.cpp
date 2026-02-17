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
    if (c < node->card)
        insert(node->left, node, c);
    else if (node->card < c)
        insert(node->right, node, c);
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

void CardList::remove(const Card& c) {
    remove(head, c);
    if (head) head->parent = nullptr;
}

void CardList::remove(Node*& node, const Card& c) {
    if (!node) return;

    if (c < node->card) {
        remove(node->left, c);
        if (node->left) node->left->parent = node;
    }
    else if (node->card < c) {
        remove(node->right, c);
        if (node->right) node->right->parent = node;
    }
    else {
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        }
        else if (!node->left) {
            Node* temp = node;
            node = node->right;
            if (node) node->parent = temp->parent;
            delete temp;
        }
        else if (!node->right) {
            Node* temp = node;
            node = node->left;
            if (node) node->parent = temp->parent;
            delete temp;
        }
        else {
            Node* succ = node->right;
            while (succ->left) succ = succ->left;

            node->card = succ->card;

            remove(node->right, succ->card);
            if (node->right) node->right->parent = node;
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

    if (n->right)
        return leftmost(n->right);

    Node* p = n->parent;
    while (p && n == p->right) {
        n = p;
        p = p->parent;
    }
    return p;
}

CardList::Node* CardList::predecessor(Node* n) {
    if (!n) return nullptr;

    if (n->left)
        return rightmost(n->left);

    Node* p = n->parent;
    while (p && n == p->left) {
        n = p;
        p = p->parent;
    }
    return p;
}

CardList::Iterator& CardList::Iterator::operator++() {
    if (curr)
        curr = CardList::successor(curr);
    return *this;
}

CardList::Iterator& CardList::Iterator::operator--() {
    if (curr)
        curr = CardList::predecessor(curr);
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
        bool a = false;
        bool b = false;

        for (auto it = alice.begin(); it != alice.end(); ++it) {
            Card c = *it;
            if (bob.contains(c)) {
                std::cout << "Alice picked matching card " << c << std::endl;
                alice.remove(c);
                bob.remove(c);
                a = true;
                break;
            }
        }

        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            Card c = *it;
            if (alice.contains(c)) {
                std::cout << "Bob picked matching card " << c << std::endl;
                bob.remove(c);
                alice.remove(c);
                b = true;
                break;
            }
        }

        if (!a && !b) break;
    }
}
