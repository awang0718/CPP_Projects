#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace std;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traverse = NULL;
  endOfTrav = true;
}

ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal* Traverse) {
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  traverse = Traverse;

  initial = start;
  points.push_back(start_);
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (start_.x < png_.width() - 1)
    if (visitable(Point(start_.x + 1, start_.y))) // Add right pixel to traveral, if possible
      traverse->add(Point(start_.x + 1, start_.y));
  if (start_.y < png_.height() - 1)
    if (visitable(Point(start_.x, start_.y + 1)))  // Add bottom pixel to traveral, if possible
      traverse->add(Point(start_.x, start_.y + 1));
  if (start_.x > 0)
    if (visitable(Point(start_.x - 1, start_.y))) // Add left pixel to traveral, if possible
      traverse->add(Point(start_.x - 1, start_.y));
  if (start_.y > 0)
    if (visitable(Point(start_.x, start_.y - 1)))  // Add upper pixel to traveral, if possible
      traverse->add(Point(start_.x, start_.y - 1));

  //Locate next available traversal iterator
  Point nextPoint = traverse->pop();
  while (checkVisited(nextPoint)) { // Make sure pixel has not already been visited   //while (visited[nextPoint.x + png_.width() * nextPoint.y])
    if (traverse->empty() == true) {  // If traversal is empty, return current iterator
      endOfTrav = true;
      traverse = NULL;
      return *this;
    }
    nextPoint = traverse->pop();
  }

  traverse->add(nextPoint);
  start_ = nextPoint; // Set the new starting point
  points.push_back(start_); // Push new starting point to list of visited points

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //return Point(0, 0);
  return start_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return endOfTrav != other.endOfTrav;

  // bool thisEmpty = false;
  // bool otherEmpty = false;
  //
  // if (traverse == NULL) { thisEmpty = true; }
  // if (other.traverse == NULL) { otherEmpty = true; }
  //
  // if (!thisEmpty)  { thisEmpty = traverse->empty(); }
  // if (!otherEmpty) { otherEmpty = other.traverse->empty(); }
  //
  // if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  // else if ((!thisEmpty)&&(!otherEmpty)) return (traverse != other.traverse); //both not empty then compare the traversals
  // else return true; // one is empty while the other is not, return true
}


bool ImageTraversal::Iterator::visitable(Point pixel) {
  if (calculateDelta(png_.getPixel(initial.x, initial.y), png_.getPixel(pixel.x, pixel.y)) < tolerance_ && // Pixel is within tolerance
      pixel.x < png_.width() && pixel.y < png_.height()) return true;  // Pixel is not out-of-bounds
  return false;
}

bool ImageTraversal::Iterator::checkVisited(Point pixel) {
  if (points.empty())
    return false;
  for (unsigned i = 0; i < points.size(); i++)
    if(pixel == points[i])
      return true;
  return false;
}
