/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     int rows = theSource.getRows();
     int cols = theSource.getColumns();
     if((rows == 0 && cols == 0) || theTiles.empty()) return NULL;

     MosaicCanvas *canvas = new MosaicCanvas(rows, cols);
     map<Point<3>,TileImage*> map;	// Create map of <points: Tile Images>
     vector<Point<3>> points;		// Create a vector of points
     points.resize(theTiles.size());

     for(unsigned int i = 0; i < theTiles.size(); i++) {
       Point<3> p=convertToXYZ(theTiles[i].getAverageColor());	// Retrieve point from average color
       points[i] = p;			// Set point in vector
       //points.push_back(p);
       map[p] = &theTiles[i];		// Add point and its corresponding tile image to map
     }

     KDTree<3> tree(points);		// Build KDTree from the vector of points

     for(int i =0; i<rows;i++){
        for(int j=0;j<cols;j++){
          Point<3> p=convertToXYZ(theSource.getRegionColor(i,j));// Retrieve point from source image's region color
          Point<3> nearest = tree.findNearestNeighbor(p);	// REtrieve point from the source image's point's nearest neighbor
          //cout << nearest << endl;
          TileImage* image =  map[nearest];	// Retrieve proper tile map from map
          canvas->setTile(i, j, image);		// Set proper canvas tile
        }
      }

    return canvas;

}
