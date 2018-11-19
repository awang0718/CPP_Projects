
/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include<iostream>
#include "dsets.h"
#include<vector>
#include "cs225/PNG.h"
#include <utility>      // std::pair, std::make_pair

#include<map>

using namespace std;
using namespace cs225;

class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int,int);
  bool canTravel(int x, int y, int dir);
  void setWall(int x, int y, int dir, bool exists );
  vector<int> solveMaze();
  PNG* drawMaze() const;
  PNG* drawMazeWithSolution();
  PNG* drawCreativeMaze() const;
  ~SquareMaze();
private:
  bool canremove(int x,int y,int wall);
  DisjointSets maze;
 // vector<pair<int,int>> walls;
  map<pair<int,int>,pair<int,int>> grid; // (x, y): (right wall, bottom wall)
  int width_;
  int height_;
  // PNG* image;
};


#endif
