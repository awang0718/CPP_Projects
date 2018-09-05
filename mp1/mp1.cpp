#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  PNG inputImage = PNG();  // Create input image
  inputImage.readFromFile(inputFile);  // Read in PNG image from inputFile

  PNG outputImage = PNG(inputImage.width(), inputImage.height());  // Create output image with same dimensions as input image

  for (unsigned x = 0; x < inputImage.width(); x++) {
    for (unsigned y = 0; y < inputImage.height(); y++) {
      HSLAPixel & inputPixel = inputImage.getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      HSLAPixel & outputPixel = outputImage.getPixel(outputImage.width()-1-x, outputImage.height()-1-y);  // Retrieve pixel from inputImage at location (outputImage.width()-1-x, outputImage.height()-1-y)
      
      // Set the outputPixel equal to the inputPixel by setting the outputPixel's HSLA values equal to inputPixel's HSLA values
      outputPixel.h = inputPixel.h;
      outputPixel.s = inputPixel.s;
      outputPixel.l = inputPixel.l;
      outputPixel.a = inputPixel.a;
    }
  }

  outputImage.writeToFile(outputFile); // Write output Image to outputFule
}


PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  
  
  return png;
}
