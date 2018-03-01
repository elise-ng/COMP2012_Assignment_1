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
        while (nodePtr != nullptr) {
            if (nodePtr->getShop()->getShopNumber() == shopNumber) {
                return false;
            }
            if (nodePtr->getNext() == nullptr) {
                nodePtr->setNext(newNodePtr);
            }
            nodePtr = nodePtr->getNext();
        }
    } else {
        // LL empty
        this->shopHead = newNodePtr;
    }
    return true;
}

bool Mall::removeShop(int shopNumber) {
    Node* nodePtr = this->shopHead;
    Node* prevPtr = nullptr;
    while (nodePtr != nullptr) {
        if (nodePtr->getShop()->getShopNumber() == shopNumber) {
            // Target found
            if (prevPtr == nullptr) {
                // Target is head
                this->shopHead = nodePtr->getNext();
                delete nodePtr;
                nodePtr = nullptr;
                return true;
            } else {
                // Target is not head
                prevPtr->setNext(nodePtr->getNext());
                delete nodePtr;
                nodePtr = nullptr;
                return true;
            }
        } else {
            prevPtr = nodePtr;
            nodePtr = nodePtr->getNext();
        }
    }
    return false;
}

Shop* Mall::getShop(int shopNumber) {
    Node* nodePtr = this->shopHead;
    while (nodePtr != nullptr) {
        if (nodePtr->getShop()->getShopNumber() == shopNumber) {
            return nodePtr->getShop();
        }
        nodePtr = nodePtr->getNext();
    }
    return nullptr;
}
