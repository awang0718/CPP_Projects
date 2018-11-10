/* Your code here! */
#include"dsets.h"

void DisjointSets::addelements(int num) {
  for(int i = 0;i < num; i++)
    data.push_back(-1);
}

int DisjointSets::find(int elem) {
  if(data[elem] < 0)
    return elem;
  else{
    int root = find(data[elem]);
    data[elem] = root;
    return root;
  }
}

void DisjointSets::setunion(int a, int b) {
  int idxa = find(a), idxb = find(b);
  if(idxa == idxb) return;
  if(data[idxa] <= data[idxb]){
    data[idxa] += data[idxb];
    data[idxb] = idxa;
  }
  else {
    data[idxb] += data[idxa];
    data[idxa] = idxb;
  }
}

int DisjointSets::size(int elem) {
  return -data[find(elem)];
}
