//Submit this file
#include "shop.h"
//You are NOT allowed to include any additional library

Shop::Shop(string name, int shopNumber) {
    this->name = name;
    this->shopNumber = shopNumber;
    this->products = nullptr;
    this->productCount = 0;
}

Shop::Shop(Shop& another) {
    this->name = another.name;
    this->shopNumber = another.shopNumber;
    this->products = new Product* [another.productCount];
    for (int i = 0; i < another.productCount; i++) {
        this->products[i] = new Product(*(another.products[i]));
    }
    this->productCount = another.productCount;
}

Shop::~Shop() {
    for (int i = 0; i < this->productCount; i++) {
        delete this->products[i];
        this->products[i] = nullptr;
    }
    delete[] this->products;
    this->products = nullptr;
}

string Shop::getName() {
    return this->name;
}

int Shop::getShopNumber() {
    return this->shopNumber;
}

void Shop::setName(string name) {
    this->name = name;
}

void Shop::setShopNumber(int shopNumber) {
    this->shopNumber = shopNumber;
}

void Shop::addProduct(string name, ProductType type, float price, int quantityToAdd) {
    for (int i = 0; i < this->productCount; i++) {
        if (this->products[i]->getName() == name) {
            this->products[i]->setQuantity(this->products[i]->getQuantity() + quantityToAdd);
            return;
        }
    }
    // Product is new
    // Create new product object
    Product* newProductPtr = new Product(name, type, price);
    newProductPtr->setQuantity(quantityToAdd);
    // Create new product array
    Product** newProducts = new Product* [this->productCount + 1];
    int newProductCount = 0;
    // Copy and insert new product
    for (int i = 0; i < this->productCount; i++) {
        if (newProductPtr->compare(this->products[i]) == -1) {
            // new product smaller than product[i], insert before product[i]
            newProducts[newProductCount] = newProductPtr;
            newProductCount += 1;
        }
        newProducts[newProductCount] = this->products[i];
        newProductCount += 1;
    }
    // Delete old array
    delete[] this->products;
    // Update values
    this->products = newProducts;
    this->productCount = newProductCount;
}

bool Shop::removeProduct(string name, int quantityToRemove) {
    if (quantityToRemove <= 0) { return false; }
    bool shouldRemoveTarget = false;
    for (int i = 0; i < this->productCount; i++) {
        if (this->products[i]->getName() == name) {
            Product* target = this->products[i];
            if (target->getQuantity() < quantityToRemove) {
                return false;
            }
            target->setQuantity(target->getQuantity() - quantityToRemove);
            if (target->getQuantity() == 0) {
                shouldRemoveTarget = true;
                // delay return
            } else {
                return true;
            }
        }
    }
    if (shouldRemoveTarget) {
        // Create new product array
        Product** newProducts = new Product* [this->productCount - 1];
        int newProductCount = 0;
        // Copy and remove target
        for (int i = 0; i < this->productCount; i++) {
            if (this->products[i]->getQuantity() == 0) {
                // target found, proceed to delete
                delete this->products[i];
                this->products[i] = nullptr;
                continue;
            }
            newProducts[newProductCount] = this->products[i];
            newProductCount += 1;
        }
        // Delete old array
        delete[] this->products;
        // Update values
        this->products = newProducts;
        this->productCount = newProductCount;
        return true;
    } else {
        // search found nothing
        return false;
    }
}

Product* Shop::findProduct(string name) {
    for (int i = 0; i < this->productCount; i++) {
        if (this->products[i]->getName() == name) {
            return this->products[i];
        }
    }
    return nullptr;
}

bool Shop::updatePrice(string name, float price) {
    if (price <= 0) { return false; }
    // search for target, find original index
    int originalIndex = -1;
    for (int i = 0; i < this->productCount; i++) {
        if (this->products[i]->getName() == name) {
            this->products[i]->setPrice(price);
            originalIndex = i;
            break;
        }
    }
    // not found
    if (originalIndex == -1) { return false; }
    // find new index
    int newIndex = -1;
    for (int i = 0; i < this->productCount; i++) {
        if (this->products[originalIndex]->compare(this->products[i]) == -1) {
            newIndex = i;
            break;
        }
    }
    // reinsert target if index changed
    if (originalIndex != newIndex) {
        Product* tempProductPtr = nullptr;
        if (originalIndex < newIndex) {
            for (int i = originalIndex; i <= newIndex; i++) {
                tempProductPtr = this->products[i];
                this->products[i] = this->products[i+1];
                this->products[i+1] = tempProductPtr;
            }
        } else { // originalIndex > newIndex
            for (int i = originalIndex; i >= newIndex; i--) {
                tempProductPtr = this->products[i];
                this->products[i] = this->products[i-1];
                this->products[i-1] = tempProductPtr;
            }
        }
    }
    return true;
}
