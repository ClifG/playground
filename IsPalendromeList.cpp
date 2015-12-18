//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <memory>
#include <stack>
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
    
    LinkedList(const LinkedList<T> &other)
    {
        // Copy
        Node<T> *otherHead = other.get_Head();
        
        while (otherHead)
        {
            Append(otherHead->data);
            otherHead = otherHead->next;
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
    
    void Prepend(T d)
    {
        if (!head)
        {
            head = new Node<T>(d);
        }
        else
        {
            Node<T> *newHead = new Node<T>(d);
            newHead->next = head;
            head = newHead;
        }
    }
    
    // Read-only access to the head pointer
    Node<T>* get_Head() const
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

bool IsPalendrome(LinkedList<int> *list)
{
    if (!list)
    {
        return true; // why not?
    }
    
    unique_ptr<LinkedList<int>> reverse(new LinkedList<int>());
    
    Node<int> *head = list->get_Head();
    
    while (head)
    {
        reverse->Prepend(head->data);
        head = head->next;
    }
    
    head = list->get_Head();
    Node<int> *r_head = reverse->get_Head();
    
    // Compare the given list with the reversed list.
    while (head)
    {
        if (!r_head || (head->data != r_head->data))
        {
            return false;
        }
        
        head = head->next;
        r_head = r_head->next;
    }
    
    return (r_head == nullptr);
}

bool IsPalendrome2(LinkedList<int> *list)
{
    if (!list || !list->get_Head())
    {
        return true;
    }
    
    stack<int> S;
    
    Node<int> *fast = list->get_Head();
    Node<int> *slow = fast;
    
    while (fast && fast->next)
    {
        S.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }
    
    if (fast)
    {
        // Odd length list
        slow = slow->next;
    }
    
    while (slow)
    {
        if (slow->data != S.top())
        {
            return false;
        }
        
        slow = slow->next;
        S.pop();
    }
    
    assert(S.empty());
    
    return true;
}

int main(int argc, const char * argv[]) {
    LinkedList<int> list1;
    
    list1.Append(2);
    list1.Append(3);
    list1.Append(5);
    list1.Append(3);
    list1.Append(2);
    
    LinkedList<int> list2;
    
    list2.Append(8);
    list2.Append(7);
    list2.Append(1);
    list2.Append(9);
    list2.Append(7);
    list2.Append(8);
    
    LinkedList<int> list3;
    
    list3.Append(8);
    list3.Append(8);
    
    
    PrintIntLinkedList(&list1);
    
    printf("IsPalendrome1: ");
    printf((IsPalendrome(&list1)) ? "true\n" : "false\n");
    
    printf("IsPalendrome2: ");
    printf((IsPalendrome2(&list1)) ? "true\n" : "false\n");
    

    PrintIntLinkedList(&list2);
    
    printf("IsPalendrome1 ");
    printf((IsPalendrome(&list2)) ? "true\n" : "false\n");
    
    printf("IsPalendrome2: ");
    printf((IsPalendrome2(&list2)) ? "true\n" : "false\n");

    
    PrintIntLinkedList(&list3);
    
    printf("IsPalendrome1 ");
    printf((IsPalendrome(&list3)) ? "true\n" : "false\n");
    
    printf("IsPalendrome2: ");
    printf((IsPalendrome2(&list3)) ? "true\n" : "false\n");
    
    return 0;
}
