//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <memory>

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

// Returns a new LinkedList allocated on the heap. Caller must delete.
LinkedList<int>* SumLists(LinkedList<int> *list1, LinkedList<int> *list2)
{
    // Must pass two valid lists (they can be empty though)
    if (!list1 || !list2)
    {
        return nullptr;
    }
    
    Node<int> *itr1 = list1->get_Head();
    Node<int> *itr2 = list2->get_Head();
    
    // Special case: both lists are empty
    if (!itr1 && !itr2)
    {
        // Return an empty list
        return new LinkedList<int>();
    }
    
    if (!itr1 || !itr2)
    {
        // One list is empty, so just copy the non-empty list
        return (!itr1) ?
            new LinkedList<int>(*list2) :
            new LinkedList<int>(*list1);
    }
    
    unique_ptr<LinkedList<int>> returnList(new LinkedList<int>());
    
    bool carry = false;
    while(itr1 && itr2)
    {
        int sum = itr1->data + itr2->data;
        if (carry)
        {
            sum++;
        }
        
        carry = (sum >= 10);
        sum %= 10;
        
        returnList->Append(sum);
        
        itr1 = itr1->next;
        itr2 = itr2->next;
    }
    
    Node<int> *finish = itr1 ? itr1 : itr2;
    
    while(finish)
    {
        // Copy any remaining digits if there are any
        int digit = finish->data;
        if (carry)
        {
            digit++;
        }
        
        carry = (digit >= 10);
        digit %= 10;
        
        returnList->Append(digit);
        
        finish = finish->next;
    }
    
    if (carry)
    {
        returnList->Append(1);
    }
    
    return returnList.release();
}

int main(int argc, const char * argv[]) {
    LinkedList<int> list1;
    
    list1.Append(2);
    list1.Append(3);
    list1.Append(3);
    
    LinkedList<int> list2;
    
    list2.Append(8);
    list2.Append(7);
    list2.Append(1);
    list2.Append(9);
    
    PrintIntLinkedList(&list1);
    printf("+\n");
    PrintIntLinkedList(&list2);
    printf("=\n");
    
    unique_ptr<LinkedList<int>> sumList(SumLists(&list1, &list2));
    PrintIntLinkedList(sumList.get());
    
    return 0;
}
