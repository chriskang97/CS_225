#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include <vector>

using namespace cs225;
using namespace std ;
/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(PNG & image) ;
  HSLAPixel getColor(unsigned x, unsigned y );

private:
  unsigned width ;
  vector<HSLAPixel> image_ref ;
};
