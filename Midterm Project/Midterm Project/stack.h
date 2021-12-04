#include <iostream>
#include <string>
using namespace std;
#define SIZE 15

template <class T> class stack {
    private:
        int top;
        T st[SIZE];
    public:
        stack();
        void push(T k);
        T pop();
        T peek();
        bool isFull();
        bool isEmpty();

};