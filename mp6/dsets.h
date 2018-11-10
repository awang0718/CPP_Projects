/* Your code here! */
#ifndef DESTS_H
#define DESTS_H

#include<vector>
#include<iostream>

using namespace std;

class DisjointSets{
  public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
  // private:
    vector<int> data;
};

#endif
