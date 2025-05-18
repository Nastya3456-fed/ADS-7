// Copyright 2022 NNTU-CS
#include <iostream>
#include "train.h"
#include <cstdint>
#include <chrono>
#include <random>

int main() {
    std::cout << "Dlina,Reshim,DlinaPoezda,Shagi,Vremia" << std::endl;

    for (int n = 1; n <= 140; n += 9) {
        for (int mode = 0; mode <= 2; ++mode) {
            Train train;

            // Заполнение поезда в зависимости от режима
            if (mode == 0) {
                // все лампочки выключены
                for (int i = 0; i < n; ++i)
                    train.addCar(false);
            }
            else if (mode == 1) {
                // все лампочки включены
                for (int i = 0; i < n; ++i)
                    train.addCar(true);
            }
            else if (mode == 2) {
                // случайное распределение лампочек
                std::random_device rd;
                std::mt19937 gen(rd());
                std::bernoulli_distribution d(0.5);

                for (int i = 0; i < n; ++i)
                    train.addCar(d(gen));
            }

            try {
                // Засекаем время
                auto start = std::chrono::steady_clock::now();

                int length = train.getLength();

                // Засекаем конец времени
                auto end = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                int steps = train.getOpCount();

                std::cout << n << "," << mode << "," << length << "," << steps << "," << duration << std::endl;
            }
            catch (const std::logic_error& e) {
                std::cout << n << "," << mode << ",ERROR,0,0" << std::endl;
            }
        }
    }

    return 0;
}
