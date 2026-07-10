# CH01-TENSOR

**Language**  
[简体中文](README.zh.md)

## INTRODUCTION
Welcome to Polaris.This is the first chapter of the tutorial series.
In this chapter, you need to complete or learn the following things:
- Environment configuration
- Engineering specifications
- Introduction to deep learning
- Linear algebra and deep learning

Before learning, you should master the following knowledge:
- Basic knowledge of linear algebra (mainly matrices)
- C/C++ basics (data types, pointers, functions, structures, classes)

## Environment configuration
It is recommended to use VSCode to learn this project. There are many tutorials online on how to configure the C++ environment for VSCode, so I won't go into detail here.
The additional dependency that needs to be configured is CMake.

## Engineering specifications
**To do a good job, one must first sharpen one's tools.**  
First, you need to understand the project structure, the files/modules/functions that may be needed...
A common pattern is to place source files (.cpp/.cxx) in the src folder and header files (.h/.hpp) in the include folder.
Among them, the src and include folders can be further classified according to their functions, such as utils (tools), config (configuration files), etc. You can create them as needed, and this project will provide as standardized a file classification as possible.
At the beginning of each file, you can also refer to my pattern:
// 
// filename.cpp 
// ProjectName
//
// Created by username on xx-xx-xx

## Introduction to deep learning
I won't talk about many advanced concepts and rigorous logic here--these are well covered in tutorials on the market. I will talk more about my personal understanding, which may help everyone better understand deep learning.
deep learning is essentially fitting a `function`, which means that many things can be described by some function. However, unlike the functions we usually see, the functions fitted by deep learning are multivariate, with all variables being tensors and several orders of magnitude more complex.
With this macro concept, we can better understand which modules are important and which functions need to be focused on.
By the way, `this project is more suitable for readers who are interested in systems`. If you plan to focus on algorithms, other tutorials, courses, or books may be more suitable for you. However, this suggestion is not absolute. Algorithms are built on top of systems, and understanding some knowledge about systems is beneficial to algorithms.

## Linear algebra and deep learning
Linear algebra is not a very advanced field. You can think of linear algebra as a carrier of `information`, and one of the most important concepts in deep learning is information. How to carry more information in a unit space is a very important topic. For example, if a matrix is a singular matrix, then it is not invertible, and it is a `bad matrix` (quoted from MIT 18.06 Gilbert Strang), because this matrix carries some `nonsense`. If you don't know what a singular matrix is, don't worry. Everyone should have learned about systems of linear equations:
```{2x+4=2y,4x+8=4y}``
Obviously, these two equations cannot be solved for a unique solution because the second equation is just twice the first equation. Therefore, we say that this equation does not carry enough information.