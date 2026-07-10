#include <iostream>
#include <chrono>
#include "../include/tensor.h"
#include "../include/tensor_test.h"

int main() {
    Tensor t1 = Tensor(100000, 5000);
    Tensor t2 = Tensor(100000, 5000);
    Tensor t3 = Tensor(100000, 5000);

    DataGeneration(t1);
    DataGeneration(t2);

    auto start = std::chrono::high_resolution_clock::now();

    t3 = t1 + t2;

    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "TIME : " << us.count() / 1000.0 << " ms";

    std::cout << "\n";
    return 0;
}