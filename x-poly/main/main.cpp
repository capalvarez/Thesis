#include <iostream>

#include <string>
#include "Stack.h"

using namespace std;



int main ()
{
    Stack<int> int_stack;
    Stack<string> str_stack;
    int_stack.push(10);
    str_stack.push("Hello");
    str_stack.push("World");
    cout << int_stack.pop() << endl;
    cout << str_stack.pop() << endl;
    cout << str_stack.pop() << endl;
    return 0;
}