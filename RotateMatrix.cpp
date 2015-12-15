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

void PrintMatrix(vector<vector<int>> &M)
{
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++)
        {
            printf ("%d ", M[i][j]);
        }
        printf ("\n");
    }
    printf("\n");
}

void RotateMatrix(vector<vector<int>> &m)
{
    // Matrix is NxN so there are N/2 "levels" as we work inward. It's okay
    // to ignore a remainder of 1, the innermost level of an odd-dimension matrix
    // will be a single element and no need to rotate.
    
    int n = m.size() - 1;

    for (int level = 0; level < ((n+1) / 2); level++)
    {
        for (int i = level; i < (n - level); i++)
        {
            // Save the bottom-left value
            int saved = m[n - i][level];
            
            // Bottom left takes bottom right value
            m[n - i][level] = m[n - level][n - i];
            
            // Bottom right takes top right value
            m[n - level][n - i] = m[i][n - level];
            
            // Top right takes top left value
            m[i][n - level] = m[level][i];
            
            // Top left takes saved bottom left value
            m[level][i] = saved;
        }
    }
}


int main(int argc, const char * argv[]) {
    
    vector<vector<int>> m(6, vector<int>(6));
    
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            m[i][j] = (i * 6) + j;
        }
    }
    
    PrintMatrix(m);
    
    RotateMatrix(m);
    
    PrintMatrix(m);
    
    printf("\n****************\n");
    
    vector<vector<int>> m2(5, vector<int>(5));
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            m2[i][j] = (i * 5) + j;
        }
    }
    
    PrintMatrix(m2);
    
    RotateMatrix(m2);

    PrintMatrix(m2);
    
    return 0;
}
