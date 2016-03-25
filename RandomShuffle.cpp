//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>

using namespace std;

void PrintArray(int deck[], int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%u", deck[i]);
        if (i < (size - 1))
            printf(", ");
    }
    printf("]\n");
}

void Shuffle(int deck[], int size)
{
    if (size <= 1)
        return;
    
    while (size > 0)
    {
        int idx = rand() % size;
        int temp = deck[size - 1];
        deck[size - 1] = deck[idx];
        deck[idx] = temp;
        size--;
    }
}

int main(int argc, const char * argv[]) {

    int deck[52];
    for (int i = 0; i < 52; i++)
    {
        deck[i] = i + 1;
    }
    
    printf("Before: ");
    PrintArray(deck, 52);

    for (int i = 0; i < 3; i++)
    {
        Shuffle(deck, 52);
        printf("After: ");
        PrintArray(deck, 52);
    }
    
    return 0;
}
