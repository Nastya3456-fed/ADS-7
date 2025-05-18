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
    Car* SecFirst = first;
    int carriages = 1;

    // Если поезд из одного вагона
    if (SecFirst->next == first) {
        countOp = 1;
        return 1;
    }

    // Основной алгоритм подсчета
    while (true) {
        if (!SecFirst->light) {
            SecFirst->light = true;  // Включаем свет (маркируем вагон)
            countOp++;               // Операция изменения состояния
            
            SecFirst = SecFirst->next; // Переходим к следующему вагону
            countOp++;               // Операция перехода
            carriages++;             // Увеличиваем счетчик вагонов
        } else {
            break;  // Нашли помеченный вагон
        }
    }

    // Восстанавливаем исходное состояние
    Car* current = first;
    do {
        current->light = false;
        current = current->next;
    } while (current != first);

    return carriages;
}


int Train::getOpCount() {
    return countOp;
}
