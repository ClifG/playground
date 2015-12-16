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

int RunLength(char **s)
{
    if (!s || !(*s) || !(*s)[0])
        return 0;
    
    // Makes things easier to read...
    char *c = *s;
    
    int runLen = 1;
    char match = *c;
    
    while (*(++c) == match)
        runLen++;
    
    // Caller needs us to update the reader
    *s = c;
    
    return runLen;
}

void CompressString(char *s)
{
    if (!s || !s[0])
        return;
    
    char *reader = s;
    int len = RunLength(&reader);
    
    while(len > 0)
    {
        s++;
        if (len > 1)
        {
            // For this example, we won't bother with runs greater than 9
            *s = len + '0';
            s++;
        }
        
        *s = *reader;
        len = RunLength(&reader);
    }
}

void RunTest(char *s1)
{
    char buffer[1024] = {};
    
    strcpy(buffer, s1);
    
    printf("before: %s\n", buffer);
    CompressString(buffer);
    printf("after: %s\n", buffer);
}


int main(int argc, const char * argv[]) {
    RunTest("aabcccccaaa");
    RunTest("abksjdjdjsieeekeelslkslsssjejifiiiiidijsiisisissssslslslslllllllleieiiieeeuuee");
    RunTest("abiejslenw");
    
    return 0;
}
