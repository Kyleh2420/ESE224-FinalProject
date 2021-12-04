#include "templateStack.h"
using namespace std;

template<class T> templateStack<T>::templateStack() {
    top = -1;
}

template <class T> void templateStack<T>:: push (T k) {
    if (isFull()) {
        cout << "Stack is full" << endl;
    }
    top++;
    st[top]=k;
}

template <class T> bool templateStack<T>::isEmpty() {
    if (top == -1)
        return 1;
    else 
        return 0;
}

template <class T> bool templateStack<T>::isFull() {
    if (top == (SIZE - 1))
        return 1;
    else
        return 0;
}

template <class T> T templateStack<T>::pop() {
    T popped = st[top];
    top--;
    return popped;
}

template <class T> T templateStack<T>::peek() {
    T tmp = st[top];
    return tmp;
}

