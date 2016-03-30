//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class MinStack
{
private:
    vector<T> stack;
    vector<T> minStack;
    
public:
    MinStack() {}
    virtual ~MinStack() {}
    
    void push(T item)
    {
        if (minStack.empty() || (item <= minStack.back()))
        {
            minStack.push_back(item);
        }
        stack.push_back(item);
    }
    
    T pop()
    {
        if (stack.empty())
        {
            throw;
        }
        
        T back = stack.back();
        stack.pop_back();
        
        if (back == minStack.back())
        {
            minStack.pop_back();
        }
        
        return back;
    }
    
    T min()
    {
        if (minStack.empty())
        {
            throw;
        }
        
        return minStack.back();
    }
    
    bool empty()
    {
        return stack.empty();
    }
    
    void print()
    {
        if (stack.empty())
        {
            cout << "Empty!" << endl;
        }
        else
        {
            bool first = true;
            for (T item: stack)
            {
                if (!first)
                {
                    cout << ", ";
                }
            
                cout << item;
                first = false;
            }
            cout << endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    MinStack<int> s;
    s.push(5);
    s.push(3);
    s.push(4);
    s.push(10);
    
    while (!s.empty())
    {
        cout << "Stack: ";
        s.print();
    
        cout << "Min: " << s.min() << endl << endl;
        s.pop();
    }

    cout << "Stack ";
    s.print();
    
    return 0;
}
