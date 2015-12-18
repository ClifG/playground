//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <assert.h>

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

void PartitionList(LinkedList<int> *list, int p)
{
    if (!list)
    {
        return;
    }
    
    Node<int> *insert = list->get_Head();
    if (!insert)
    {
        return;
    }
    
    Node<int> *swap = insert->next;
    
    while(swap)
    {
        if (insert->data < p)
        {
            insert = insert->next;
            swap = swap->next;
        }
        else if (swap->data >= p)
        {
            swap = swap->next;
        }
        else
        {
            assert(swap->data < p);
            
            int save = insert->data;
            insert->data = swap->data;
            swap->data = save;
            
            insert = insert->next;
            swap = swap->next;
        }
    }
}

int main(int argc, const char * argv[]) {
    LinkedList<int> intList;
    
    intList.Append(3);
    intList.Append(5);
    intList.Append(8);
    intList.Append(5);
    intList.Append(10);
    intList.Append(2);
    intList.Append(1);
    
    PrintIntLinkedList(&intList);
    
    PartitionList(&intList, 5);
    
    printf("\nPartitioned about 5:\n");
    PrintIntLinkedList(&intList);
    
    PartitionList(&intList, 10);
    
    printf("\nPartitioned about 10:\n");
    PrintIntLinkedList(&intList);
    
    PartitionList(&intList, 2);
    
    printf("\nPartitioned about 2:\n");
    PrintIntLinkedList(&intList);
    
    PartitionList(&intList, 1);
    
    printf("\nPartitioned about 1:\n");
    PrintIntLinkedList(&intList);
    
    return 0;
}
