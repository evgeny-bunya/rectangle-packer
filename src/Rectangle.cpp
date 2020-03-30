#include "Rectangle.h"

Rectangle::Rectangle():
  width(0),
  height(0)
{
}

Rectangle::Rectangle(double w, double h):
  width(w),
  height(h)
{
}

double Rectangle::getArea()
{
  return this->width * this->height;
}

std::string Rectangle::getString()
{
  return std::string(
   "w=" +
   std::to_string(this->width) +
   " h=" +
   std::to_string(this->height)
   );
}
