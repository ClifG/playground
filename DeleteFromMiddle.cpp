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
void DeleteFromMiddle(Node<T> *n)
{
    if (!n || !n->next)
    {
        return;
    }
    
    n->data = n->next->data;
    
    Node<T> *toDelete = n->next;
    n->next = n->next->next;
    delete toDelete;
}

void RunTest(LinkedList<int> *intList, int k)
{
    printf("Delete node %d (0-based)\n", k);
    
    Node<int> *deleteNode = intList->get_Head();
    for (int i = 0; i < k; i++)
    {
        deleteNode = deleteNode->next;
    }
    
    DeleteFromMiddle(deleteNode);
    
    PrintIntLinkedList(intList);
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
    
    RunTest(&intList, 2);
    RunTest(&intList, 8);
    RunTest(&intList, 3);
    
    return 0;
}
