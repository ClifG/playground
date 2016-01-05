//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class TrieNode {
private:
    char m_value;
    bool m_isWord;
    TrieNode *m_children[26];
    
public:
    TrieNode(char c)
    : m_value(c)
    , m_isWord(false)
    {
        for (int i = 0; i < 26; i++)
        {
            m_children[i] = nullptr;
        }
    }
    
    virtual ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            if (m_children[i] != nullptr)
            {
                delete m_children[i];
            }
        }
    }
    
    char GetValue()
    {
        return m_value;
    }
    
    bool GetIsWord()
    {
        return m_isWord;
    }
    
    void SetIsWord(bool isWord)
    {
        m_isWord = isWord;
    }
    
    TrieNode* GetChild(char value)
    {
        return m_children[value - 'a'];
    }
    
    TrieNode* GetOrAddChild(char value)
    {
        int index = value - 'a';
        if (!m_children[index])
        {
            m_children[index] = new TrieNode(value);
        }
        
        return m_children[index];
    }
};

TrieNode* BuildDictionary(string dictPath)
{
    TrieNode *root = new TrieNode(' ');
    
    cout << "Loading file: " << dictPath << endl;
    ifstream wordFile(dictPath);
    string line;
    
    while (getline(wordFile, line))
    {
        TrieNode *curr = root;
        for (char c: line)
        {
            curr = curr->GetOrAddChild(tolower(c));
        }
        
        curr->SetIsWord(true);
    }
    
    return root;
}

void PrintWordsInternal(int row, int col, vector<vector<char>> &board, vector<vector<bool>> &visited, int n, string s, int minLength, TrieNode *dict)
{
    if (!dict)
    {
        return;
    }
    
    visited[row][col] = true;
    
    for (int nextRow = max(0, row - 1); nextRow <= min(n - 1, row + 1); nextRow++)
    {
        for (int nextCol = max(0, col - 1); nextCol <= min(n - 1, col + 1); nextCol++)
        {
            if (!visited[nextRow][nextCol])
            {
                TrieNode *nextDict = dict->GetChild(board[nextRow][nextCol]);
                if (nextDict != nullptr)
                {
                    s.push_back(board[nextRow][nextCol]);
                    
                    if ((nextDict->GetIsWord()) && (s.length() >= minLength))
                    {
                        cout << s << endl;
                    }
                    
                    PrintWordsInternal(nextRow, nextCol, board, visited, n, s, minLength, nextDict);
                    
                    s.pop_back();
                }
            }
        }
    }
    
    visited[row][col] = false;
}

void PrintWords(vector<vector<char>> &board, int n, int minLength, TrieNode *dict)
{
    vector<vector<bool>> visited(n, vector<bool>(n));
    string currentString;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            currentString.clear();
            currentString.push_back(board[row][col]);
            PrintWordsInternal(row, col, board, visited, n, currentString, minLength, dict->GetChild(board[row][col]));
        }
    }
}

void PrintBoard(vector<vector<char>> &board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    // Create a dictionary trie. We're responsible for freeing the memory.
    TrieNode *root = BuildDictionary("/usr/share/dict/words");
    
    // Create our board
    int size = 16;
    vector<vector<char>> board(size, vector<char>(4));
    
    sranddev();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = 'a' + (rand() % 26);
        }
    }
    
    PrintBoard(board, size);
    cout << endl << endl;
    
    PrintWords(board, size, 3, root);
    
    delete root;
    return 0;
}
