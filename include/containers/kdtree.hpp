/** ---------------------------------------------------------------------------
 ** kdtree.hpp
 ** 3-dimensional tree structure that stores nodes that consist of a point and
 ** a photon.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_KDTREE_HPP
#define RAY_TRACER_KDTREE_HPP

/*********************************************************************************
This code has been adapted from Adrian Jarabo's & Diego Gutierrez's implementation,
which is also adapted from Adolfo Munoz's Mjolnir-RT, developed at Universidad
de Zaragoza (Spain).
**********************************************************************************/

#include <algorithm>
#include <dimensions.hpp>
#include <list>
#include <math.h>
#include <photon.hpp>
#include <point.hpp>
#include <vector>

using namespace std;

class Node {

friend class KDTree;

public:

    Node() : mAxis(NO_DIM) {}

    Node(const Point &point, const Photon &photon) : mAxis(NO_DIM), mPoint(point), mPhoton(photon) {}

    Point GetPoint() const { return mPoint; }

    Photon GetData() const { return mPhoton; }

private:

    Dimension mAxis;
    Point mPoint;
    Photon mPhoton;
};

class KDTree {

public:

    KDTree() {}

    void Clear();

    void Store(const Point &point, const Photon &photon);

    // Fixed Radius
    unsigned int Find(const Point &p, const float radius, list<const Node *> *nodes) const;

    // Nearest Neighbor search
    void Find(const Point &p, const unsigned int nb_elements, vector<const Node *> &nodes, float &max_distance) const;

    const Node &Find(const Point &p) const;

    void Balance();

    unsigned int Size() const;

    bool IsEmpty() const;

    const Node &operator[](const unsigned int idx) const;

private:

    list<Node> mNodes;
    vector<Node> mBalanced;

    static void MedianSplit(vector<Node> &p, const int start, const int end, const int median, const Dimension &axis);

    static void BalanceSegment(vector<Node> &pbal, vector<Node> &porg, const int index,
                               const int start, const int end, const Point &bbmin, const Point &bbmax);

    unsigned int Closest(const Point &p, const unsigned int index, const unsigned int best) const;

    void Find(const Point &p, const unsigned int index, const float radius, list<const Node *> &nodes) const;

    void Find(const Point &p, const unsigned int index, const unsigned int nb_elements, float &dist_worst, vector<const Node *> &nodes,
              vector<pair<unsigned int, float>> &dist) const;

    // Removed static for compiling problems
    //static class HeapComparison
    class HeapComparison {
    public:
        bool operator()(const pair<int, float> &val1, const pair<int, float> &val2) const {
            return val1.second < val2.second;
        }
    };

    void UpdateHeapNodes(const Node &node, const float distance, const unsigned int nb_elements,
                         vector<const Node *> &nodes, vector<pair<unsigned int, float>> &dist) const;
};

#endif // RAY_TRACER_KDTREE_HPP