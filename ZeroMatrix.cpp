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

void ZeroMatrix(vector<vector<int>> &M)
{
    int rows = M.size();
    
    if (rows <= 0)
        return;
    
    int cols = M[0].size();
    
    bool markRows[rows];
    for (int i = 0; i < rows; i++)
        markRows[i] = false;
    
    bool markCols[cols];
    for (int j = 0; j < cols; j++)
        markCols[j] = false;
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (M[i][j] == 0)
            {
                markRows[i] = true;
                markCols[j] = true;
            }
        }
    }
    
    for (int i = 0; i < rows; i++)
    {
        if (markRows[i])
        {
            for (int j = 0; j < cols; j++)
                M[i][j] = 0;
        }
    }
    
    for (int j = 0; j < cols; j++)
    {
        if (markCols[j])
            for (int i = 0; i < rows; i++)
                M[i][j] = 0;
    }
}

int main(int argc, const char * argv[]) {
    int rows = rand() % 10 + 1;
    int cols = rand() % 10 + 1;
    vector<vector<int>> m(rows, vector<int>(cols));
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            m[i][j] = rand() % 10;
        }
    }
    
    PrintMatrix(m);
    
    ZeroMatrix(m);
    
    PrintMatrix(m);
    
    return 0;
}
