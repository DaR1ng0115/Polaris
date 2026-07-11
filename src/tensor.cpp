//
// tensor.cpp
// Polaris
// 
// Created by DaR1ng on 26-7-10

#include "../include/tensor.h"

Tensor::Tensor()
:strides_(0), shape_(), data_(nullptr), length_(0) {}

Tensor::Tensor(const std::vector<int64_t> &shape) 
:shape_(shape), length_(1), strides_(shape.size(), 1) {
    for(int i=0; i<shape.size(); ++i) {
        length_ *= shape[i];
        for(int j=shape.size()-1; j>i; --j) {
            strides_[i] *= shape[j];
        }
    }
    data_ = (float*)calloc(length_, sizeof(float));
}

Tensor::Tensor(const std::vector<int64_t> &shape, float fill_data)
:shape_(shape), length_(1), strides_(shape.size(), 1) {
    for(int i=0; i<shape.size(); ++i) {
        length_ *= shape[i];
        for(int j=shape.size()-1; j>i; --j) {
            strides_[i] *= shape[j];
        }
    }
    data_ = (float*)malloc(length_*sizeof(float));
    for(int i=0; i<length_; ++i) {
        data_[i] = fill_data;
    }
}

Tensor::~Tensor() {
    free(data_);
    data_ = nullptr;
}

int64_t Tensor::shape(int dim) {
    return shape_[dim-1];
}

const std::vector<int64_t> Tensor::shape() const {
    return shape_;
}

const std::vector<int64_t> Tensor::strides() const {
    return strides_;
}

int64_t Tensor::length() {
    return length_;
}

int64_t Tensor::length() const {
    return length_;
}

float* Tensor::data() {
    return data_;
}

const float* Tensor::data() const {
    return data_;
}

void Tensor::copy(const Tensor& other) {
    std::copy(other.data(), other.data()+other.length(), data_);
}

Tensor Tensor::operator+(const Tensor& other) const {
    assert(shape_ == other.shape());
    Tensor res(shape_);
    for(int i=0; i<length_; ++i) {
        res.data_[i] = data_[i] + other.data_[i];
    }
    return res;
}

Tensor& Tensor::operator=(const Tensor& other) {
    if(data_ == nullptr) {
        length_ = 1;
        for(int i=0; i<other.shape().size(); ++i) {
            length_ *= other.shape()[i];
            for(int j=shape().size()-1; j>i; --j) {
                strides_[i] *= other.shape()[j];
            }
    }
    data_ = (float*)calloc(length_, sizeof(float));
    }
    assert(shape_ == other.shape());
    for(int i=0; i<other.length(); ++i) {
        data_[i] = other.data()[i];
    }
    return *this;
}