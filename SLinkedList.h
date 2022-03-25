#pragma once
#include "Node.h"
#include <iostream>

using namespace std;

template <class T>
class SLinkedList{
private:
    Node<T> *dummyHead;
    

public:
    SLinkedList();
    SLinkedList(const SLinkedList&);
    SLinkedList& operator=(const SLinkedList<T>&);
    ~SLinkedList();

    void destroy();
    int size();
    int indexOf(const T&) const;
    bool isEmpty();

    Node<T>* zeroth()const;
    Node<T>* first()const;
    Node<T>* find(const T&);
    Node<T>* findPrevious(const T&);

    void insert(const T&, Node<T>*);
    void remove(const T&);
    void print();

};


template <class T>
SLinkedList<T>::SLinkedList(){
    dummyHead = new Node<T>(T(), NULL);
}


template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList&  other){
    dummyHead = new Node(T(), NULL);
    *this = other;
}


template <class T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList<T>& other){
    if(this != &other){
        destroy();
        Node<T> *node = other.first();
        Node<T> *p = zeroth();
        while(node){
            insert(node->data, p);
            node = node->next;
            p = p->next;
        }
    }
    return *this;
}


template <class T>
SLinkedList<T>::~SLinkedList(){
    destroy();
    delete dummyHead;
}


template <class T>
void SLinkedList<T>::destroy(){
    Node<T> *p = first();
    while(!isEmpty())
        remove(first()->data);
}


template <class T>
int SLinkedList<T>::size(){
    Node<T> *p = first();
    int count = 0;
    while(p){
        count++;
        p = p->next;
    }
    return count;
}


template <class T>
int SLinkedList<T>::indexOf(const T& value) const{
    Node<T> *p = first();
    int index = 0;
    while(p){
        if(p->data == value)
            return index;
        index++;
        p = p->next;
    }
    return -1;
}


template <class T>
bool SLinkedList<T>::isEmpty(){
    return first() == NULL;
}


template <class T>
Node<T>* SLinkedList<T>::zeroth() const{
    return dummyHead;
}


template<class T>
Node<T>* SLinkedList<T>::first() const{
    return dummyHead->next;
}


template<class T>
Node<T>* SLinkedList<T>::find(const T& item) {
    Node<T> *p = first();
    while(p){
        if(p->data == item)
            return p;
        p = p->next;
    }
    return NULL;
}


template<class T>
Node<T>* SLinkedList<T>::findPrevious(const T& item) {
    Node<T> *p = zeroth();
    while(p->next){
        if(p->next->data == item)
            return p;
        p = p->next;
    }
    return NULL;
}


template<class T>
void SLinkedList<T>::insert(const T& item, Node<T> *node){
    Node<T> *newNode = new Node<T>(item, node->next);
    node->next = newNode;
}


template<class T>
void SLinkedList<T>::remove(const T& item) {
    Node<T> *p = findPrevious(item);
    
    if(p){
        Node<T> *temp = p->next;
        p->next = temp->next;
        delete temp;
    }
    
}


template<class T>
void SLinkedList<T>::print(){
    Node<T> *p = first();
    while(p){
        cout << p->data << " " << endl;
        p = p->next;
    }
}

