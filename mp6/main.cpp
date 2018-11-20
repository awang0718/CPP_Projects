#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>      // std::pair, std::make_pair
#include <queue>
#include <algorithm>
#include <sys/time.h>
#include<math.h>

using namespace std;

void SquareMaze::makeCreativeMaze(int width,int height, int radius)
{
  this->width_ = width;
  this->height_ = height;
  int n = height_*width_;
  grid.clear();
  maze.data.clear();

  for(int j = 0; j < height; j++){
    for(int i = 0; i < width; i++){
    	grid[make_pair(i,j)] = make_pair(1,1);
    }
  }
  maze.addelements(n);

  // srand((unsigned)time(NULL));
  static struct timeval tv;
  gettimeofday(&tv, NULL);

  int X = rand() % width;
  int Y = rand() % height;
  int idx = Y*width+X;
  // while(maze.size(idx)!= n - (radius*(radius-1) / 2))
  while(maze.size(idx)!= n - 24*25)
  {
    int wallRemove = rand() % 2;
    if(canremove(X,Y,wallRemove)) {
      setCreativeWall(X,Y,wallRemove,0);
      if (wallRemove==0 && !(X >= 25 && Y < 25))
        maze.setunion(idx,idx + 1);
      else if (wallRemove==1 && !(X >= 25 && Y < 25))
        maze.setunion(idx,idx + width_);
    }

    X = rand() % width;
    Y = rand() % height;
    idx = Y*width+X;
  }
  cout << "n: " << n << endl;
}

void SquareMaze::setCreativeWall(int x, int y, int dir, bool exists)
{
  /*if (x - y <= 0) {
    if (dir == 0 && x+1 - y <= 0) {
      if (exists) grid[pair<int,int>(x, y)].first = 1;
      else grid[pair<int,int>(x, y)].first = 0;
    }
    else if (x - (y+1) <= 0){
      if (exists) grid[pair<int,int>(x, y)].second = 1;
      else grid[pair<int,int>(x, y)].second = 0;
    }
  }*/
  if (!(x >= 25 && y < 25)) {
    if (dir == 0 /*&& !(x + 1 > 24 && y < 25)*/) {
      if (exists) grid[pair<int,int>(x, y)].first = 1;
      else grid[pair<int,int>(x, y)].first = 0;
    }
    else /*if (!(x >= 25 && y + 1 < 25))*/{
      if (exists) grid[pair<int,int>(x, y)].second = 1;
      else grid[pair<int,int>(x, y)].second = 0;
    }
  }	
  // cout << "setCreativeWall > x: " << x  << "\ty: " << y << endl;
}

PNG* SquareMaze::drawCreativeMazeWithSolution()
{
  PNG* image=drawMaze();
  // ima=image;
  vector<int> solution=solveMaze();
  // pair<int,int> cur=pair<int,int>(5,5);
  int x=5,y=5;
  for(auto i:solution){
    int k;
    if(i==0){
      k=x+10;
      for(;x<k;x++){
        HSLAPixel &p=image->getPixel(x,y);
        p=HSLAPixel(0,1,0.5,1);
      }
    }
    if(i==1){
      k=y+10;
      for(;y<k;y++){
        HSLAPixel &p=image->getPixel(x,y);
        p=HSLAPixel(0,1,0.5,1);
      }
    }
    if(i==2){
      k=x-10;
      for(;x>k;x--){
        HSLAPixel &p=image->getPixel(x,y);
        p=HSLAPixel(0,1,0.5,1);
      }
    }
    if(i==3){
      k=y-10;
      for(;y>k;y--){
        HSLAPixel &p=image->getPixel(x,y);
        p=HSLAPixel(0,1,0.5,1);
      }
    }
  }
  if(1){
    HSLAPixel &p=image->getPixel(x,y);
    p=HSLAPixel(0,1,0.5,1);

  }
  x=x-5;
  for(int k=1;k<10;k++){
    HSLAPixel &p2=image->getPixel(x+k,height_*10);
    p2=HSLAPixel(1,1,1);

  }
  cout << "x: " << y << "\tx: " << y << endl;  
  for(int i = height_*10 - 1; i > (height_ - 25) *10 - 1; i--){
    for(int j = 1; j < (height_ - 25) * 10 + 1; j++){
      // cout << "i: " << i << "\tj: " << j << endl;
      HSLAPixel &p=image->getPixel(i,j);
      p=HSLAPixel(0,1,0.5 - i*.0005,1);
    }
  }  

  return image;
}

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze maze1;
    maze1.makeCreativeMaze(50, 50, 50);
    // cout << "makeCreativeMaze" << endl;
    maze1.solveMaze();
    // cout << "solveMaze" << endl;
    PNG *p = maze1.drawCreativeMazeWithSolution();
    // cout << "drawCreativeMaze" << endl;
    p->writeToFile("creative" + string(".png"));

    /*
    SquareMaze maze2;
    maze2.makeCreativeMaze(50, 50, 50);
    // cout << "makeCreativeMaze" << endl;
    maze2.solveMaze();
    // cout << "solveMaze" << endl;
    PNG *p2 = maze2.drawCreativeMazeWithSolution();
    // cout << "drawCreativeMaze" << endl;
    // p2->writeToFile("creative" + string(".png"));
    */
    
    return 0;
}
