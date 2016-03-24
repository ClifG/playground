//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

class Trie
{
private:
    struct Node
    {
        Node* children[26];
        bool isWord;
        
        Node() : isWord(false)
        {
            for (int i = 0; i < 26; i++)
            {
                children[i] = nullptr;
            }
        }
        
        virtual ~Node()
        {
            for (int i = 0; i < 26; i++)
            {
                if (children[i])
                {
                    delete children[i];
                }
            }
        }
    };
    
private:
    Node _root;
    
    Node* _GetPath(char* s)
    {
        if (!s || !*s)
        {
            return nullptr;
        }
        
        Node* p = &_root;
        while(*s)
        {
            if (p->children[_ToLower(*s) - 'a'])
            {
                p = p->children[_ToLower(*s) - 'a'];
            }
            else
            {
                return nullptr;
            }
            
            s++;
        }
        
        return p;
    }
    
    char _ToLower(char c)
    {
        if (c >= 'A' && c <= 'Z')
            return (c - 'A') + 'a';
        return c;
    }
    
public:
    Trie() {}
    virtual ~Trie() {}
    
    void Insert(const char *s)
    {
        if (!s || !*s)
        {
            return;
        }
        
        Node *p = &_root;
        while (*s)
        {
            int value = _ToLower(*s) - 'a';
            if (!p->children[value])
            {
                p->children[value] = new Node();
            }
            p = p->children[value];
            s++;
        }
        
        p->isWord = true;
    }
    
    bool IsValidPath(char *s)
    {
        Node* p = _GetPath(s);
        return (p != nullptr);
    }
    
    bool IsWord(char *s)
    {
        Node* p = _GetPath(s);
        return (p && p->isWord);
    }
    
    
};

void FillTrie(string filePath, Trie *trie)
{
    if (!trie)
        return;
    
    ifstream dictFile(filePath);
    string line;
    
    while (getline(dictFile, line))
    {
        trie->Insert(line.c_str());
    }
}

static const char* keyMap[] =
{
    "",    //0
    "",    //1
    "abc", //2
    "def", //3
    "ghi", //4
    "jkl", //5
    "mno", //6
    "prs", //7
    "tuv", //8
    "wxy"  //9
};

void _PrintWords(const char* number, char* word, int idx, Trie *trie)
{
    if (!number[idx])
    {
        if (trie->IsWord(word))
        {
            printf("%s\n", word);
        }
        return;
    }
    
    const char* letters = keyMap[number[idx] - '0'];
    while (*letters)
    {
        word[idx] = *letters;
        if (trie->IsValidPath(word))
        {
            _PrintWords(number, word, idx + 1, trie);
        }
        letters++;
    }
    word[idx] = '\0';
}

void PrintWords(const char* number)
{
    static Trie trie;
    static bool trieInitialized = false;
    
    // Note: Not thread-safe
    if (!trieInitialized)
    {
        FillTrie("/usr/share/dict/words", &trie);
        trieInitialized = true;
    }
    
    std::unique_ptr<char[]> word(new char[strlen(number) + 1]());
    _PrintWords(number, word.get(), 0, &trie);
}

int main(int argc, const char * argv[]) {
    printf("9673:\n");
    PrintWords("9673");
    
    printf("\n\n44678:\n");
    PrintWords("44678");
    
    printf("\n\n323:\n");
    PrintWords("323");
    
    printf("\n\n382736372637236:\n");
    PrintWords("382736372637236");
    
    printf("done!\n");
    
    return 0;
}
