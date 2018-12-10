#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
 #include <queue>
 #include <algorithm>
 #include <string>
 #include <list>
 // #include <bits/stdc++.h>
 /**
  * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
  *
  * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
  * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
  * be traveled along the shortest path.
  *
  * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
  *
  * @param start The key for the starting vertex.
  * @param end   The key for the ending vertex.
  */
 using namespace std;
 template <class V = Vertex, class E = Edge>
 class compare
 {
 public:
   bool operator()(V v1,V v2)
   {
     if(v1["weight"]=="inf"||stod(v1["weight"])>stod(v2["weight"]))
     return true;
     return false;

   }
 };
 template <class V, class E>
 std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
   std::list<std::string> path;
 	for(auto &i:vertexMap)
   {
     i.second["weight"] = "inf";
     i.second["pred"] = "";
     i.second["visited"] = "0";
   }
   vertexMap.at(start)["weight"]="0";
 	// string::size_type sz;
   priority_queue<V, vector<V>, compare<V>> pq;
   for(auto i:adjList.at(vertexMap.at(start).key()))
   {
     V& t=vertexMap.at(i->get().dest().key());
     t["weight"] = to_string(i->get().weight());
     t["pred"] = start;
     t["visited"] = "1";
     pq.push(t);
   }
   while (!pq.empty()) {
     /* code */
     // cout<<"some"<<endl;
     V&t =vertexMap.at(pq.top().key());
     pq.pop();
     t["visited"] = "1";
     for(auto i:adjList.find(t.key())->second)
     {
       string key;
       if(t.key()==i->get().dest().key())
        key=i->get().source().key();
       else
        key=i->get().dest().key();
       V& t2=vertexMap.at(key);
       if(t2["visited"]=="1")
       continue;
       if(t2["weight"]=="inf"||stod(t2["weight"])>i->get().weight()+stod(t["weight"]))
       {
       t2["weight"] = to_string(i->get().weight()+stod(t["weight"]));
       t2["pred"] = t.key();
       // t["visited"] = "1";
       pq.push(t2);
       }
     }
   }
   string ts=end;
   while(ts!=start)
   {
     // cout<<"other"<<endl;
     path.push_back(ts);
     ts=vertexMap.at(ts)["pred"];
   }
   path.push_back(ts);
   reverse(path.begin(),path.end());
   return path;
 }
