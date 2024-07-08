#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    bool isEndOfCard;
    TrieNode() : isEndOfCard(false) {}
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie() { root = new TrieNode(); }

    void insert(string cardNumber)
    {
        TrieNode *node = root;
        for (char c : cardNumber)
        {
            if (!node->children.count(c))
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfCard = true;
    }

    bool search(string cardNumber)
    {
        TrieNode *node = root;
        for (char c : cardNumber)
        {
            if (!node->children.count(c))
            {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfCard;
    }
};

int main()
{
    Trie trie;
    trie.insert("1234567890123456");
    trie.insert("9876543210987654");

    cout << (trie.search("1234567890123456") ? "Card is valid" : "Card is invalid") << endl;
    cout << (trie.search("1111222233334444") ? "Card is valid" : "Card is invalid") << endl;

    return 0;
}
