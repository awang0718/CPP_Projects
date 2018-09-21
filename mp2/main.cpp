#include "Image.h"
#include "StickerSheet.h"

int main() {
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png

  Image alma;
  alma.readFromFile("tests/alma.png");

  StickerSheet sheet(alma, 10);

  Image alma2 = Image(alma);
  alma2.scale(.10);
  alma2.desaturate();
  alma2.lighten(.15);

  Image i;
  i.readFromFile("tests/i.png");
  i.scale(.25);

  Image i2 = Image(i);
  i2.scale(.4);
  i2.saturate();
  i2.lighten(.15);

  sheet.addSticker(i, 420, 100);
  sheet.addSticker(i2, 437, 125);
  sheet.addSticker(alma2, 275, 40);
  sheet.addSticker(alma2, 550, 40);

  Image alma3 = Image(sheet.render());
  alma3.scale(.25);
  alma3.desaturate();
  alma3.darken(.03);
  sheet.addSticker(alma3, 340, 400);

  Image alma4 = Image(sheet.render());
  alma4.scale(.25);
  alma4.desaturate();
  alma4.darken(.03);
  sheet.addSticker(alma4, 340, 400);

  Image alma5 = Image(sheet.render());
  alma5.scale(.25);
  alma5.desaturate();
  alma5.darken(.03);
  sheet.addSticker(alma5, 340, 400);

  sheet.render().writeToFile("myImage.png");

  return 0;
}
