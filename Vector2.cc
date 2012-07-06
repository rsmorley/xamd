#include "Vector2.h"
#include <iostream>

Vector2 operator* (double f, const Vector2& v)
{
  return Vector2(v.x() * f, v.y() * f);
}

std::ostream& operator<<(std::ostream& out, const Vector2& v)
{
    out << '[' << v.x() << ", " << v.y() << ']';
      return out;
}

