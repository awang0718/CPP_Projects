#include <string>

#include "Image.h"

#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <cmath>
#include <cstdlib>

void Image::lighten (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.l = pixel.l + 0.1;  // Increase luminance
      if (pixel.l > 1)  // Make sure the luminance is within the range [0,1]
        pixel.l = 1;
    }
  }
}

void Image::lighten (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.l = pixel.l + amount;  // Increase luminance
      if (pixel.l > 1)  // Make sure the luminance is within the range [0,1]
        pixel.l = 1;
    }
  }
}

void Image::darken (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.l = pixel.l - 0.1;  // Decrease luminance
      if (pixel.l < 0)  // Make sure the luminance is within the range [0,1]
        pixel.l = 0;
    }
  }
}

void Image::darken (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.l = pixel.l - amount;  // Decrease luminance
      if (pixel.l < 0)  // Make sure the luminance is within the range [0,1]
        pixel.l = 0;
    }
  }
}

void Image::saturate (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.s = pixel.s + 0.1;  // Increase saturation
      if (pixel.s > 1)  // Make sure the saturation is within the range [0,1]
        pixel.s = 1;
    }
  }
}

void Image::saturate (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.s = pixel.s + amount;  // Increase saturation
      if (pixel.s > 1)  // Make sure the saturation is within the range [0,1]
        pixel.s = 1;
    }
  }
}

void Image::desaturate (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.s = pixel.s - 0.1;  // Decrease saturation
      if (pixel.s < 0)  // Make sure the saturation is within the range [0,1]
        pixel.s = 0;
    }
  }
}

void Image::desaturate (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.s = pixel.s - amount;  // Decrease saturation
      if (pixel.s < 0)  // Make sure the saturation is within the range [0,1]
        pixel.s = 0;
    }
  }
}

void Image::grayscale (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.s = 0;  // Set saturation to 0
    }
  }
}

void Image::rotateColor (double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);  // Retrieve pixel from inputImage at location (x, y)
      pixel.h = pixel.h + degrees;  // Increase hue
      // Make sure the saturation is within the range [0,360]
      if (pixel.h > 360)
        pixel.h = pixel.h - 360;
      if (pixel.h < 0)
        pixel.h = pixel.h + 360;
    }
  }
}

void Image::illinify (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.h > 293.5)   // Account for wrap-around
        pixel.h = 11;
      else {
        // Change the hue of each pixel to either 11 (orange) or 216 (blue)
        // based on if the pixel's hue value is closer to orange than blue
        if(std::abs(pixel.h - 11) < std::abs(pixel.h - 216))
          pixel.h = 11;
        else
          pixel.h = 216;
      }
    }
  }
}

void Image::scale (double factor){
  Image copy = *this;
  resize(this->width() * factor, this->height() * factor); // Resize the image

  // Scale the old copy image onto the new image
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel = copy.getPixel((int)(x / factor), (int)(y / factor)); // Scale the image
    }
  }

}

void Image::scale (unsigned w, unsigned h){
  Image copy = *this;
  resize(w, h); // Resize the image

  // Scale the old copy image onto the new image
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel = copy.getPixel((int)(x / (w / this->width())), (int)(y / (h / this->height())));  // Scale the image
    }
  }
}
