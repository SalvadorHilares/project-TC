#ifndef LIST_H
#define LIST_H

#include "node.h"

// TODO: Implement all methods
template <typename T>
class List {
    public:
        List(){};
        ~List(){
            // TODO            
        } ;

        virtual T front() = 0;
        virtual T back() = 0;
        virtual void push_front(T data) = 0;
        virtual void push_back(T data) = 0;
        virtual T pop_front() = 0;
        virtual T pop_back() = 0;
        virtual void insert(T data, int location) = 0;
        virtual bool remove(int location) = 0;
        virtual T& operator[](int location) = 0;
        virtual bool is_empty() = 0;
        virtual int size() = 0;
        virtual void clear() = 0;
        virtual void sort() = 0;
        virtual bool is_sorted() = 0;
        virtual void reverse() = 0;
        virtual std::string name() = 0;
};

#endif