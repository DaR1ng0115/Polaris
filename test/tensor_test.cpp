//
// tensor_test.cpp
// Polaris
// 
// Created by DaR1ng on 26-7-10

#include "../include/tensor.h"
#include "../include/tensor_test.h"

void DataGeneration(Tensor& t) {
    for(int i=0; i<t.rows(); ++i) {
        for(int j=0; j<t.cols(); ++j) {
            t(i, j) = 1;
        }
    }
}

