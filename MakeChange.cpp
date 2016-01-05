//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <map>
#include <assert.h>

using namespace std;

#define ARRAYSIZE(a) sizeof(a) / sizeof(a[0])

int NumDenoms(int amount, int *denoms, int denomSize)
{
    assert(amount >= 0);
    assert(denomSize >= 0);
    
    if (amount == 0)
        return 1;
    
    if (denomSize == 0)
        return 0;
    
    int result = 0;
    int coinCount = 0;
    
    while (amount >= (denoms[0] * coinCount))
    {
        result += NumDenoms(amount - (denoms[0] * coinCount), denoms + 1, denomSize - 1);
        coinCount++;
    }
    
    return result;
}

int NumDenomsFast(int amount, int *denoms, int denomSize)
{
    map<int, int> solved;
    solved[0] = 1;
    
    for (int i = 1; i <= amount; i++)
    {
        solved[i] = 0;
    }
    
    for (int i = 0; i < denomSize; i++)
    {
        // Figure out how we make every value, bottom-up, adding in new types of coins
        // each time.
        for (int j = denoms[i]; j <= amount; j++)
        {
            solved[j] += solved[j - denoms[i]];
        }
    }
    
    return solved[amount];
}


int main(int argc, const char * argv[]) {
    int denoms[] = {25, 10, 5, 1};

    cout << "15, [25, 10, 5, 1] = " << NumDenomsFast(15, denoms, ARRAYSIZE(denoms)) << endl;
    
    return 0;
}
