#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point
{
    vector<double> coordinates;
    int dimension() const
    {
        return coordinates.size();
    }
};

struct PointComparator
{
    int dim;
    PointComparator(int d) : dim(d) {}
    bool operator()(const Point &p1, const Point &p2) const
    {
        return p1.coordinates[dim] < p2.coordinates[dim];
    }
};

struct KDNode
{
    Point point;
    KDNode *left;
    KDNode *right;
    KDNode(const Point &p) : point(p), left(nullptr), right(nullptr) {}
};

KDNode *buildKDTree(vector<Point> &points, int depth = 0)
{
    if (points.empty())
        return nullptr;

    int dim = depth % points[0].dimension();
    sort(points.begin(), points.end(), PointComparator(dim));

    int medianIndex = points.size() / 2;
    KDNode *node = new KDNode(points[medianIndex]);

    vector<Point> leftPoints(points.begin(), points.begin() + medianIndex);
    vector<Point> rightPoints(points.begin() + medianIndex + 1, points.end());

    node->left = buildKDTree(leftPoints, depth + 1);
    node->right = buildKDTree(rightPoints, depth + 1);

    return node;
}

void nearestNeighborSearch(KDNode *root, const Point &target, KDNode *&best, double &bestDist, int depth = 0)
{
    if (root == nullptr)
        return;

    double dist = 0;
    for (int i = 0; i < target.dimension(); ++i)
    {
        dist += (root->point.coordinates[i] - target.coordinates[i]) * (root->point.coordinates[i] - target.coordinates[i]);
    }
    dist = sqrt(dist);

    if (best == nullptr || dist < bestDist)
    {
        best = root;
        bestDist = dist;
    }

    int dim = depth % target.dimension();
    KDNode *nextBranch = nullptr;
    KDNode *otherBranch = nullptr;

    if (target.coordinates[dim] < root->point.coordinates[dim])
    {
        nextBranch = root->left;
        otherBranch = root->right;
    }
    else
    {
        nextBranch = root->right;
        otherBranch = root->left;
    }

    cout << "Checking node with coordinates (";
    for (size_t i = 0; i < root->point.coordinates.size(); ++i)
    {
        cout << root->point.coordinates[i];
        if (i < root->point.coordinates.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "), current best distance: " << bestDist << endl;

    nearestNeighborSearch(nextBranch, target, best, bestDist, depth + 1);

    if ((target.coordinates[dim] - root->point.coordinates[dim]) * (target.coordinates[dim] - root->point.coordinates[dim]) < bestDist)
    {
        nearestNeighborSearch(otherBranch, target, best, bestDist, depth + 1);
    }
}

int main()
{
    vector<Point> points = {
        {{2.0, 3.0}},
        {{5.0, 4.0}},
        {{9.0, 6.0}},
        {{4.0, 7.0}},
        {{8.0, 1.0}},
        {{7.0, 2.0}}};

    KDNode *root = buildKDTree(points);

    Point target = {{9.0, 2.0}};
    KDNode *best = nullptr;
    double bestDist = numeric_limits<double>::max();

    nearestNeighborSearch(root, target, best, bestDist);

    if (best)
    {
        cout << "\nNearest neighbor found at: (";
        for (size_t i = 0; i < best->point.coordinates.size(); ++i)
        {
            cout << best->point.coordinates[i];
            if (i < best->point.coordinates.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << ") with distance " << bestDist << endl;
    }
    else
    {
        cout << "No nearest neighbor found." << endl;
    }

    return 0;
}
