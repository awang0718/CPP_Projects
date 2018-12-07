#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return adjList[v.key()].size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert(std::pair<std::string,V &>(key,v));
  adjList[key] = std::list<edgeListIter>();
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  V &curv=vertexMap[key];
  for(auto &i:	adjList[key])
  {
    string tkey;
    if(curv==i->source)
   		tkey=i->get().dest().key();
    else
      tkey=i->get().source().key();

    for(auto j=adjList[tkey].begin();j<adjList[tkey].end();j++)
    {
     	   if((*j)->get()==i->get())
         {
           adjList[tkey].erase(j);
           break;
         }
    }
    edgeList.erase(i);
  }
  vertexMap.erase(key);
  adjList.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
	edgeList.push_back(e);
  auto it=edgeList.end();
  it--;
  adjList[v1.key()].push_back(it);
  adjList[v2.key()].push_back(it);

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  // V &curv=vertexMap[key1];
  for(auto &i:	adjList[key1])
  {
    if(i->get().dest().key()==key2||i->get().source().key()==key2)
    {
      removeEdge(i);
    }
  }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  std::string key1=it->get().dest().key(),key2=it->get().source().key();
  for(auto i=adjList[key1].begin();i<adjList[key1].end();i++)
  {
  	if((*i)->get().dest().key()==key2||(*i)->get().source().key()==key2)
  	{
   		adjList[key1].erase[i];
  	}
  }
  for(auto i=adjList[key2].begin();i<adjList[key2].end();i++)
  {
  	if((*i)->get().dest().key()==key1||(*i)->get().source().key()==key1)
  	{
   		adjList[key2].erase[i];
  	}
  }
  edgeList.erase(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  auto &j=adjList.find(key)->second;
   for(auto i:j)
  {
   	edges.push_back(*i);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  // auto i=begin();i<adjList.find(key2)->second.end();i++
  // unsigned size=adjList.find(key2)->second.size();
  // for(unsigned z=0;z<size;z++)
  // {
  //    const auto i=(adjList.find(key2)->second).begin()+z;
  // 	if((*i)->get().dest().key()==key1||(*i)->get().source().key()==key1)
  // 	{
  //  		return true;
  // 	}
  // }
  for(auto i:adjList.find(key1)->second)
  {
    if(i->get().dest().key()==key2)
    {
      return true;
    }
  }
  return false;
}

