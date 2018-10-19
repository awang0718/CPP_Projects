#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(PNG png) : png_(png) { }
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel = HSLAPixel();
  int width  = png_.width();
  int height = png_.height();
  int centerX = png_.width() / 2;
  int centerY = png_.height() / 2;

  //pixel.h = (abs((int)x - centerX) + abs((int)y - centerY)) * 360 / (width / 2 + height / 2);
  pixel.l = 0.7 - (abs((int)x - centerX) + abs((int)y - centerY)) * 0.4 / (width + height);
  pixel.s = 0.7 - (abs((int)x - centerX) + abs((int)y - centerY)) * 0.4 / (width + height);
  pixel.a = 1.0;

  return pixel;
//  return HSLAPixel();
}
