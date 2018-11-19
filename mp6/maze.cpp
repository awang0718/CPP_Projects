
/* Your code here! */
#include "maze.h"
#include"dsets.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>      // std::pair, std::make_pair
#include <queue>
#include<algorithm>
#include<iostream>
#include<sys/time.h>
using namespace std;

SquareMaze::SquareMaze()
{
  this->width_ = 0;
  this->height_ = 0;  
}

void SquareMaze::makeMaze(int width,int height)
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
  while(maze.size(idx)!= n )
  {
    int wallRemove = rand() % 2;
    if(canremove(X,Y,wallRemove)){
      setWall(X,Y,wallRemove,0);
      if(wallRemove==0)
        maze.setunion(idx,idx + 1);
      else
        maze.setunion(idx,idx + width_);
    }

    X = rand() % width;
    Y = rand() % height;
    idx = Y*width+X;
  }
}

bool SquareMaze::canremove(int x,int y,int wall)
{
   int   idx = y*width_+x;

  if(x >= width_ || y >= height_) return false;
  if(y == height_-1 && wall==1) return false;
  if(x == width_-1 && wall==0) return false;
  if(wall==0) {
    if(maze.find(idx)==maze.find(idx+1)) return false;
    if(grid[pair<int,int>(x,y)].first==0) return false;
  }
  else {
    if(maze.find(idx)==maze.find(idx+width_)) return false;
    if(grid[pair<int,int>(x,y)].second==0) return false;
  }
  return true;
}

bool SquareMaze::canTravel(int x, int y, int dir)
{
  if(dir==0)
  {
    if(x >= width_) return false;
    if(grid[pair<int,int>(x,y)].first == 1) return false;
  }
  if(dir==1)
  {
    if(y >= height_) return false;
    if(grid[pair<int,int>(x,y)].second == 1) return false;
  }
  if(dir==2)
  {
    if(x-1 < 0 ) return false;
    if(grid[pair<int,int>(x-1,y)].first == 1) return false;
  }
  if(dir==3)
  {
    if (y-1 < 0) return false;
    if(grid[pair<int,int>(x,y-1)].second == 1) return false;
  }
  return true;
}

void SquareMaze::setWall(int x, int	y, int dir, bool exists )
{
  if (dir == 0) {
    if (exists) grid[pair<int,int>(x, y)].first = 1;
  	else grid[pair<int,int>(x, y)].first = 0;
  }
  else {
    if (exists) grid[pair<int,int>(x, y)].second = 1;
  	else grid[pair<int,int>(x, y)].second = 0;
  }

}

vector<int> SquareMaze::solveMaze()
{
  vector<vector<int>> visited;
  vector<pair<int,int>> lastRow;

  map<pair<int,int>,pair<int,int>> map;

  visited.resize(width_);
  for(auto &i:visited)
    i.resize(height_);

  // for(int i = 0; i < width_ * height_; i++)
  //   visited.push_back(0);
  queue<pair<int,int>> q;
  q.push(pair<int,int>(0,0));
  //cout<<"width: "<<width_<<" height_: "<<height_<<endl;
  while(!q.empty()){
    int x=q.front().first;
    int y=q.front().second;
    q.pop();
    //cout<<"x: "<<x<<" y: "<<y<<endl;
    visited[x][y]=1;

    if (y == height_-1)
      lastRow.push_back(pair<int,int>(x,y));

    if(canTravel(x,y,0) && !visited[x+1][y])
    {
    	q.push(pair<int,int>(x+1,y));
      map[pair<int,int>(x+1,y)]=pair<int,int>(x,y);
    }
    if(canTravel(x,y,1) && !visited[x][y+1])
    {
    	q.push(pair<int,int>(x,y+1));
       map[pair<int,int>(x,y+1)]=pair<int,int>(x,y);

    }
    if(canTravel(x,y,2) && !visited[x-1][ y])
    {
    	q.push(pair<int,int>(x-1,y));
      map[pair<int,int>(x-1,y)]=pair<int,int>(x,y);

    }
    if(canTravel(x,y,3) && !visited[x][ y-1])
    {
    	q.push(pair<int,int>(x,y-1));
      map[pair<int,int>(x,y-1)]=pair<int,int>(x,y);
    }
  }

  vector<int> mazePath;
  pair<int,int> end = lastRow[lastRow.size()-1];
  //cout<<"last: " <<end.first<<" "<<end.second<<endl;
  while(map.find(end)!= map.end()){
    pair<int,int> previous = map[end];
    if (previous.first==end.first-1){
      mazePath.push_back(0);
    }
    else if (previous.second==end.second-1){
      mazePath.push_back(1);
    }
    else if (previous.first==end.first+1){
      mazePath.push_back(2);
    }
    else if (previous.second==end.second+1){
      mazePath.push_back(3);
    }
    end = previous;
  }
  reverse(mazePath.begin(),mazePath.end());
  //cout<<"path: ";
  //for(auto i:mazePath)
  //cout<<" "<<i;
  //cout<<endl;
  return mazePath;
}

PNG* SquareMaze::drawMaze() const
{
  PNG* image= new PNG(width_*10+1,height_*10+1);
  for(int i=0;i<width_*10+1;i++){
    HSLAPixel &p=image->getPixel(i,0);
    HSLAPixel &p2=image->getPixel(i,height_*10);
    if(i>9 || i < 1)
    p=HSLAPixel(0,0,0);
    p2=HSLAPixel(0,0,0);
  }
  for(int i=0;i<height_*10+1;i++){
    HSLAPixel &p=image->getPixel(0,i);
    HSLAPixel &p2=image->getPixel(width_*10,i);
    p=HSLAPixel(0,0,0);
    p2=HSLAPixel(0,0,0);
  }
  for(auto &i:grid){
    int x=i.first.first;
    int y=i.first.second;
    if(i.second.first==1){
      for(int j=0;j<11;j++){
        HSLAPixel &p=image->getPixel((x+1)*10,y*10+j);
        p=HSLAPixel(0,0,0);
      }
    }
    if(i.second.second==1){
      for(int j=0;j<11;j++){
        HSLAPixel &p=image->getPixel(x*10+j,(y+1)*10);
        p=HSLAPixel(0,0,0);
      }
    }
  }

  return image;
}
PNG* SquareMaze::drawMazeWithSolution()
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

  return image;
}
SquareMaze::~SquareMaze(){
  // delete ima;
}
