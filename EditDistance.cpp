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

void PrintMatrix(char *s1, char *s2, vector<vector<int>> *M)
{
    printf("0 0 ");
    while (*s1)
    {
        printf ("%c ", *s1);
        s1++;
    }
    printf("\n");
    
    for (int i = 0; i < (*M).size(); i++)
    {
        if (i == 0)
            printf("0 ");
        else
            printf("%c ", s2[i - 1]);
        
        for (int j = 0; j < (*M)[0].size(); j++)
        {
            printf("%d ", (*M)[i][j]);
        }
        
        printf ("\n");
    }
    
    printf("\n");
}

int EditDistance(char *s1, char *s2)
{
    if (!s1 || !s2)
        return -1;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    vector<vector<int> > M(len2 + 1, vector<int>(len1 + 1));
    
    for (int i = 0; i <= len1; i++)
    {
        M[0][i] = i;
    }
    
    for (int j = 0; j <= len2; j++)
    {
        M[j][0] = j;
    }
    
    for (int j = 1; j <= len2; j++)
    {
        for (int i = 1; i <= len1; i++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                M[j][i] = M[j - 1][i - 1];
            }
            else
            {
                int dist = min(M[j-1][i], M[j][i - 1]);
                dist = min(dist, M[j - 1][i - 1]);
            
                M[j][i] = dist + 1;
            }
        }
    }
    
    PrintMatrix(s1, s2, &M);
    
    return M[len2][len1];
    
}

void RunTest(char *s1, char *s2)
{
    int dist = EditDistance(s1, s2);
    printf("[%s], [%s]: %d\n", s1, s2, dist);
}


int main(int argc, const char * argv[]) {
    RunTest("this is the first string", "this is another string");
    RunTest("book", "bokop");
    RunTest("boo", "bo");
    
    return 0;
}
