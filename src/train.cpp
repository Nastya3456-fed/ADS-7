// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;
    Train::Car* cur = first->next;
    while (cur != first) {
        Train::Car* next = cur->next;
        delete cur;
        cur = next;
    }
    delete first;
}

void Train::addCar(bool light) {
    Train::Car* car = new Train::Car;
    car->light = light;
    car->next = nullptr;
    car->prev = nullptr;

    if (!first) {
        first = car;
        first->next = first;
        first->prev = first;
    }
    else {
        Train::Car* last = first->prev;
        last->next = car;
        car->prev = last;
        car->next = first;
        first->prev = car;
    }
}

int Train::getLength() {
    if (!first) throw std::logic_error("Train is empty!");
    
    countOp = 0;
    Car* current = first;
    
    if (current->next == first) {
        countOp = 1;
        return 1;
    }
    
    current->light = true;
    countOp++;
    
    current = current->next;
    countOp++;
    
    int length = 1;
    
    while (current != first) {
        length++;
        
        if (current->light) {
            break;
        }
        
        current->light = true;
        countOp++;
        
        current = current->next;
        countOp++;
    }
    
    return length;
}


int Train::getOpCount() {
    return countOp;
}
