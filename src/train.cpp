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
    
    // Специальный алгоритм для определения длины
    // с использованием только одной "метки" (лампочки)
    
    // 1. Включаем лампочку в стартовом вагоне
    current->light = true;
    countOp++;
    
    // 2. Начинаем движение по кругу
    int length = 0;
    while (true) {
        // Переходим к следующему вагону
        current = current->next;
        countOp++;
        length++;
        
        // Проверяем состояние лампочки
        if (current->light) {
            // Нашли помеченный вагон - завершаем подсчет
            current->light = false; // Восстанавливаем исходное состояние
            countOp++;
            break;
        }
        
        // Если лампочка выключена, включаем ее
        current->light = true;
        countOp++;
    }
    
    return length;
}


int Train::getOpCount() {
    return countOp;
}
