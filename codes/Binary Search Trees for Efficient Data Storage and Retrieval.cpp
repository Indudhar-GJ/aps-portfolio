#include <iostream>
using namespace std;

struct Transaction
{
    int id;
    double amount;
    Transaction(int id, double amount) : id(id), amount(amount) {}
};

struct Node
{
    Transaction *data;
    Node *left;
    Node *right;
    Node(Transaction *data) : data(data), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    Node *root;

    void insert(Node *&node, Transaction *data)
    {
        if (!node)
        {
            node = new Node(data);
            return;
        }
        if (data->amount < node->data->amount)
        {
            insert(node->left, data);
        }
        else
        {
            insert(node->right, data);
        }
    }

    void inOrder(Node *node)
    {
        if (node)
        {
            inOrder(node->left);
            cout << "Transaction ID: " << node->data->id << ", Amount: " << node->data->amount << endl;
            inOrder(node->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(Transaction *data)
    {
        insert(root, data);
    }

    void inOrder()
    {
        inOrder(root);
    }
};

int main()
{
    BST bst;
    bst.insert(new Transaction(1, 100.0));
    bst.insert(new Transaction(2, 50.0));
    bst.insert(new Transaction(3, 200.0));
    bst.insert(new Transaction(4, 150.0));

    cout << "In-Order Traversal of Transactions:" << endl;
    bst.inOrder();

    return 0;
}
