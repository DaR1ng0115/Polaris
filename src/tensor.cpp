// 
// tensor.cpp
// Polaris
//
// Created by DaR1ng on 26-7-9

#include "../include/tensor.h"
#include <cassert>

Tensor::Tensor() 
:rows_(1), cols_(1), data_(0) {
    this->data_ = std::vector<float>(1);
}

Tensor::Tensor(int rows, int cols)
:rows_(rows), cols_(cols) {
    this->data_ = std::vector<float>(this->rows_*this->cols_);
    for(int i=0; i<this->length(); ++i) {
        this->data_[i] = 0.0f;
    }
}

Tensor::Tensor(int rows, int cols, float fill_data)
:rows_(rows), cols_(cols) {
    this->data_ = std::vector<float>(this->rows_*this->cols_);
    for(int i=0; i<this->length(); ++i) {
        data_[i] = fill_data;
    }
}

float Tensor::at(int rows_idx, int cols_idx) const {
        return this->data()[rows_idx*this->cols() + cols_idx];
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

Tensor& Tensor::operator=(const Tensor& other) {
    if(this->rows() == 1 && this->cols() == 1 && this->at(0, 0) == 0.0f) {
        this->data_ = std::vector<float>(other.rows()*other.cols());
        this->rows_ = other.rows(); this->cols_ = other.cols();
    }
    assert(this->rows() == other.rows() && this->cols() == other.cols());
    for(int i=0; i<this->length(); ++i) {
        this->data_[i] = other.data()[i];
    }
    return *this;
}

float& Tensor::operator()(int rows_idx, int cols_idx) {
    assert(rows_idx>=0 && cols_idx>=0 && rows_idx<this->rows_ && cols_idx<this->cols_);
    return this->data_[rows_idx*this->cols_+cols_idx];
}

const float& Tensor::operator()(int rows_idx, int cols_idx) const {
    assert(rows_idx>=0 && cols_idx>=0 && rows_idx<this->rows_ && cols_idx<this->cols_);
    return this->data_[rows_idx*this->cols_+cols_idx];
}