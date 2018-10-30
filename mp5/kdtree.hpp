/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

/**
* This function returns true if the value of the first point at the dimension curDim
* is less than the value of second point at the dimension curDim. If the first point
* at the dimension curDim is equal to the value of second point at the dimension curDim,
* then refer to the < operator.
**/
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim]) return first < second; // If values at curDim are equal, refer to < operator
    else if (first[curDim] < second[curDim]) return true;
    else if (first[curDim] > second[curDim]) return false;
    return false;
}

/**
*  This function returns true if the distance between potential and target is smaller
*  that the distance between target and currentBest. If the distances are equal,
*  then refer to the < operator.
**/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    // Distance between target and potential
    double targetDist = 0;
    for (int i = 0; i < Dim; i++)
      targetDist += pow((target[i] - potential[i]), 2);

    // Distance between target and currentBest
    double currentDist = 0;
    for (int j = 0; j < Dim; j++)
      currentDist += pow((target[j] - currentBest[j]), 2);

    if (targetDist == currentDist) return potential < currentBest; // If distances are equal, refer to < operator
    else if (targetDist < currentDist) return true;
    else if (targetDist > currentDist) return false;
    return false;
}

/*
*   KDTree constructor
*/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.empty()){
      root = NULL;
      size = 0;
      return;
    }

    vector<Point<Dim>> points;
    for (size_t i = 0; i < newPoints.size(); i++)
      points.push_back(newPoints[i]);

    size = points.size();
    buildTree(0, 0, newPoints.size() - 1, points, root);
}

/*
*   KDTree copy constructor
*/
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = copy(other.root);
  size = other.size;

}

/*
*   KDTree = operator
*/
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
     clear(root);
     root = copy(rhs.root);
     size = rhs.size;
  }
  return *this;
}

/*
*   KDTree destructor
*/
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
  root = NULL;
}

/*
*   KDTree copy function
*/
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode*& KDNode)
{
    if (KDNode == NULL) return NULL;
    // Copy this KDNode and it's children
    KDTreeNode* newNode = new KDTreeNode(KDNode->point);
    newNode->left = copy(KDNode->left);
    newNode->right = copy(KDNode->right);
    return newNode;
}

/*
*   KDTree clear function
*/
template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* KDNode)
{
    if (KDNode == NULL) return;

    clear(KDNode->left);
    clear(KDNode->right);
    delete KDNode;
}

/*
*   This function will sort the vector that will represent the KDTree using "Binary Sort."
*   During the sorting process, it will recursively build the K-d Tree.
*/
template <int Dim>
// typename KDTree<Dim>::KDTreeNode*
void KDTree<Dim>::buildTree(int dim, int begin, int end, vector<Point<Dim>>& points, KDTreeNode*& KDNode)
{
    if (begin > end) return; // If vector to build is null, return.
    int median = (begin + end) / 2;
    Point<Dim> KDPoint = quickSelect(dim, begin, end, median, points); //Ensure the median point is at the median index
    KDNode = new KDTreeNode(KDPoint);
    // Recursively contruct the left and right halves of the KDTree
    buildTree((dim + 1) % Dim, begin, median - 1, points, KDNode->left);
    buildTree((dim + 1) % Dim, median + 1, end, points, KDNode->right);
    //return KDNode;
}

/*
*   This function will return the kth smallest element in the [begin, end] list, via Wikipedia.
*/
template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(int dim, int begin, int end, int k, vector<Point<Dim>>& points)
{
    if (begin == end) return points[begin]; // If vector to only containts 1 element, return that element
    int pivotIndex = (begin + end) / 2; // Select some pivot index. In this case, the middle of the list is chosen.
    int part = partition(dim, begin, end, pivotIndex, points);
    if (k == part) return points[k];
    // Recursively search through either the 1st or second half of the list
    if (k < part) return quickSelect(dim, begin, part - 1, k, points);
    else return quickSelect(dim, part + 1, end, k, points);
}

/*
*   This function will partition all elements of the vector and return the pivotindex, via Wikipedia.
*   All elements with a smaller dimensional value than the pivot element is positioned at the left of the pivot element.
*   All elements with a larger dimensional value than the pivot element is positioned at the right of the pivot element.
*/
template <int Dim>
int KDTree<Dim>::partition(int dim, int begin, int end, int pivotIndex, vector<Point<Dim>>& points)
{
    Point<Dim> pivot = points[pivotIndex];
    swap(points[pivotIndex], points[end]);  // Move pivot element to end of vector
    int storeIndex = begin;

    for (int i = begin; i < end; i++) { // Move all elements with a smaller dimensional value than the pivot element to the left of the pivot
      if (smallerDimVal(points[i], pivot, dim)) {
        swap(points[storeIndex], points[i]);
        storeIndex++;
      }
    }
    swap(points[storeIndex], points[end]);  // Move pivot element to final position
    return storeIndex;
}


