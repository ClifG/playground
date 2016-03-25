//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>

using namespace std;

bool AddBits(bool a, bool b, bool *c)
{
    if (a && b)
    {
        bool oldCarry = *c;
        *c = true;
        return oldCarry;
    }
    else if (a != b)
    {
        return !(*c);
    }
    else
    {
        bool oldCarry = *c;
        *c = false;
        return oldCarry;
    }
}

uint Add(uint x, uint y)
{
    uint retVal = 0;
    uint pos = 0;

    bool carry = false;

    while ((x > 0) || (y > 0))
    {
        bool newBit = AddBits(x & 1, y & 1, &carry);
        
        if (newBit)
        {
            retVal += (1 << pos);
        }
        
        pos++;
        x >>= 1;
        y >>= 1;
    }
    
    if (carry)
    {
        retVal += (1 << pos);
    }
    
    return retVal;
}

int main(int argc, const char * argv[]) {
    printf("1 + 1 = %u\n", Add(1, 1));
    printf("3 + 12 = %u\n", Add(3, 12));
    printf("0 + 0 = %u\n", Add(0, 0));
    printf("1 + 0 = %u\n", Add(1, 0));
    
    return 0;
}
