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
  // picture_ = new Image[max];
  // picture_[0] = picture;
  //
  // max_ = max;
  // x_ = 0;
  // y_ = 0;

  picture_ = new Image*[max];
  x_ = new unsigned[max];
  y_ = new unsigned[max];

  picture_[0] = new Image(picture);
  x_[0] = 0;
  y_[0] = 0;

  max_ = max;
};

StickerSheet::~StickerSheet (){
  delete[] picture_;
  delete[] x_;
  delete[] y_;
};

StickerSheet::StickerSheet (const StickerSheet &other){
  // picture_ = new Image[other.max_];
  // for (unsigned i = 0; i < max_; i++)
  //   picture_[i] = other.picture_[i];
  //
  // max_ = other.max_;
  // x_ = other.x_;
  // y_ = other.y_;

  picture_ = new Image*[other.max_];
  x_ = new unsigned[other.max_];
  y_ = new unsigned[other.max_];

  for (unsigned i = 0; i < other.max_; i++) {
    picture_[i] = new Image(*other.picture_[i]);
    x_[i] = other.x_[i];
    y_[i] = other.x_[i];
  }
  max_ = other.max_;
};

StickerSheet const & StickerSheet::operator= (const StickerSheet &other){
  if (this != &other) {
    // delete picture_;
    //
    // picture_ = new Image[other.max_];
    // for (unsigned i = 0; i < max_; i++)
    //   picture_[i] = other.picture_[i];
    //
    // max_ = other.max_;
    // x_ = other.x_;
    // y_ = other.y_;

    delete[] picture_;
    delete[] x_;
    delete[] y_;

    picture_ = new Image*[other.max_];
    x_ = new unsigned[other.max_];
    y_ = new unsigned[other.max_];

    for (unsigned i = 0; i < other.max_; i++) {
      picture_[i] = new Image(*other.picture_[i]);
      x_[i] = other.x_[i];
      y_[i] = other.x_[i];
    }
    max_ = other.max_;
  }

  return *this;
};

void StickerSheet::changeMaxStickers (unsigned max){
  if (max < max_) {
    // Image *newPicture = new Image[max];
    // for (unsigned i = 0; i < max; i++)
    //   newPicture[i] = picture_[i];
    //
    // delete[] picture_;
    // for (unsigned i = 0; i < max; i++)
    //   picture_[i] = newPicture[i];
    //
    // max_ = max;
  }

  Image **newPicture = new Image*[max];
  unsigned *newX = new unsigned[max];
  unsigned *newY = new unsigned[max];

  for (unsigned i = 0; i < max; i++) {
    newPicture[i] = picture_[i];
    newX[i] = x_[i];
    newY[i] = y_[i];
  }

  delete[] picture_;
  delete[] x_;
  delete[] y_;

  picture_ = new Image*[max];
  x_ = new unsigned[max];
  y_ = new unsigned[max];

  for (unsigned i = 0; i < max; i++) {
    picture_[i] = new Image(*newPicture[i]);
    x_[i] = newX[i];
    y_[i] = newY[i];
  }
  max_ = max;

  delete[] newPicture;
  delete[] newX;
  delete[] newY;
};

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  for (unsigned i = 0; i < max_; i++) {
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
  if (index >= max_)
    return false;

  if (picture_[index] != NULL) {
    x_[index] = x;
    y_[index] = y;
    return true;
  }
  return false;
};

void StickerSheet::removeSticker (unsigned index){
  if (picture_[index] != NULL) {
    delete picture_[index];
    x_[index] = 0;
    y_[index] = 0;
  }
};

Image * StickerSheet::getSticker (unsigned index) const {
  if (picture_[index] == NULL)
    return NULL;

  return picture_[index];
};

Image StickerSheet::render () const {

  unsigned width = picture_[0]->width();
  unsigned height = picture_[0]->height();

  // Calculate width & height of the render needed to fit all stickers
  for (unsigned i = 0; i < max_; i++){
    if (picture_[i] != NULL) {
      unsigned w = x_[i] + picture_[i]->width();
      unsigned h = y_[i] + picture_[i]->height();

      if (width < w)
        width = w;
      if (height < h)
        height = h;
    }
  }

  Image *render = new Image(*picture_[0]);
  render->resize(width,height);

  //Loop through the all sitckers in the sheet
  for (unsigned j = 0; j < max_; j++) {
    if (picture_[0] != NULL) {
      Image sticker = *picture_[j];

      for (unsigned x = x_[j]; x < x_[j] + sticker.width(); x++) {
        for (unsigned y = y_[j]; y < y_[j] + sticker.height(); y++) {

          HSLAPixel *pixel = &sticker.getPixel(x - x_[j], y - y_[j]);
          HSLAPixel *renderPix = &render->getPixel(x, y);

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

  Image sheet = *render;
  delete render;
  render = NULL;

  return sheet;
};
