//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <set>

using namespace std;

template <class T>
struct Node
{
    Node *next;
    T data;
    
    Node(T d) :
        data(d),
        next(nullptr)
    {}
};

template <class T>
class LinkedList
{
private:
    Node<T> *head;
    
public:
    LinkedList() :
        head(nullptr)
    {}
    
    ~LinkedList()
    {
        while (head)
        {
            Node<T> *toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }
    
    void Append(T d)
    {
        if (!head)
        {
            head = new Node<T>(d);
        }
        else
        {
            Node<T> *itr = head;
            while (itr->next)
            {
                itr = itr->next;
            }
            
            itr->next = new Node<T>(d);
        }
    }
    
    // Read-only access to the head pointer
    Node<T>* get_Head()
    {
        return head;
    }
};

void PrintIntLinkedList(LinkedList<int> *list)
{
    Node<int> *itr = list->get_Head();
    while(itr)
    {
        printf("%d -> ", itr->data);
        itr = itr->next;
    }
    
    printf("null\n");
}

template <class T>
Node<T>* KthToLast(LinkedList<T> *list, int k)
{
    if (!list || (k < 0))
    {
        return nullptr;
    }
    
    Node<T> *first = list->get_Head();
    Node<T> *second = first;
    
    for (int i = 0; i < k; i++)
    {
        if (!second)
        {
            return nullptr;
        }
        
        second = second->next;
    }
    
    while(second)
    {
        second = second->next;
        first = first->next;
    }
    
    return first;
}

void RunTest(LinkedList<int> *intList, int k)
{
    Node<int> *foundNode = KthToLast(intList, k);
    if (!foundNode)
    {
        printf("Couldn't get %d from last\n", k);
    }
    else
    {
        printf("%d from last: %d\n", k, foundNode->data);
    }
}

int main(int argc, const char * argv[]) {
    LinkedList<int> intList;
    
    intList.Append(5);
    intList.Append(10);
    intList.Append(15);
    intList.Append(5);
    intList.Append(22);
    intList.Append(22);
    intList.Append(22);
    intList.Append(13);
    intList.Append(5);
    
    PrintIntLinkedList(&intList);
    
    RunTest(&intList, 0);
    RunTest(&intList, 1);
    RunTest(&intList, 2);
    RunTest(&intList, 8);
    RunTest(&intList, 9);
    RunTest(&intList, 10);
    
    return 0;
}
