// 
// tensor.cpp
// Polaris
//
// Created by DaR1ng on 26-7-9

#include "../include/tensor.h"
#include <cassert>

Tensor::Tensor() 
:rows_(1), cols_(1), data_(0) {}

Tensor::Tensor(int rows, int cols)
:rows_(rows), cols_(cols) {
    for(int i=0; i<this->length(); ++i) {
        this->data_[i] = 0;
    }
}

Tensor::Tensor(int rows, int cols, float fill_data)
:rows_(rows), cols_(cols) {
    for(int i=0; i<this->length(); ++i) {
        data_[i] = fill_data;
    }
}

int Tensor::rows() const {
    return this->rows_;
}

int Tensor::cols() const {
    return this->cols_;
}

int Tensor::length() const {
    return this->data_.size();
}

float* Tensor::data() {
    return this->data_.data();
}

const float* Tensor::data() const {
    return this->data_.data();
}

Tensor Tensor::operator+(const Tensor& other) const {
    assert(this->rows() == other.rows() && this->cols() == other.cols());
    Tensor res(this->rows(), this->cols());
    for(int i=0; i<this->length(); ++i) {
        res.data()[i] = this->data_[i] + other.data()[i];
    }
    return res;
}