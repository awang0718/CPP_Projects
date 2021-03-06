/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <string>
#include <cmath>
#include <cstdlib>

#include "Image.h"
#include "cs225/PNG.h"
using cs225::PNG;
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

class StickerSheet {
  public:
    StickerSheet (const Image &picture, unsigned max);
    ~StickerSheet ();
    StickerSheet (const StickerSheet &other);
    const StickerSheet & 	operator= (const StickerSheet &other);

    void changeMaxStickers (unsigned max);
    int addSticker (Image &sticker, unsigned x, unsigned y);
    bool translate (unsigned index, unsigned x, unsigned y);
    void removeSticker (unsigned index);
    Image * getSticker (unsigned index) const;
    Image render () const;

  private:
    Image* sheet_;
    Image** picture_;
    unsigned max_;
    unsigned* x_;
    unsigned* y_;
};
