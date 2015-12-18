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

void RemoveDupes(LinkedList<int> *list)
{
    Node<int> *itr = list->get_Head();
    if (!itr)
    {
        return;
    }
    
    set<int> seen;
    seen.insert(itr->data);
    
    while(itr->next)
    {
        if (seen.end() != seen.find(itr->next->data))
        {
            // Found a dupe. Remove it.
            Node<int> *toDelete = itr->next;
            itr->next = itr->next->next;
            delete toDelete;
        }
        else
        {
            seen.insert(itr->next->data);
            itr = itr->next;
        }
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
    
    RemoveDupes(&intList);
    PrintIntLinkedList(&intList);
    
    return 0;
}
