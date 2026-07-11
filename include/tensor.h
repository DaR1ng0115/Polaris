//
// tensor.h
// Polaris
//
// Created by DaR1ng on 26-7-10

#pragma once
#include <vector>
#include<cstdlib>
#include<assert.h>

class Tensor {
private:
    std::vector<int64_t> strides_;
    std::vector<int64_t> shape_;
    float* data_;
    int64_t length_;
public:
    Tensor();
    Tensor(const std::vector<int64_t> &shape);
    Tensor(const std::vector<int64_t> &shape, float fill_data);
    ~Tensor();

    int64_t shape(int dim);
    const std::vector<int64_t> shape() const;
    const std::vector<int64_t> strides() const;
    int64_t length();
    int64_t length() const;
    float* data();
    const float* data() const;
    void copy(const Tensor& other);

    Tensor operator+(const Tensor& other) const;
    Tensor& operator=(const Tensor& other);
    float& operator()(const std::vector<int64_t> &shape);
    const float& operator()(const std::vector<int64_t> &shape) const;
};