#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
    private:
        Node<T>* head;
        Node<T>* tail;
        int nodes;
    public:
        DoubleList() : List<T>() {
            head = nullptr;
            tail = nullptr;
            nodes = 0;
        }

        ~DoubleList(){ 
         	// TODO
             delete head;
             delete tail;
             nodes = 0;            
        }

        T front() override;
        T back() override;
        void push_front(T data) override;
        void push_back(T data) override;
        T pop_front() override;
        T pop_back() override;
        void insert(T data, int location) override;
        bool remove(int location) override;
        T& operator[](int location) override;
        bool is_empty() override;
        int size() override;
        void clear() override;
        void sort() override;
        bool is_sorted() override;
        void reverse() override;
        std::string name() override;
        
};

template <typename T>
T DoubleList<T>::front(){
    return head->data;
}

template <typename T>
T DoubleList<T>::back(){
    return tail->data;
}

template <typename T>
void DoubleList<T>::push_front(T data){
    Node<T>* nodo = new Node<T>(data);
    if (nodes == 0){
        head = nodo;
        tail = nodo;
    }else{
        nodo->next = head;
        head->prev = nodo;
        head = nodo;
    }
    nodes++;
}

template <typename T>
void DoubleList<T>::push_back(T data){
    //TODO
    Node<T>* nodo = new Node<T>(data);
    if(nodes == 0){
        head = nodo;
        tail = nodo;
    }else{
        nodo->prev = tail;
        tail->next = nodo;
        tail = nodo;
    }
    nodes++;
}

template <typename T>
T DoubleList<T>::pop_front(){
    if(nodes == 0){
        throw("ERROR");
    }else{
        Node<T>* temp = head;
        T data = temp->data;
        head = head->next;
        delete temp;
        head->prev = nullptr;
        nodes--;
        return data;
    }
}

template <typename T>
T DoubleList<T>::pop_back(){
    if(nodes == 0){
        throw("ERROR");
    }else{
        Node<T>* temp = tail;
        T data = temp->data;
        tail = tail->prev;
        delete temp;
        tail->next = nullptr;
        nodes--;
        return data;
    }
}

template <typename T>
void DoubleList<T>::insert(T data, int location){
    if ( location >= nodes){
        throw("ERROR");
    }else{
        Node<T>* nodo = new Node<T>(data);
        Node<T>* temp=head;
        int i=0;
        while(i<location){
            temp=temp->next;
            i++;
        }
        nodo -> prev = temp -> prev;
        temp -> prev -> next = nodo;
        temp -> prev = nodo;
        nodo -> next = temp;
        nodes++;
    }
}

template <typename T>
bool DoubleList<T>::remove(int location){
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
T& DoubleList<T>::operator[](int location){
    Node<T>* temp = head;
    if ( location >= nodes){
        throw("ERROR");
    }else{
        int cont = 0;
        while(cont < location){
            temp = temp->next;
            cont++;
        }
    }
    return temp->data;
}

template <typename T>
bool DoubleList<T>::is_empty(){
    return (size() == 0) ? true : false;
}

template <typename T>
int DoubleList<T>::size(){
    return nodes;
}

template<typename T>
void DoubleList<T>::clear(){
    while(head!=nullptr){
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

template<typename T>
void DoubleList<T>::sort(){
    Node<T>* temp = head;
    Node<T>* siguiente = nullptr;
    for(int i=0; i<size()-1; i++){
        siguiente = temp->next;
        for(int j=0; j<size()-i-1;j++){
            if(temp->data > siguiente->data){
                T swap = temp->data;
                temp->data = siguiente->data;
                siguiente->data = swap;
            }
            siguiente = siguiente->next;
        }
        temp = temp->next;
    }
}

template<typename T>
bool DoubleList<T>::is_sorted(){
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
void DoubleList<T>::reverse(){
    Node<T>* temphead = head;
    Node<T>* temptail = tail;
    bool par = true;
    while(temphead != temptail && par){
        T aux = temphead->data;
        temphead->data = temptail->data;
        temptail->data = aux;
        temphead = temphead->next;
        if(temphead = temptail){
            par = false;
        }
        temptail = temptail->prev;
    }
}

template<typename T>
std::string DoubleList<T>::name(){
    return "Double List";
}
#endif