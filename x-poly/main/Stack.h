#ifndef THESIS_STACK_H
#define THESIS_STACK_H

template <class T>
class Stack
{
public:
    Stack();
    void push(T i);
    T pop();
private:
    int top;
    T st[100];
};

template <class T>
Stack<T>::Stack()
{
    top = -1;
}

template <class T>
void Stack<T>::push(T i)
{
    st[++top] = i;
}

template <class T>
T Stack<T>::pop()
{
    return st[top--];
}

#endif 
