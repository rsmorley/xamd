
#include "BoundingBox.h"
#include <float.h>
#include <math.h>

BoundingBox::BoundingBox()
{
  min = Vector(DBL_MAX, DBL_MAX, DBL_MAX);
  max = Vector(-DBL_MAX, -DBL_MAX, -DBL_MAX);
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::extend(const Vector& p)
{
  min = Vector(fmin(p.x(), min.x()), fmin(p.y(), min.y()), fmin(p.z(), min.z()));
  max = Vector(fmax(p.x(), max.x()), fmax(p.y(), max.y()), fmax(p.z(), max.z()));
}
