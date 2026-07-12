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

Tensor::Tensor(const Tensor& other) {
    std::copy(other.data(), other.data()+other.length(), data_);
}

Tensor::Tensor(Tensor&& other)
:strides_(std::move(other.strides_)), shape_(std::move(other.shape_)), data_(other.data_), length_(other.length_) {
    other.data_ = nullptr;
    other.length_ = 0;
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

// 

Tensor Tensor::operator+(const Tensor& other) const {
    assert(shape_ == other.shape());
    Tensor res(shape_);
    for(int i=0; i<length_; ++i) {
        res.data_[i] = data_[i] + other.data_[i];
    }
    return res;
}

Tensor& Tensor::operator=(const Tensor& other) {
    if(this == &other) return;
    if(data_ == nullptr) {
        shape_ = other.shape();
        strides_.resize(shape_.size());
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
    std::copy(other.data(), other.data()+other.length(), data_);
    return *this;
}

Tensor& Tensor::operator=(Tensor&& other) {
    if(this == &other) return;
    free(data_);
    strides_ = std::move(other.strides_);
    shape_ = std::move(other.shape_);
    data_ = other.data_;
    length_ = other.length_;
    other.data_ = nullptr;
    other.length_ = 0;
    return *this;
}

// 在实现对括号的重载的时候，我也遇到了一个技术选型的问题，也许你可以从我的纠结中得到不一样的思考。
// 选择1: 接收可变的参数，使用时类似于tensor(x, y, z, ...)，这是最自然的使用方式，符合多维张量的访问方式
// 但选择它需要引入可变参模版，这会打乱教学进度，提前进入模版概念
// 选择2: 使用vector<int64_t> shape传参，也可以实现可变参数
// 但使用太麻烦，每次访问都要构造一个vector，而且后续如果重构，成本非常高
// 选择3: 固定二维访问，能更好的衔接前面的学习，并且重构成本不高，改为可变参模版，前面的二维索引访问仍可用
// 因而此处选择第三种方式

float& Tensor::operator()(int rows_idx, int cols_idx) {
    assert(shape_.size() == 2 && rows_idx >= 0 && cols_idx >= 0 && rows_idx < shape_[0] && cols_idx < shape_[1]);
    return data_[rows_idx*strides_[1] + cols_idx*strides_[0]];
}

const float& Tensor::operator()(int rows_idx, int cols_idx) const {
    assert(shape_.size() == 2 && rows_idx >= 0 && cols_idx >= 0 && rows_idx < shape_[0] && cols_idx < shape_[1]);
    return data_[rows_idx*strides_[1] + cols_idx*strides_[0]];
}