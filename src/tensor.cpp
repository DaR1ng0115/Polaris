//
// tensor.cpp
// Polaris
// 
// Created by DaR1ng on 26-7-10

#include "../include/tensor.h"

Tensor::Tensor()
:strides_(0), shape_(), data_(nullptr), length_(0) {}

// 在理解下面这些代码之前，请再次回顾一下各个变量的含义。
// strides 用于映射到一维索引,shape 各维度数,data 实际存储数组的一维顺序数组的首地址,length 元素总数
// 接下来我来说明一下难以理解的部分
// strides : 仿照matrix二维映射到一维索引的思考，我们也可以推导出类似的规律。
// 拿个简单的例子，假设一个Tensor的三个维度分别对应时分秒，那么我如果想求第x小时第y分钟第z秒怎么求？
// 我想你应该很快就能说出来，3600x+60y+x，但为什么呢？
// 如第3小时第25分钟第5秒，前面的3个小时肯定都要算上，也就是3x3600，25分钟也要算上，即25x60，最后算上5秒
// 这就是索引映射公式，总结成抽象的规律，也就是说，一个长度为n的shape数组，对应的第x项的索引应该是shape数组的
// 第x项后面所有元素的乘积。
// 比如shape[4, 5, 6, 7] ---> strides[5x6x7=210, 6x7=42, 7, 1]（strides的最后一项总是1）

Tensor::Tensor(const std::vector<int64_t> &shape) 
:strides_(shape.size(), 1), shape_(shape), length_(1) {
    for(int i=0; i<shape.size(); ++i) {
        length_ *= shape[i];
        for(int j=shape.size()-1; j>i; --j) {
            strides_[i] *= shape[j];
        }
    }
// calloc和malloc类似，不同的是，一个是参入的参数不一样，分别是数据的数量和单个数据大小，另一个是默认所有元素填充为0
    data_ = (float*)calloc(length_, sizeof(float));
}

Tensor::Tensor(const std::vector<int64_t> &shape, float fill_data)
:strides_(shape.size(), 1), shape_(shape), length_(1) {
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

// 拷贝构造函数，使用std::copy实现深拷贝
// 注，浅拷贝和深拷贝:
// 实际上，这里有两层语义，并不是只拷贝指针就是浅拷贝，拷贝指针指向的数据就是深拷贝，第一个是相对意义上的，
// 上面所说的通过std::copy实现深拷贝即为相对意义上的，即它只会拷贝所给对象内存放的数据，如果这个对象存放的
// 数据还是指针，比如vector<float*>，那么严格来说，依然是浅拷贝
// 第二个是绝对意义上的，上述的对于vector<float*>仍然是浅拷贝，就是绝对意义上的。绝对的深拷贝应该是无论有
// 多少的嵌套指针，都会拷贝到最后一层数据，即便最后一层数据也是指针(均为nullptr)。
// 我们常说vector的拷贝和std::copy是深拷贝，其实是相对意义上的，对于无指针嵌套的对象的确是深拷贝。

Tensor::Tensor(const Tensor& other) {
    std::copy(other.data(), other.data()+other.length(), data_);
    strides_ = other.strides();
    shape_ = other.shape();
    length_ = other.length();
}

// 此处是移动构造函数
// 移动语义我在matrix.cpp中已说明过，这里借助实际的函数再讲解一下
// "&&"的意思是右值，简单来说就是一个临时的对象，比如int a = 1，此处的a是左值，1是右值，当赋值结束，1就被销毁了
// 这和移动构造有什么关系呢？重点在于，移动构造在于"移动"，不会发生拷贝，也就是说，如果传入的是一个左值（持久对象）
// 那么这个左值对象就变成空对象了。如果想保留传入对象，那就必须用拷贝构造。

Tensor::Tensor(Tensor&& other)
// std::move()并不是移动本身，而是将一个左值对象强行转化为右值对象，以完成移动语义
// 移动语义的根本之处其实在于这两行:
// data_ = other.data_;
// other.data_ = nullptr;
// 第一步是所有权转移，第二步就是原指针置空
// 因此，其实std::move()就是帮我们在底层做了这些事情，将原对象属性全部清空
:strides_(std::move(other.strides_)), shape_(std::move(other.shape_)), data_(other.data_), length_(other.length_) {
    other.data_ = nullptr;
    other.length_ = 0;
}

// 此处的析构函数切不可忘记实现，否则会发生内存泄漏，这在深度学习训练中尤其严重

Tensor::~Tensor() {
    free(data_);
    data_ = nullptr;
}

int64_t Tensor::shape(int dim) const {
    return shape_[dim];
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

// 此处的移动语义可以和移动构造对照着理解，过程是类似的。
// 再次提醒，对于非RAII属性，在进行移动之后，一定要将其清零或置空
// 否则很容易会导致double free

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