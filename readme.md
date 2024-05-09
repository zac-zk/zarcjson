# C++11 实现的JSON库

## 项目描述

本项目基于[json-tutorial](https://github.com/miloyip/json-tutorial)实现，原项目采用标准C语言（C89）实现，本项目使用C++11标准进行了重构，并对功能进行了扩展。

## 主要扩展

1. 解析器和生成器采用单例模式实现，利用智能指针维护其生命周期。
2. 利用GoogleTest测试框架进行TDD开发。
