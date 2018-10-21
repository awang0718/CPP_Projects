
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG png;       png.readFromFile("triforce.png");
  FloodFilledImage image(png);

  BFS bfs(png, Point(90, 297), 0.05);
  MyColorPicker green(png, 95);
  image.addFloodFill( bfs, green );

  BFS bfs2(png, Point(90, 140), 0.05);
  MyColorPicker green2(png, 95);
  image.addFloodFill( bfs2, green2 );

  // BFS bfs3(png, Point(90, 80), 0.05);
  // HSLAPixel color(43, 1.0, 0.85);
  // SolidColorPicker yellow(color); //  RainbowColorPicker rainbow2(0.05);
  // image.addFloodFill( bfs3, yellow );

  BFS bfs4(png, Point(90, 297), 0.2);
  MyColorPicker blue(png, 180);
  image.addFloodFill( bfs4, blue );

  BFS bfs5(png, Point(90, 140), 0.05);
  MyColorPicker blue2(png, 95);
  image.addFloodFill( bfs5, blue2 );

  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
