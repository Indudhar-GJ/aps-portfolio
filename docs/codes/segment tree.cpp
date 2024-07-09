
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <limits>
using namespace std;

vector<long> v, tree;

void createTree(int index, int st, int end)
{
    if (st == end)
    {
        tree[index] = v[st];
        return;
    }

    long mid = (st + end) / 2;
    createTree(2 * index + 1, st, mid);
    createTree(2 * index + 2, mid + 1, end);
    tree[index] = 0;
}

void updateTree(int index, int st, int end, int l, int r, int val)
{
    if (st == end && st == l)
    {
        tree[index] += val;
        return;
    }
    if (end < l || st > r)
    {
        return;
    }
    if (l <= st && end <= r)
    {
        tree[index] += val;
        return;
    }

    long mid = (st + end) / 2;
    updateTree(2 * index + 1, st, mid, l, r, val);
    updateTree(2 * index + 2, mid + 1, end, l, r, val);
}

void propagate(int node)
{
    int left = 2 * node + 1;
    int right = 2 * node + 2;

    tree[left] += tree[node];
    tree[right] += tree[node];

    tree[node] = 0;
}

long long query(int index, int st, int end, int pos)
{
    if (st == end)
    {
        return tree[index];
    }
    propagate(index);
    int mid = (st + end) / 2;

    if (st <= pos && pos <= mid)
    {
        return query(2 * index + 1, st, mid, pos);
    }
    else
    {
        return query(2 * index + 2, mid + 1, end, pos);
    }
}

int main()
{
    int n, q;
    cin >> n >> q;

    v = vector<long>(n, INT_MAX);
    tree = vector<long>(4 * n, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    createTree(0, 0, n - 1);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int a, b, u;
            cin >> a >> b >> u;
            updateTree(0, 0, n - 1, a - 1, b - 1, u);
        }
        else
        {
            int k;
            cin >> k;
            cout << query(0, 0, n - 1, k - 1) << "\n";
        }
    }

    return 0;
}