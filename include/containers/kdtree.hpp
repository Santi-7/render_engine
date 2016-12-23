/* ---------------------------------------------------------------------------
 ** kdtree.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_KDTREE_HPP
#define RAY_TRACER_KDTREE_HPP

/*********************************************************************************
This code has been adapted from Adrian Jarabo's & Diego Gutierrez's implementation,
whis is also adapted from Adolfo Munoz's Mjolnir-RT, developed at Universidad
de Zaragoza (Spain).
**********************************************************************************/

#include <algorithm>
#include <dimensions.hpp>
#include <list>
#include <math.h>
#include <point.hpp>
#include <vector>

using namespace std;

template<class T>
class Node {
    
public:

    Node() : mAxis(NO_DIM) {}

    Node(const Point &point, const T &data) : mAxis(NO_DIM), mPoint(point), mData(data) {}

    Point &GetPoint() const { return mPoint; }

    T &GetData() const { return mData; }

private:

    Dimension mAxis;
    Point mPoint;
    T mData;
};

template<class T>
class KDTree {

public:

    KDTree() {}

    void Clear();

    void Store(const Point &point, const T &data);

    // Fixed Radius
    int Find(const Point &p, float radius, list<const Node<T> *> *nodes) const;

    // Nearest Neighbor search
    void Find(const Point &p, int nb_elements, vector<const Node<T> *> &nodes, float &max_distance) const;

    Node<T> &Find(const Point &p) const;

    void Balance();

    inline int Size() const;

    inline bool IsEmpty() const;

    inline Node<T> &operator[](const unsigned int idx) const;

private:

    list<Node<T>> mNodes;
    vector<Node<T>> mBalanced;

    static void MedianSplit(vector<Node<T>> &p, int start, int end, int median, int axis);

    static void BalanceSegment(vector<Node<T>> &pbal, vector<Node<T>> &porg, int index,
                               int start, int end, const Point &bbmin, const Point &bbmax);

    int Closest(const Point &p, int index, int best) const;

    void Find(const Point &p, int index, float radius, list<const Node<T> *> &nodes) const;

    void Find(const Point &p, int index, int nb_elements, float &dist_worst, vector<const Node<T> *> &nodes,
              vector<pair<int, float>> &dist) const;

    //I've removed static for compiling problems
    //static class HeapComparison
    class HeapComparison {
    public:
        bool operator()(const pair<int, float> &val1, const pair<int, float> &val2) const {
            return val1.second < val2.second;
        }
    };

    void UpdateHeapNodes(const Node<T> &node, const float distance, int nb_elements,
                         vector<const Node<T> *> &nodes, vector<pair<int, float>> &dist) const;
};

#endif // RAY_TRACER_KDTREE_HPP