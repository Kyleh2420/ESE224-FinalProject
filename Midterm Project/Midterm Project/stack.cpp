#include "stack.h"
using namespace std;

template<class T> stack<T>::stack() {
    top = -1;
}

template <class T> void stack<T>:: push (T k) {
    if (isFull()) {
        cout << "Stack is full" << endl;
    }
    top++;
    st[top]=k;
}

template <class T> bool stack<T>::isEmpty() {
    (top == -1) ? return 1 : return 0;
}

template <class T> bool stack<T>::isFull() {
    (top == (SIZE-1)) ? return 1 : return 0;
}

template <class T> T stack<T>::pop() {
    T popped = st[top];
    top--;
    return popped;
}

template <class T> T stack<T>::peek() {
    T tmp = st[top];
    return tmp;
}

