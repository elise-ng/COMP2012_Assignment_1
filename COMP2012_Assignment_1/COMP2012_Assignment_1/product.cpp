//Submit this file
#include "product.h"
//You are NOT allowed to include any additional library

Product::Product(string name, ProductType type, float price) {
    this->name = name;
    this->type = type;
    this->price = price;
    this->quantity = 0;
}

string Product::getName() {
    return this->name;
}

ProductType Product::getType() {
    return this->type;
}

float Product::getPrice() {
    return this->price;
}

int Product::getQuantity() {
    return this->quantity;
}

bool Product::setPrice(float price) {
    if (price > 0) {
        this->price = price;
        return true;
    } else {
        return false;
    }
}

bool Product::setQuantity(int quantity) {
    if (quantity >= 0) {
        this->quantity = quantity;
        return true;
    } else {
        return false;
    }
}

int Product::compare(Product *other) {
    if (fabs(this->getPrice() - other->getPrice()) < 0.01f) {
        if (this->getName() > other->getName()) {
            return 1;
        } else if (this->getName() < other->getName()) {
            return -1;
        } else {
            return 0;
        }
    } else if (this->getPrice() > other->getPrice()) {
        return 1;
    } else {
        return -1;
    }
}
