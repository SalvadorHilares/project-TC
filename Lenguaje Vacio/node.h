#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){ 
        next = nullptr;
        prev = nullptr;
    }

    Node(T value){
        // TODO
        data = value;
        next = nullptr;
        prev = nullptr;
    }

    void killSelf(){
        // TODO        
    }
};

#endif