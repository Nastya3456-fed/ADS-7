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

        if (SecFirst->light) {        // Если у первой вагонки свет включен
            SecFirst = SecFirst->next;// Переходим к следующей вагонетке
            countOp += 2;             // Учитываем операции (смотри ниже)
        }else{  // Если у первой вагонки свет выключен (false)
            SecFirst->light = true; // Включаем свет (ставим метку)
            SecFirst = SecFirst->next;
            countOp += 2;
        }

        while (!SecFirst->light) { // Пока свет выключен у текущей вагонки
            SecFirst = SecFirst->next;
            countOp += 2;
            ++carriages;
        }
        SecFirst->light = false;   // Выключаем свет у текущей вагонки (сбрасываем метку)

        if (!first->light)
            return carriages;   // Если у первой вагонки свет теперь выключен
    }
}

int Train::getOpCount() {
    return countOp;
}
