#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "node.h"

template<typename T>
class Queue{
    private:
        Node<T>* head;
        int nodes;
    public:
        Queue(){
            head = nullptr;
            nodes = 0;
        }
        ~Queue(){
            delete head;
            nodes = 0;
        }
        void enqueue(T data);
        T dequeue();
        T front();
        T back();
        T& operator[](int location);
        bool is_empty();
        int size();
};

template<typename T>
void Queue<T>::enqueue(T data){
    Node<T>* nodo = new Node<T>;
    nodo->data = data;
    nodo->next = head;
    head = nodo;
    nodes++;
}

template<typename T>
T Queue<T>::dequeue(){
    if(head == nullptr){
        throw("ERROR");
    }else{
        Node<T>* temp = head;
        T data = head->data;
        head = head->next;
        delete temp;
        nodes--;
        return data;
    }
}

template<typename T>
T Queue<T>::front(){
    return head->data;
}

template<typename T>
T Queue<T>::back(){
    Node<T>* temp = head;
    while(temp->next != nullptr)
        temp = temp->next;
    T ultimate_element = temp->data;
    return ultimate_element;
}

template<typename T>
bool Queue<T>::is_empty(){
    return (nodes == 0) ? true : false;
}

template <typename T>
T& Queue<T>::operator[](int location){
    Node<T>* temp = head;
    int cont = 0;
    while(temp != nullptr && cont < location){
        temp = temp->next;
        cont++;
    }
    return temp->data;
}

template<typename T>
int Queue<T>::size(){
    return nodes;
}
#endif