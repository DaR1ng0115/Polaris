#include <iostream>
#include "../include/tensor.h"

int main() {
    Tensor t1(2, 3);
    Tensor t2(2, 3);
    Tensor t3(2, 3);

    for(int i=0; i<6; ++i) {
        t1.data()[i] = i+1;
        t2.data()[i] = 2*i;
    }

    t3 = t1 + t2;

    for(int i=0; i<6; ++i) {
        std::cout << t3.data()[i] << " ";
        std::cout << "\n";
    }
    return 0;
}