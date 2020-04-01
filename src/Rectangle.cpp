#include "Rectangle.h"
#include "Container.h"
#include <cmath>
#include <algorithm>

Rectangle::Rectangle(double w, double h):
  width(w),
  height(h),
  angleRad(0.0)
{
  this->setCoordinates(0.0, 0.0, 0.0);
}

// установка координат
void Rectangle::setCoordinates(double x0, double y0, double ang)
{
  this->coord[RECTANGLE_LEFT_DOWN] = MyVector(x0, y0);

  this->coord[RECTANGLE_LEFT_UP] = MyVector(
    x0 - this->height*sin(ang),
    y0 + this->height*cos(ang));

  this->coord[RECTANGLE_RIGHT_UP]= MyVector(
    x0 + this->width * cos(ang) - this->height*sin(ang),
    y0 + this->width * sin(ang) + this->height*cos(ang));

  this->coord[RECTANGLE_RIGHT_DOWN] = MyVector(
    x0 + this->width * cos(ang),
    y0 + this->width * sin(ang));
}

double Rectangle::getArea()
{
  return this->width * this->height;
}

bool Rectangle::intersection(const Container& container)
{
  // в нашей реализации контейнер это прямоугольник,
  // поэтому пользуемся функцией проверки пересечения прямоугольников
  Rectangle containerRectangle(container.getWidth(), container.getHeight());
  return intersection(containerRectangle);
}
// расчет пересечения с другим прямоугольником
bool Rectangle::intersection(const Rectangle& other)
{
  // критерий пересечения -
  // проецируем все точки прямоугольников на линию,
  // параллельную всем его сторонам
  // если проекции не пересекаются хотя бы на одной линии, 
  // значит пересечения нет

  // проекция рассчитывается с помощью скалярного произведения
  // у прямоугольника стороны параллельны поэтому на достаточно 2 проекции
  // для каждой фигуры
  MyVector vect[4];
  vect[0] =
    this->coord[RECTANGLE_LEFT_UP] - this->coord[RECTANGLE_LEFT_DOWN];
  vect[1] =
    this->coord[RECTANGLE_RIGHT_DOWN] - this->coord[RECTANGLE_LEFT_DOWN];
  vect[2] =
    other.coord[RECTANGLE_LEFT_UP] - other.coord[RECTANGLE_LEFT_DOWN];
  vect[3] =
    other.coord[RECTANGLE_RIGHT_DOWN] - other.coord[RECTANGLE_LEFT_DOWN];
  // перебираем проекции
  for (int i = 0 ; i < 4 ; i++)
  {
    // задаем контейнеры для хранения значений скалярных произведений
    std::vector<double> dotProductsOur, dotProductsOther;
    for (int j = 0 ; j < RECTANGLE_CORNERS ; j++)
    {
      dotProductsOur.emplace_back(vect[i].dotProduct(this->coord[j]));
      dotProductsOther.emplace_back(vect[i].dotProduct(other.coord[j]));
    }
    // сравниваем минимальные и максимальные значения проекции
    double ourMaxElement =
      *std::max_element(dotProductsOur.begin(), dotProductsOur.end());
    double ourMinElement =
      *std::min_element(dotProductsOur.begin(), dotProductsOur.end());     
    double otherMaxElement =
      *std::max_element(dotProductsOther.begin(), dotProductsOther.end());
    double otherMinElement =
      *std::min_element(dotProductsOther.begin(), dotProductsOther.end());
    // если проекция не пересекаются -
    // можно смело говорить что прямоугольники не пересекаются 
    if ( (ourMaxElement < otherMinElement) ||
	 (otherMaxElement < ourMinElement))
    {
      return false;
    }
  }
  // если мы дошли до конца цикла - значит пересечения всегда есть
  // т.е прямоугольники пересекаются
  return true;
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
