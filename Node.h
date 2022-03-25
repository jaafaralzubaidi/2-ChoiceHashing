#pragma once
#include <iostream>

using namespace std;


template <class T>
class Node{
public: 
    T data;
    Node *next;

    Node(const T& d = T(), Node *n = NULL) : data(d), next(n) {}
};