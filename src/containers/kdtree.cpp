/* ---------------------------------------------------------------------------
 ** kdtree.cpp
 ** Implementation for KDTree class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <kdtree.hpp>
#include <fstream>

void KDTree::Clear() {
    mNodes.clear();
    mBalanced.clear();
}

void KDTree::Store(const Point &point, const Photon &photon) {
    mNodes.push_back(Node(point, photon));
}

//========================================================================================================
// Fixed Radius
unsigned int KDTree::Find(const Point &p, const float radius, list<const Node *> *nodes) const {
    if (nodes) {
        Find(p, 1, radius, *nodes);
        return static_cast<unsigned int>(nodes->size());
    }
    else {
        list<const Node *> local_nodes;
        Find(p, 1, radius, local_nodes);
        return static_cast<unsigned int>(local_nodes.size());
    }
}

//========================================================================================================
// Nearest Neighbor search
void KDTree::Find(const Point &p, const unsigned int nb_elements, vector<const Node *> &nodes, float &max_distance) const {
    nodes.clear();
    max_distance = numeric_limits<float>::infinity();

    if (mBalanced.empty())
        return;

    nodes.reserve(nb_elements);
    vector<pair<unsigned int, float> > dist;
    dist.reserve(nb_elements);

    Find(p, 1, nb_elements, max_distance, nodes, dist);
}

const Node &KDTree::Find(const Point &p) const {
    return mBalanced[Closest(p, 1, 1)];
}

unsigned int KDTree::Size() const {
    return static_cast<unsigned int>(mBalanced.size());
}

bool KDTree::IsEmpty() const {
    return mBalanced.empty();
}

const Node &KDTree::operator[](const unsigned int idx) const {
#ifdef _SAFE_CHECK_
    if ( idx > mBalanced.size()-1) throw("Out-of-range");
#endif
    return mBalanced[idx];
}

//--------------------------------------------------------------------------------------------------
//Private Find(radius)
void KDTree::Find(const Point &p, const unsigned int index, const float radius, list<const Node *> &nodes) const {
    //We check if our node enters
    if (mBalanced[index].mPoint.Distance(p) < radius) { nodes.push_back(&mBalanced[index]); }
    //Now we check that this is not a leaf node
    if (index < ((mBalanced.size() - 1) / 2)) {
        float distaxis = p[mBalanced[index].mAxis] - mBalanced[index].mPoint[mBalanced[index].mAxis];
        if (distaxis < 0.0) // left node first
        {
            Find(p, 2 * index, radius, nodes);
            if (radius > fabs(distaxis)) // Maybe we can Find more mNodes on the other child
                Find(p, 2 * index + 1, radius, nodes);
        }
        else //right node first
        {
            Find(p, 2 * index + 1, radius, nodes);
            if (radius > fabs(distaxis)) // Maybe we can Find more mNodes on the other child
                Find(p, 2 * index, radius, nodes);
        }
    }
}

//--------------------------------------------------------------------------------------------------
//Private Find(N-Nearest Neighbors)
void KDTree::UpdateHeapNodes(const Node &node, const float distance, const unsigned int nb_elements,
                             vector<const Node *> &nodes, vector<pair<unsigned int, float>> &dist) const {
    // If there's still buffer for  more, don't bother with heaps...
    if (nodes.size() < nb_elements) {
        dist.push_back(pair<unsigned int, float>(nodes.size(), distance));
        nodes.push_back(&node);

        //...unless you've reach max size, then prepare the heap...
        if (nodes.size() == nb_elements)
            make_heap(dist.begin(), dist.end(), HeapComparison());
    }
    else {
        int idx = dist.front().first;
        nodes[idx] = &node;
        // Pop removed element
        pop_heap(dist.begin(), dist.end(), HeapComparison());
        dist.pop_back();
        // Push new one
        dist.push_back(pair<unsigned int, float>(idx, distance));
        push_heap(dist.begin(), dist.end(), HeapComparison());
    }
    //if( !(mNodes.size() < nb_elements) )
    //{	mNodes.pop_back();dist.pop_back(); }
    //
    //mNodes.push_back(&node);
    //dist.push_back(distance);

    //for(int j=0; j<mNodes.size(); ++j)
    //for(int i=0; i<mNodes.size()-1; ++i)
    //{
    //	if( dist[i] > dist[i+1] )
    //	{
    //		const Node* aux_node = mNodes[i];
    //		mNodes[i] = mNodes[i+1];
    //		mNodes[i+1] = aux_node;
    //		float aux_dist = dist[i];
    //		dist[i] = dist[i+1];
    //		dist[i+1] = aux_dist;
    //	}
    //}
}

void KDTree::Find(const Point &p, unsigned int index, const unsigned int nb_elements, float &dist_worst,
                  vector<const Node *> &nodes, vector<pair<unsigned int, float>> &dist) const {
    float aux;
    //We check if our node is better
    if ((aux = mBalanced[index].mPoint.Distance(p)) < dist_worst) {
        UpdateHeapNodes(mBalanced[index], aux, nb_elements, nodes, dist);
        dist_worst = (nodes.size() < nb_elements) ? numeric_limits<float>::infinity() : dist.front().second;
    }

    //Now we check that this is not a leaf node
    if (index < ((mBalanced.size() - 1) / 2)) {
        float distaxis = p[mBalanced[index].mAxis] - mBalanced[index].mPoint[mBalanced[index].mAxis];
        //if( dist_worst < fabs(distaxis) )
        //	return;

        if (distaxis < 0.0) // left node first
        {
            Find(p, 2 * index, nb_elements, dist_worst, nodes, dist);
            if (dist_worst > fabs(distaxis)) // Maybe we can Find more mNodes on the other child
                Find(p, 2 * index + 1, nb_elements, dist_worst, nodes, dist);
        }
        else //right node first
        {
            Find(p, 2 * index + 1, nb_elements, dist_worst, nodes, dist);
            if (dist_worst > fabs(distaxis)) // Maybe we can Find more mNodes on the other child
                Find(p, 2 * index, nb_elements, dist_worst, nodes, dist);
        }
    }
}

//--------------------------------------------------------------------------------------------------
// Closest
unsigned int KDTree::Closest(const Point &p, const unsigned int index, const unsigned int best) const {
    unsigned int sol = best;
    float distbest = p.Distance(mBalanced[best].mPoint);
    float aux;
    //We check if our node is better
    if ((aux = mBalanced[index].mPoint.Distance(p)) < distbest) {
        sol = index;
        distbest = aux;
    }
    //Now we check that this is not a leaf node
    if (index < ((mBalanced.size() - 1) / 2)) {
        float distaxis = p[mBalanced[index].mAxis] - mBalanced[index].mPoint[mBalanced[index].mAxis];
        if (distaxis < 0.0) // left node first
        {
            unsigned int candidate = Closest(p, 2 * index, sol);
            if ((aux = mBalanced[candidate].mPoint.Distance(p)) < distbest) {
                sol = candidate;
                distbest = aux;
            }
            if (distbest > fabs(distaxis)) // Maybe the best solution is on the other side
            {
                candidate = Closest(p, 2 * index + 1, sol);
                if (mBalanced[candidate].mPoint.Distance(p) < distbest) {
                    sol = candidate;
                }
            }
        }
        else //right node first
        {
            unsigned int candidate = Closest(p, 2 * index + 1, sol);
            if ((aux = mBalanced[candidate].mPoint.Distance(p)) < distbest) {
                sol = candidate;
                distbest = aux;
            }
            if (distbest > fabs(distaxis)) // Maybe the best solution is on the other side
            {
                candidate = Closest(p, 2 * index, sol);
                if (mBalanced[candidate].mPoint.Distance(p) < distbest) {
                    sol = candidate;
                }
            }
        }
    }
    return sol;
}

#define myswap(array, a, b) { Node aux=(array)[(a)]; (array)[(a)]=(array)[(b)]; (array)[(b)] = aux; }

//--------------------------------------------------------------------------------------------------
//Balance Tree
void KDTree::MedianSplit(vector<Node> &p, const int start, const int end, const int median, const Dimension &axis) {
    int left = start;
    int right = end;

    while (right > left) {
        float v = p[right].mPoint[axis];
        int i = left - 1;
        int j = right;
        for (;;) {
            while (v > p[++i].mPoint[axis]);
            while (v < p[--j].mPoint[axis] && j > left);
            if (i >= j)
                break;
            myswap(p, i, j);
        }

        myswap(p, i, right);
        if (i >= median)
            right = i - 1;
        if (i <= median)
            left = i + 1;
    }
}

void KDTree::BalanceSegment(vector<Node> &pbal, vector<Node> &porg, const int index, const int start, const int end,
                            const Point &bbmin, const Point &bbmax) {
    int median = 1;
    while ((4 * median) <= (end - start + 1))
        median += median;

    if ((3 * median) <= (end - start + 1)) {
        median += median;
        median += start - 1;
    } else
        median = end - median + 1;

    // elegimos el eje más apropiado...
    Dimension axis = bbmax.LongestDimension(bbmin);

    // partimos el bloque de fotones por la mediana
    MedianSplit(porg, start, end, median, axis);

    pbal[index] = porg[median];
    pbal[index].mAxis = axis;

    // y por último balanceamos recursivamente los bloques izquierdo y derecho
    if (median > start) {
        // balancear el segmento izquierdo
        if (start < median - 1) {
            Point newbbmax = bbmax;
            newbbmax.SetDimension(axis, pbal[index].mPoint[axis]);
            BalanceSegment(pbal, porg, 2 * index, start, median - 1, bbmin, newbbmax);
        } else {
            pbal[2 * index] = porg[start];
        }
    }

    if (median < end) {
        // balancear el segmento derecho
        if (median + 1 < end) {
            Point newbbmin = bbmin;
            newbbmin.SetDimension(axis, pbal[index].mPoint[axis]);
            BalanceSegment(pbal, porg, 2 * index + 1, median + 1, end, newbbmin, bbmax);
        } else {
            pbal[2 * index + 1] = porg[end];
        }
    }
}

void KDTree::Balance() {
    if (mNodes.size() == 0) return;
    vector<Node> aux(mNodes.size() + 1);
    mBalanced.resize(mNodes.size() + 1);
    int i;
    Point bbmax = mNodes.front().mPoint;
    Point bbmin = mNodes.front().mPoint;
    //mBalanced[0] and aux[0] do not contain any useful information
    for (i = 1; !(mNodes.empty()); i++, mNodes.pop_front()) {
        aux[i] = mNodes.front();
        // X dimension.
        if (aux[i].mPoint[X] < bbmin[X]) bbmin.SetX(aux[i].mPoint[X]);
        if (aux[i].mPoint[X] > bbmax[X]) bbmax.SetX(aux[i].mPoint[X]);
        // Y dimension.
        if (aux[i].mPoint[Y] < bbmin[Y]) bbmin.SetY(aux[i].mPoint[Y]);
        if (aux[i].mPoint[Y] > bbmax[Y]) bbmax.SetY(aux[i].mPoint[Y]);
        // X dimension.
        if (aux[i].mPoint[Z] < bbmin[Z]) bbmin.SetZ(aux[i].mPoint[Z]);
        if (aux[i].mPoint[Z] > bbmax[Z]) bbmax.SetZ(aux[i].mPoint[Z]);
    }
    mNodes.clear();

    BalanceSegment(mBalanced, aux, 1, 1, static_cast<unsigned int>(mBalanced.size()) - 1, bbmin, bbmax);
}

void KDTree::DumpToFile(const string& filename)
{
    ofstream out(filename);
    for (const Node &p : mBalanced)
    {
        float x = p.GetPoint().GetX();
        float y = p.GetPoint().GetY();
        float z = p.GetPoint().GetZ();
        out << x << ' ' << y << ' ' << z << '\n';
    }
    out.close();
}
