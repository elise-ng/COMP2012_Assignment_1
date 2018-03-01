//Submit this file
#include "node.h"
//You are NOT allowed to include any additional library

Node::Node(Shop* shop, Node* next) {
    this->shop = shop;
    this->next = next;
}

Node::~Node() {
    delete this->shop;
    this->shop = nullptr;
}

Shop* Node::getShop() {
    return this->shop;
}

Node* Node::getNext() {
    return this->next;
}

void Node::setShop(Shop *shop) {
    this->shop = shop;
}

void Node::setNext(Node *node) {
    this->next = node;
}
