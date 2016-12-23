/* ---------------------------------------------------------------------------
 ** kdtree.cpp
 ** Implementation for KDTree class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <kdtree.hpp>

template<class T>
void KDTree<T>::Clear() {
    mNodes.clear();
    mBalanced.clear();
}

template<class T>
void KDTree<T>::Store(const Point &point, const T &data) {
    mNodes.push_back(Node<T>(point, data));
}

//========================================================================================================
// Fixed Radius
template<class T>
int KDTree<T>::Find(const Point &p, float radius, list<const Node<T> *> *nodes) const {
    if (nodes) {
        Find(p, 1, radius, *nodes);
        return nodes->size();
    }
    else {
        list<const Node<T> *> local_nodes;
        Find(p, 1, radius, local_nodes);
        return local_nodes.size();
    }
}

//========================================================================================================
// Nearest Neighbor search
template<class T>
void KDTree<T>::Find(const Point &p, int nb_elements, std::vector<const Node<T> *> &nodes, float &max_distance) const {
    nodes.clear();
    max_distance = std::numeric_limits<float>::infinity();

    if (mBalanced.empty())
        return;

    nodes.reserve(nb_elements);
    std::vector<pair<int, float> > dist;
    dist.reserve(nb_elements);

    Find(p, 1, nb_elements, max_distance, nodes, dist);
}

template<class T>
Node<T> &KDTree<T>::Find(const Point &p) const {
    return mBalanced[Closest(p, 1, 1)];
}

template<class T>
int KDTree<T>::Size() const {
    return mBalanced.size();
}

template<class T>
bool KDTree<T>::IsEmpty() const {
    return mBalanced.empty();
}

template<class T>
Node<T> &KDTree<T>::operator[](const unsigned int idx) const {
#ifdef _SAFE_CHECK_
    if ( idx > mBalanced.size()-1) throw("Out-of-range");
#endif
    return mBalanced[idx];
}

//--------------------------------------------------------------------------------------------------
//Private Find(radius)
template<class T>
void KDTree<T>::Find(const Point &p, int index, float radius, list<const Node<T> *> &nodes) const {
    //We check if our node enters
    if (mBalanced[index].GetPoint().Distance(p) < radius) { nodes.push_back(&mBalanced[index]); }
    //Now we check that this is not a leaf node
    if (index < ((mBalanced.size() - 1) / 2)) {
        float distaxis = p[mBalanced[index].mAxis] - mBalanced[index].GetPoint()[mBalanced[index].mAxis];
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
template<class T>
void KDTree<T>::UpdateHeapNodes(const Node<T> &node, const float distance, int nb_elements,
                                std::vector<const Node<T> *> &nodes, std::vector<pair<int, float> > &dist) const {
    // If there's still buffer for  more, don't bother with heaps...
    if (nodes.size() < nb_elements) {
        dist.push_back(pair<int, float>(nodes.size(), distance));
        nodes.push_back(&node);

        //...unless you've reach max size, then prepare the heap...
        if (nodes.size() == nb_elements)
            std::make_heap(dist.begin(), dist.end(), HeapComparison());
    }
    else {
        int idx = dist.front().first;
        nodes[idx] = &node;
        // Pop removed element
        pop_heap(dist.begin(), dist.end(), HeapComparison());
        dist.pop_back();
        // Push new one
        dist.push_back(pair<int, float>(idx, distance));
        push_heap(dist.begin(), dist.end(), HeapComparison());
    }
    //if( !(mNodes.size() < Size) )
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

template<class T>
void KDTree<T>::Find(const Point &p, int index, int nb_elements, float &dist_worst,
                     std::vector<const Node<T> *> &nodes, std::vector<pair<int, float> > &dist) const {
    float aux;
    //We check if our node is better
    if ((aux = mBalanced[index].GetPoint().Distance(p)) < dist_worst) {
        UpdateHeapNodes(mBalanced[index], aux, nb_elements, nodes, dist);
        dist_worst = (nodes.size() < nb_elements) ? numeric_limits<float>::infinity() : dist.front().second;
    }

    //Now we check that this is not a leaf node
    if (index < ((mBalanced.size() - 1) / 2)) {
        float distaxis = p[mBalanced[index].mAxis] - mBalanced[index].GetPoint()[mBalanced[index].mAxis];
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
template<class T>
int KDTree<T>::Closest(const Point &p, int index, int best) const {
    int sol = best;
    float distbest = p.Distance(mBalanced[best].GetPoint());
    float aux;
    //We check if our node is better
    if ((aux = mBalanced[index].GetPoint().Distance(p)) < distbest) {
        sol = index;
        distbest = aux;
    }
    //Now we check that this is not a leaf node
    if (index < ((mBalanced.size() - 1) / 2)) {
        float distaxis = p[mBalanced[index].mAxis] - mBalanced[index].GetPoint()[mBalanced[index].mAxis];
        if (distaxis < 0.0) // left node first
        {
            int candidate = Closest(p, 2 * index, sol);
            if ((aux = mBalanced[candidate].GetPoint().Distance(p)) < distbest) {
                sol = candidate;
                distbest = aux;
            }
            if (distbest > fabs(distaxis)) // Maybe the best solution is on the other side
            {
                candidate = Closest(p, 2 * index + 1, sol);
                if ((aux = mBalanced[candidate].GetPoint().Distance(p)) < distbest) {
                    sol = candidate;
                }
            }
        }
        else //right node first
        {
            int candidate = Closest(p, 2 * index + 1, sol);
            if ((aux = mBalanced[candidate].GetPoint().Distance(p)) < distbest) {
                sol = candidate;
                distbest = aux;
            }
            if (distbest > fabs(distaxis)) // Maybe the best solution is on the other side
            {
                candidate = Closest(p, 2 * index, sol);
                if ((aux = mBalanced[candidate].GetPoint().Distnace(p)) < distbest) {
                    sol = candidate;
                }
            }
        }
    }
    return sol;
}

#define myswap(array, a, b) { Node<T> aux=(array)[(a)]; (array)[(a)]=(array)[(b)]; (array)[(b)] = aux; }

//--------------------------------------------------------------------------------------------------
//Balance Tree
template<class T>
void KDTree<T>::MedianSplit(std::vector<Node<T>> &p, int start, int end, int median, int axis) {
    int left = start;
    int right = end;

    while (right > left) {
        float v = p[right].GetPoint()[axis];
        int i = left - 1;
        int j = right;
        for (;;) {
            while (v > p[++i].GetPoint()[axis]);
            while (v < p[--j].GetPoint()[axis] && j > left);
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

template<class T>
void KDTree<T>::BalanceSegment(std::vector<Node<T>> &pbal, std::vector<Node<T>> &porg, int index, int start, int end,
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
            newbbmax[axis] = pbal[index].GetPoint()[axis];
            BalanceSegment(pbal, porg, 2 * index, start, median - 1, bbmin, newbbmax);
        } else {
            pbal[2 * index] = porg[start];
        }
    }

    if (median < end) {
        // balancear el segmento derecho
        if (median + 1 < end) {
            Point newbbmin = bbmin;
            newbbmin[axis] = pbal[index].GetPoint()[axis];
            BalanceSegment(pbal, porg, 2 * index + 1, median + 1, end, newbbmin, bbmax);
        } else {
            pbal[2 * index + 1] = porg[end];
        }
    }
}

template<class T>
void KDTree<T>::Balance() {
    std::vector<Node<T>> aux(mNodes.size() + 1);
    mBalanced.resize(mNodes.size() + 1);
    int i;
    Point bbmax = mNodes.front().GetPoint();
    Point bbmin = mNodes.front().GetPoint();
    //mBalanced[0] and aux[0] do not contain any useful information
    for (i = 1; !(mNodes.empty()); i++, mNodes.pop_front()) {
        aux[i] = mNodes.front();
        // X dimension.
        if (aux[i].GetPoint()[X] < bbmin[X]) bbmin[X] = aux[i].GetPoint()[X];
        if (aux[i].GetPoint()[X] > bbmax[X]) bbmax[X] = aux[i].GetPoint()[X];
        // Y dimension.
        if (aux[i].GetPoint()[Y] < bbmin[Y]) bbmin[Y] = aux[i].GetPoint()[Y];
        if (aux[i].GetPoint()[Y] > bbmax[Y]) bbmax[Y] = aux[i].GetPoint()[Y];
        // X dimension.
        if (aux[i].GetPoint()[Z] < bbmin[Z]) bbmin[Z] = aux[i].GetPoint()[Z];
        if (aux[i].GetPoint()[Z] > bbmax[Z]) bbmax[Z] = aux[i].GetPoint()[Z];
    }
    mNodes.clear();

    KDTree<T>::BalanceSegment(mBalanced, aux, 1, 1, mBalanced.size() - 1, bbmin, bbmax);
}