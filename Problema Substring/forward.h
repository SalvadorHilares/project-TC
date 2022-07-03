#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
    private:
        Node<T>* head;
        int nodes;

    public:
        ForwardList(): List<T>() {
            head = nullptr;
            nodes = 0;
        }
        ~ForwardList(){
            //TODO
            delete head;
            nodes = 0;
        }
        
        T front() override; // IMPLEMENTADO
        T back() override; // IMPLEMENTADO
        void push_front(T data) override; // IMPLEMENTADO
        void push_back(T data) override; // IMPLEMENTADO
        T pop_front() override; // IMPLEMENTADO
        T pop_back() override; // IMPLEMENTADO
        void insert(T data, int location) override; // IMPLEMENTADO
        bool remove(int location) override; // IMPLEMENTADO
        T& operator[](int location) override; // IMPLEMENTADO
        bool is_empty() override; // IMPLEMENTADO
        int size() override; // IMPLEMENTADO
        void clear() override; // IMPLEMENTADO
        void sort() override; // IMPLEMENTADO
        bool is_sorted() override; // IMPLEMENTADO
        void reverse() override;
        std::string name() override; // IMPLEMENTADO
};

template <typename T>
T ForwardList<T>::front(){
    return head->data;
}

template <typename T>
T ForwardList<T>::back(){
    Node<T>* temp = head;
    while(temp->next != nullptr)
        temp = temp->next;
    T ultimate_element = temp->data;
    return ultimate_element;
}

template <typename T>
void ForwardList<T>::push_front(T data){
    Node<T>* nodo = new Node<T>;
    nodo->data = data;
    nodo->next = head;
    head = nodo;
    nodes++;
}

template <typename T>
void ForwardList<T>::push_back(T data){
    //TODO
    Node<T>* nodo = new Node<T>;
    nodo->data = data;
    nodo->next = nullptr;
    if(head == nullptr){
        head = nodo;
    }
    else{
        Node<T>* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = nodo;
    }
    nodes++;
}

template <typename T>
T ForwardList<T>::pop_front(){
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

template <typename T>
T ForwardList<T>::pop_back(){
    T data;
    if(head ->next == nullptr){
        delete head;
        head = nullptr;
        nodes--;
        return data;
    }else{
        Node<T>* temp = head;
        while(temp->next->next != nullptr)
            temp = temp->next;
        data = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        nodes--;
        return data;
    }
}

template <typename T>
void ForwardList<T>::insert(T data, int location){
    Node<T>* nodo = new Node<T>(data);
    Node<T>* temp=head;
    int i=0;
    while(i<location-1){
        temp=temp->next;
        i++;
    }
    nodo->next=temp->next;
    temp->next=nodo;
}

template <typename T>
bool ForwardList<T>::remove(int location){
    if (location >= this->nodes){
                return false;
        }else{
            if (location == 0){
                pop_front();
                return true;
            }else if ( location == this->nodes-1){
                pop_back();
                return true;
            }else {
                int cont = 0;
                Node<T>* temp = this->head;
                while (cont < location - 1) {
                    temp = temp->next;
                    cont++;
                }
                temp->next->next = temp->next;
                delete temp;
                this->nodes--;
                return true;
            }
        }
}

template <typename T>
T& ForwardList<T>::operator[](int location){
    Node<T>* temp = head;
    int cont = 0;
    while(temp != nullptr && cont < location){
        temp = temp->next;
        cont++;
    }
    return temp->data;
}

template <typename T>
bool ForwardList<T>::is_empty(){
    return (nodes == 0) ? true : false;
}

template <typename T>
int ForwardList<T>::size(){
    return nodes;
}

template<typename T>
void ForwardList<T>::clear(){
    while(head!=nullptr){
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

template<typename T>
void ForwardList<T>::sort(){
    Node<T>* temp = head;
    Node<T>* siguiente = nullptr;
    while(temp->next!=nullptr){
        siguiente = temp->next;
        while(siguiente!=nullptr){
            if(temp->data > siguiente->data){
                T swap = siguiente->data;
                siguiente->data = temp->data;
                temp->data = swap;
            }
            siguiente = siguiente->next;
        }
        temp = temp->next;
    }
}

template<typename T>
bool ForwardList<T>::is_sorted(){
    if(size()<=1)
        return true;
    Node<T>* comp = head;
    int i=0; 
    while(i<size()-1){
        if(comp->data > comp->next->data)
            return false;
        comp = comp->next;
        i++;
    }
    return true;
}

template<typename T>
void ForwardList<T>::reverse(){
    Node<T>* temp = head;
    Node<T>* prev = nullptr, *next = nullptr;

    while(temp != nullptr){
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    head = temp;
}

template<typename T>
std::string ForwardList<T>::name(){
    return "Forward List";
}

#endif