// template <int Dim>
// Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
// {
//     /**
//      * @todo Implement this function!
//      */
//
//     return findNearNeighbor(Dim, root->point, query, root);
//
//     // return Point<Dim>();
// }
//
//
// template <int Dim>
// Point<Dim> KDTree<Dim>::findNearNeighbor(int dim, const Point<Dim>& currentBest, const Point<Dim>& target, KDTreeNode* KDNode) const
// {
//     if (smallerDimVal(target, currentBest, dim)) {
//       if (KDNode->left != NULL)
//         return findNearNeighbor((dim + 1) % Dim, KDNode->left->point, target, KDNode->left);
//       else
//         return KDNode->point;
//     }
//     else {
//       if (KDNode->right != NULL)
//         return findNearNeighbor((dim + 1) % Dim, KDNode->right->point, target, KDNode->right);
//       else
//         return KDNode->point;
//     }
//
//
// }


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     //cout<<"query "<<query<<endl;
    if(root==NULL)
    return Point<Dim>();
    Point<Dim> p=findnhelper(root,0,Point<Dim>(),query);
    //cout<<"final result "<<p<<endl;
    return p;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findnhelper(KDTreeNode * subroot,int d,Point<Dim> currentBest,Point<Dim>query) const{
  int flag=0;
  // cout<<"current point :"<<subroot->point<<" radius"<<getradius(subroot->point,query)<<endl;
  if(subroot->point==query)
    return query;
  if(smallerDimVal(query,subroot->point,d)){
    if(subroot->left==NULL){
      currentBest=subroot->point;
      int r=getradius(currentBest,query);
      if(subroot->right!=NULL&&biggerraduis(query,subroot->point,d%Dim,r)){
      Point<Dim> potential=findnhelper(subroot->right,(d+1)%Dim,currentBest,query);
      if(shouldReplace(query,currentBest,potential))
        return potential;
      return currentBest;
      }
      else{
        return currentBest;
      }
    }
    Point<Dim> potential=findnhelper(subroot->left,(d+1)%Dim,currentBest,query);
    if(shouldReplace(query,subroot->point,potential)) currentBest=potential;
    else
    currentBest=subroot->point;
    flag=1;
  }
  else{
    if(subroot->right==NULL){
      currentBest=subroot->point;
      int r=getradius(currentBest,query);
      if(subroot->left!=NULL&&biggerraduis(query,subroot->point,d%Dim,r)){
      Point<Dim> potential= findnhelper(subroot->left,(d+1)%Dim,currentBest,query);
      if(shouldReplace(query,currentBest,potential))
          return potential;
      return currentBest;
      }
      else{
        return currentBest;
      }
    }
    Point<Dim> potential=findnhelper(subroot->right,(d+1)%Dim,currentBest,query);
    if(shouldReplace(query,subroot->point,potential)) currentBest=potential;
    else currentBest=subroot->point;
  }
  if(flag){
    int r=getradius(currentBest,query);
    if(subroot->right!=NULL&&biggerraduis(query,subroot->point,d%Dim,r)){
      Point<Dim> potential=findnhelper(subroot->right,(d+1)%Dim,currentBest,query);
      if(shouldReplace(query,currentBest,potential))
        return potential;
      return currentBest;
    }
    else{
      return currentBest;
    }
  }
  else{
    int r=getradius(currentBest,query);
    if(subroot->left!=NULL&&biggerraduis(query,subroot->point,d%Dim,r)){
      Point<Dim> potential= findnhelper(subroot->left,(d+1)%Dim,currentBest,query);
      if(shouldReplace(query,currentBest,potential))
        return potential;
      return currentBest;
    }
    else{
      return currentBest;
    }
  }

}

template <int Dim>
bool KDTree<Dim>::biggerraduis(Point<Dim> target,Point<Dim> subroot,int d,int radius) const{
  int distances=abs(subroot[d]-target[d]);
  if(distances * distances<=radius) return true;
  return false;
}
template <int Dim>
int KDTree<Dim>::getradius(Point<Dim> first,Point<Dim>second) const{
    int sum=0;
    for(long i=0;i<Dim;i++){
      sum+=pow((first[i]-second[i]),2);
    }
    return sum;
  }
