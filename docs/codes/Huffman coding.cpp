#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct HuffmanNode
{
    char data;
    int frequency;
    HuffmanNode *left, *right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNodes
{
    bool operator()(HuffmanNode *left, HuffmanNode *right)
    {
        return left->frequency > right->frequency;
    }
};

HuffmanNode *buildHuffmanTree(const unordered_map<char, int> &frequencies)
{
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;

    for (auto &pair : frequencies)
    {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();

        HuffmanNode *newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode *root, string code, unordered_map<char, string> &huffmanCodes)
{
    if (root == nullptr)
    {
        return;
    }

    if (!root->left && !root->right)
    {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

string compress(const string &input)
{
    unordered_map<char, int> frequencies;
    for (char c : input)
    {
        frequencies[c]++;
    }

    HuffmanNode *root = buildHuffmanTree(frequencies);

    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    string encodedString;
    for (char c : input)
    {
        encodedString += huffmanCodes[c];
    }

    return encodedString;
}

string decompress(const string &encodedString, HuffmanNode *root)
{
    string decodedString;
    HuffmanNode *current = root;

    for (char bit : encodedString)
    {
        if (bit == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        if (!current->left && !current->right)
        {
            decodedString += current->data;
            current = root;
        }
    }

    return decodedString;
}

int main()
{
    string input;

    cout << "Enter a string to compress using Huffman coding: ";
    getline(cin, input);

    string compressed = compress(input);
    cout << "Compressed string: " << compressed << endl;

    HuffmanNode *root = buildHuffmanTree({{'a', 1}, {'b', 1}}); // Placeholder frequencies for example
    string decompressed = decompress(compressed, root);
    cout << "Decompressed string: " << decompressed << endl;

    return 0;
}
