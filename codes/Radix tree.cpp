#include <iostream>
#include <vector>
using namespace std;

struct TrieNode
{
    TrieNode *children[26];
    bool isEndOfWord;

    TrieNode()
    {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }
};

void insert(TrieNode *root, const string &key)
{
    TrieNode *current = root;
    for (char c : key)
    {
        if (!current->children[c - 'a'])
        {
            current->children[c - 'a'] = new TrieNode();
        }
        current = current->children[c - 'a'];
    }
    current->isEndOfWord = true;
}

bool search(TrieNode *root, const string &key)
{
    TrieNode *current = root;
    for (char c : key)
    {
        if (!current->children[c - 'a'])
        {
            return false;
        }
        current = current->children[c - 'a'];
    }
    return current->isEndOfWord;
}

int main()
{
    TrieNode *root = new TrieNode();
    vector<string> words = {"and", "ant", "do", "geek", "dad", "ball"};

    for (const string &word : words)
    {
        insert(root, word);
    }

    vector<string> queries = {"do", "geek", "bat"};

    for (const string &query : queries)
    {
        cout << "Query: " << query << "\n";
        if (search(root, query))
        {
            cout << "Present in Trie\n";
        }
        else
        {
            cout << "Not present in Trie\n";
        }
    }

    return 0;
}
