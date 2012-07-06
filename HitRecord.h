#ifndef HitRecord_h
#define HitRecord_h

#include "Vector.h"
class Material;
class Primitive;
#define EPSILON (1.e-6)

class HitRecord
{
  public:
    HitRecord(double _max)
    {
      primitive = 0;
      material = 0;
      min = EPSILON;
      max = _max;
    }

    bool hit(double t, const Primitive* p, const Material* m, const Vector n)
    {
      if(t >= min && t <= max )
      {
	max = t;
	material = m;
	normal = n;
	primitive = p;
	return true;
      } 
      else
	return false;
    }

    const Material* getMaterial() const
    {
      return material;
    }

    const Vector getNormal() const
    {
      double length = normal.length();
      return normal / length;
    }

    const Primitive* getPrimitive() const
    {
      return primitive;
    }

    double getMin() const
    {
      return min;
    }

    double getMax() const
    {
      return max;
    }

  private:
    const Primitive* primitive;
    const Material* material;
    Vector normal;
    double min;
    double max;


};
#endif
