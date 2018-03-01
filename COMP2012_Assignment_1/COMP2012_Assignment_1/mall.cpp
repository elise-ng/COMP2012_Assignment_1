//Submit this file
#include "mall.h"
//You are NOT allowed to include any additional library

//NOTE: Mall::duplicateShopLinkedList must NOT be implemented here

Mall::Mall(string name, string address) {
    this->name = name;
    this->address = address;
    this->shopHead = nullptr;
}

Mall::Mall(Mall& another) {
    this->name = another.name;
    this->address = another.address;
    this->shopHead = Mall::duplicateShopLinkedList(another.shopHead);
}

Mall::~Mall() {
    Node* current = this->shopHead;
    while (current != nullptr) {
        Node* next = current->getNext();
        delete current;
        current = next;
    }
    this->shopHead = nullptr;
}

void Mall::setName(string name) {
    this->name = name;
}

void Mall::setAddress(string address) {
    this->address = address;
}

string Mall::getName() {
    return this->name;
}

string Mall::getAddress() {
    return this->address;
}

bool Mall::addShop(string name, int shopNumber) {
    Shop* newShopPtr = new Shop(name, shopNumber);
    Node* newNodePtr = new Node(newShopPtr, nullptr);
    Node* nodePtr = this->shopHead;
    if (nodePtr != nullptr) {
        // LL not empty
        for (; nodePtr->getNext() != nullptr; nodePtr = nodePtr->getNext()) {
            if (nodePtr->getShop()->getShopNumber() == shopNumber) {
                return false;
            }
        }
        nodePtr->setNext(newNodePtr);
    } else {
        // LL empty
        this->shopHead = newNodePtr;
    }
    return true;
}

bool Mall::removeShop(int shopNumber) {
    Node* nodePtr = this->shopHead;
    if (nodePtr != nullptr) {
        // LL not empty
        // Item 0
        if (nodePtr->getShop()->getShopNumber() == shopNumber) {
            delete nodePtr;
            this->shopHead = nullptr;
            return true;
        }
        // For item 1 to n-2
        for (; nodePtr->getNext() != nullptr && nodePtr->getNext()->getNext() != nullptr; nodePtr = nodePtr->getNext()) {
            // If item i+1 is target, delete item 1+1, update item i
            if (nodePtr->getNext()->getShop()->getShopNumber() == shopNumber) {
                delete nodePtr->getNext();
                nodePtr->setNext(nullptr);
                return true;
            }
        }
    }
    return false;
}

Shop* Mall::getShop(int shopNumber) {
    for (Node* nodePtr = this->shopHead; nodePtr->getNext() != nullptr; nodePtr = nodePtr->getNext()) {
        if (nodePtr->getShop()->getShopNumber() == shopNumber) {
            return nodePtr->getShop();
        }
    }
    return nullptr;
}
