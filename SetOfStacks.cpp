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
class SetOfStacks
{
private:
    vector<vector<T>> stacks;
    int capacity;
    
public:
    SetOfStacks(int c) : capacity(c) {}
    virtual ~SetOfStacks() {}
    
    void push(T item)
    {
        if (stacks.empty() || (stacks.back().size() >= capacity))
        {
            stacks.push_back(vector<T>());
        }
        stacks.back().push_back(item);
    }
    
    T pop()
    {
        return popAt(stacks.size() - 1);
    }
    
    T popAt(int stackIndex)
    {
        if (stacks.empty() || (stackIndex >= stacks.size()) || stacks[stackIndex].empty())
        {
            throw;
        }
        
        T value = stacks[stackIndex].back();
        stacks[stackIndex].pop_back();
        
        while (!stacks.empty() && stacks.back().empty())
        {
            stacks.pop_back();
        }
        
        return value;
    }
    
    void print()
    {
        if (stacks.empty())
        {
            cout << "Empty!" << endl;
            return;
        }
        
        int i = 0;
        for (vector<int> v: stacks)
        {
            cout << "Stack[" << i << "]: ";
            bool first = true;
            for (int item: v)
            {
                if (!first)
                {
                    cout << ", ";
                }
                cout << item;
                first = false;
            }
            cout << endl;
            i++;
        }
    }
};

template <class T>
void PopAtTest(SetOfStacks<T> &s, int stackIndex, int count)
{
    cout << "PopAt(" << stackIndex << ") " << count << " times..." << endl;
    for (int i = 0; i < count; i++)
    {
        cout << "Value: " << s.popAt(stackIndex) << endl;
        s.print();
    }
}

int main(int argc, const char * argv[]) {
    SetOfStacks<int> s(3);
    for (int i = 0; i < 13; i++)
    {
        s.push(i);
    }
    
    s.print();
    
    for (int i = 0; i < 6; i++)
    {
        cout << "Popping value " << s.pop() << endl;
        s.print();
    }
    
    for (int i = 100; i < 107; i++)
    {
        cout << "Pusing value " << i << endl;
        s.push(i);
        s.print();
    }
    
    PopAtTest(s, 3, 3);
    PopAtTest(s, 4, 2);
    PopAtTest(s, 0, 3);
    PopAtTest(s, 2, 3);
    PopAtTest(s, 1, 3);
    
    return 0;
}
