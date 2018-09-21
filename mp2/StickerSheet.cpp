#include <string>
#include <cmath>
#include <cstdlib>

#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
using cs225::PNG;
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

StickerSheet::StickerSheet (const Image &picture, unsigned max){
  // Create a sheet, array of sticker pictures, and array of coordinates for each picture
  sheet_ = new Image(picture);
  picture_ = new Image*[max];
  x_ = new unsigned[max];
  y_ = new unsigned[max];
  // Set all pictures to NULL
  for (unsigned i = 0; i < max; i++) {
    picture_[i] = NULL;
    x_[i] = 0;
    y_[i] = 0;
  }
  // Set max number of pictures
  max_ = max;
};

StickerSheet::~StickerSheet (){
  // Delete all pictures in array
  for (unsigned i = 0; i < max_; i++) {
    if (picture_[i] != NULL) {
      delete picture_[i];
      picture_[i] = NULL;
    }
  }
  // Delete everything and set all pointers to NULL
  delete sheet_;
  delete[] picture_;
  delete[] x_;
  delete[] y_;
  picture_ = NULL;
  x_ = NULL;
  y_ = NULL;

};

StickerSheet::StickerSheet (const StickerSheet &other){
  // Copy a sheet, array of sticker pictures, and array of coordinates for each picture from other
  sheet_ = new Image(*other.sheet_);
  picture_ = new Image*[other.max_];
  x_ = new unsigned[other.max_];
  y_ = new unsigned[other.max_];
  // Copy all pictures and coordinates from other
  for (unsigned i = 0; i < other.max_; i++) {
    // Copy data from array of pictures and array of coordinates if that picture exists
    if (other.picture_[i] != NULL){
      picture_[i] = new Image(*other.picture_[i]);
      x_[i] = other.x_[i];
      y_[i] = other.y_[i];
    }
    else {
      picture_[i] = NULL;
      x_[i] = 0;
      y_[i] = 0;
    }
  }
  // Set new max number of pictures
  max_ = other.max_;
};

StickerSheet const & StickerSheet::operator= (const StickerSheet &other){
  // Make sure other is not the sheet itself
  if (this != &other) {
    // Destroy the old sheet
    for (unsigned i = 0; i < max_; i++) {
      if (picture_[i] != NULL) {
        delete picture_[i];
        picture_[i] = NULL;
      }
    }
    delete sheet_;
    delete[] picture_;
    delete[] x_;
    delete[] y_;
    picture_ = NULL;
    x_ = NULL;
    y_ = NULL;

    // Set the new sheet equal to other
    sheet_ = new Image(*other.sheet_);
    picture_ = new Image*[other.max_];
    x_ = new unsigned[other.max_];
    y_ = new unsigned[other.max_];

    for (unsigned i = 0; i < other.max_; i++) {
      if (other.picture_[i] != NULL){
        picture_[i] = new Image(*other.picture_[i]);
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
      }
      else {
        picture_[i] = NULL;
        x_[i] = 0;
        y_[i] = 0;
      }
    }
    max_ = other.max_;
  }

  return *this;
};

void StickerSheet::changeMaxStickers (unsigned max){
  // If new max equals old max, do nothing
  if (max == max_)
    return;

  // Create new sheet of stickers
  Image *newSheet = new Image(*sheet_);
  Image **newPicture = new Image*[max];
  unsigned *newX = new unsigned[max];
  unsigned *newY = new unsigned[max];
  for (unsigned i = 0; i < max; i++)
    newPicture[i] = NULL;

  // If new max is less than old max, delete stickers from old sheet that exceed index max
  if (max < max_) {
    for (unsigned i = max; i < max_; i++) {
      if (picture_[i] != NULL) {
        delete picture_[i];
        picture_[i] = NULL;
      }
    }
    max_ = max;
  }

  // Copy data from old sheet to new sheet
  for (unsigned i = 0; i < max_ ; i++) {
    if (picture_[i] != NULL) {
      newPicture[i] = new Image(*picture_[i]);
      newX[i] = x_[i];
      newY[i] = y_[i];
    }
  }

  // Destroy the old sheet
  for (unsigned i = 0; i < max_; i++) {
    if (picture_[i] != NULL) {
      delete picture_[i];
      picture_[i] = NULL;
    }
  }
  delete sheet_;
  delete[] picture_;
  delete[] x_;
  delete[] y_;

  // Set old sheet equal to new sheet
  sheet_ = newSheet;
  max_ = max;
  picture_ = newPicture;
  x_ = newX;
  y_ = newY;
};

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  for (unsigned i = 0; i < max_; i++) {
    // Add new sticker to lowest possible index
    if (picture_[i] == NULL) {
      picture_[i] = new Image(sticker);
      x_[i] = x;
      y_[i] = y;
      return i;
    }
  }
  return -1;
};

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  // Do nothing if index is invalid
  if (index >= max_)
    return false;
  // If index contains no existing sticker, translate it
  if (picture_[index] != NULL) {
    x_[index] = x;
    y_[index] = y;
    return true;
  }
  return false;
};

void StickerSheet::removeSticker (unsigned index){
  // Remove sticker if the sticker's index is within range and if the sticker exists
  if (index < max_ && picture_[index] != NULL) {
    delete picture_[index];
    picture_[index] = NULL;
    x_[index] = 0;
    y_[index] = 0;
  }
};

Image * StickerSheet::getSticker (unsigned index) const {
  if (index >= max_ && picture_[index] == NULL)
    return NULL;

  // Get sticker if the sticker's index is within range and if the sticker exists
  return picture_[index];
};

Image StickerSheet::render () const {
  // Retrieve dimensions of the sheet
  unsigned width = sheet_->width();
  unsigned height = sheet_->height();

  // Calculate width & height of the render needed to fit all stickers
  for (unsigned i = 0; i < max_; i++){
    if (picture_[i] != NULL) {
      unsigned w = x_[i] + picture_[i]->width();
      unsigned h = y_[i] + picture_[i]->height();
      // Set new render height and width if stickers overflow out of sheet
      if (width < w)
        width = w;
      if (height < h)
        height = h;
    }
  }

  // Create render with proper dimensions
  Image *render = new Image(*sheet_);
  render->resize(width,height);

  //Loop through all valid stickers in the sheet
  for (unsigned j = 0; j < max_; j++) {
    if (picture_[j] != NULL) {
      Image sticker = *picture_[j];   // Get a sticker from the array of pictures
      for (unsigned x = x_[j]; x < x_[j] + sticker.width(); x++) {
        for (unsigned y = y_[j]; y < y_[j] + sticker.height(); y++) {
          // Retrieve the proper pixel from sticker and sheet
          HSLAPixel *pixel = &sticker.getPixel(x - x_[j], y - y_[j]);
          HSLAPixel *renderPix = &render->getPixel(x, y);
          // If pixel from sticker is valid, copy it into the render
          if (pixel->a != 0) {
    	      renderPix->h = pixel->h;
    	      renderPix->s = pixel->s;
    	      renderPix->l = pixel->l;
            renderPix->a = pixel->a;
  	      }
        }
      }

    }
  }
  return *render;
};
