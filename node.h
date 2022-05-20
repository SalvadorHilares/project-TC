#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(){ }

    Node(T value){
        // TODO
        data = value;
    }

    void killSelf(){
        // TODO
        delete next;        
    }
};

#endif