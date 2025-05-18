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
    
    // Если поезд из одного вагона
    if (current->next == first) {
        countOp = 1;
        return 1;
    }
    
    // Включаем лампочку в первом вагоне
    current->light = true;
    countOp++;
    
    // Переходим к следующему вагону
    current = current->next;
    countOp++;
    int length = 1;
    
    // Идем по кругу, пока не найдем включенную лампочку
    while (!current->light) {
        length++;
        current->light = true;  // Включаем лампочку
        countOp++;
        current = current->next; // Переходим дальше
        countOp++;
    }
    
    // Восстанавливаем исходное состояние
    current = first;
    do {
        current->light = false;
        current = current->next;
    } while (current != first);
    
    return length;
}


int Train::getOpCount() {
    return countOp;
}
