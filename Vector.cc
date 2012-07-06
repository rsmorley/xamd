#include "Vector.h"
#include <iostream>

Vector operator* (double f, const Vector& v)
{
  return Vector(v.x() * f, v.y() * f, v.z() * f);
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
    out << '[' << v.x() << ", " << v.y() << ", " << v.z() << ']';
      return out;
}

