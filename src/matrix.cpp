// 
// matrix.cpp
// Polaris
//
// Created by DaR1ng on 26-7-9

/*
这里是tensor的源文件，定义了tensor具备的功能和方法
在本章中，我会尽可能显式写出“this”，以便于理解，后续我会省略
*/

#include "../include/matrix.h"
#include <cassert>

// 在命名上，我们可以让数据结构自带的私有成员变量属性带有下标，即variable_
// 这样做可以让自己包括其他人更好地理解哪些变量是本对象的变量
Matrix::Matrix() 
:rows_(1), cols_(1) {
    this->data_ = std::vector<float>(1);
}

Matrix::Matrix(int rows, int cols)
:rows_(rows), cols_(cols) {
    this->data_ = std::vector<float>(this->rows_*this->cols_);
}

Matrix::Matrix(int rows, int cols, float fill_data)
:rows_(rows), cols_(cols) {
    this->data_ = std::vector<float>(this->rows_*this->cols_, fill_data);
}

int Matrix::rows() const {
    return this->rows_;
}

int Matrix::cols() const {
    return this->cols_;
}

// 此处我特意选择了length作为方法的名称，因为其专指matrix的“长度”，即无论是几维的matrix，压平成一维数组后的长度
int Matrix::length() const {
    return this->data_.size();
}

float* Matrix::data() {
    return this->data_.data();
}

const float* Matrix::data() const {
    return this->data_.data();
}

Matrix Matrix::operator+(const Matrix &other) const {
    assert(this->rows() == other.rows() && this->cols() == other.cols());
    Matrix res(this->rows(), this->cols());
    for(int i=0; i<this->length(); ++i) {
        res.data()[i] = this->data_[i] + other.data()[i];
    }
    return res;
}

Matrix& Matrix::operator=(const Matrix &other) {
    if(this->rows() == 1 && this->cols() == 1 && this->data_[0, 0] == 0.0f) {
        this->data_ = std::vector<float>(other.rows()*other.cols());
        this->rows_ = other.rows(); this->cols_ = other.cols();
    }
    assert(this->rows() == other.rows() && this->cols() == other.cols());
    for(int i=0; i<this->length(); ++i) {
        this->data_[i] = other.data()[i];
    }
    return *this;
}

float& Matrix::operator()(int rows_idx, int cols_idx) {
    assert(rows_idx>=0 && cols_idx>=0 && rows_idx<this->rows_ && cols_idx<this->cols_);
    return this->data_[rows_idx*this->cols_+cols_idx];
}

const float& Matrix::operator()(int rows_idx, int cols_idx) const {
    assert(rows_idx>=0 && cols_idx>=0 && rows_idx<this->rows_ && cols_idx<this->cols_);
    return this->data_[rows_idx*this->cols_+cols_idx];
}