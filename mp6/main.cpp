#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

PNG* SquareMaze::drawCreativeMaze() const 
{
    PNG* image= new PNG(width_*10+1,height_*10+1);
    for(int i=0;i<width_*10+1;i++){
	HSLAPixel &p=image->getPixel(i,0);
	HSLAPixel &p2=image->getPixel(i,height_*10);
	if(i > 9 || i < 1)
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

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze maze1;
    maze1.makeMaze(50, 50);
    PNG *p = maze1.drawCreativeMaze();

    
    return 0;
}
