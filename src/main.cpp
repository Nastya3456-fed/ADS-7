// Copyright 2022 NNTU-CS
#include <iostream>
#include "train.h"
#include <cstdint>

void testTrain(int n, int mo, int& st, int64_t& mic);
void testTrain(int n, int mo, int& st, int64_t& mic) {
    st = 0;    
    mic = 0;   
}

int main() {
    std::cout << "dlinna,Reshim,Shagi,Vrema(ms)" << std::endl;
    for (int n = 10; n <= 100; n += 10) {
        for (int mo = 0; mo <= 2; ++mo) {
            int st;
            int64_t mic;
            testTrain(n, mo, st, mic);
            std::cout << n << "," << mo << "," << st << "," << mic << std::endl;
        }
    }
    return 0;
}
