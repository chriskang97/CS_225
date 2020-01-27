#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image bg; bg.readFromFile("bg.png");
  Image i;    i.readFromFile("bk.png");
  Image i2;   i2.readFromFile("hyd.png") ;
  Image i3;   i3.readFromFile("birb.png") ;



  StickerSheet s1(bg, 3);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i2, 500, 100);
  s1.addSticker(i3, 1000, 400);

  s1.render().writeToFile("myImage.png") ;

  return 0;
}
