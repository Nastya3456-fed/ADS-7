// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : first(nullptr), countOp(0) {}

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
    countOp = 0;
    while (true) {
        Car* SecFirst = first;
        int carriages = 1;
        if (!SecFirst->light) {
            SecFirst->light = true;
            SecFirst = SecFirst->next;
            countOp += 2;
        }
        while (!SecFirst->light) {
            SecFirst = SecFirst->next;
            countOp += 2;
            ++carriages;
        }
        SecFirst->light = false;
        if (!first->light)
            return carriages;
    }
}

int Train::getOpCount() {
    return countOp;
}
