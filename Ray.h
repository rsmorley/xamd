#ifndef Ray_h
#define Ray_h

#include "Vector.h"
#include <ostream>

class Ray
{
  public:
    Ray()
    {
    }

    Ray(Vector origin, Vector direction)
    {
      o = origin;
      d = direction;
    }

    const Vector& origin() const
    {
      return o;
    }

    const Vector& direction() const
    {
      return d;
    }

    friend std::ostream& operator<<( std::ostream& out, const Ray& ray )
    {
      return out
	<< "[ " 
	<< ray.o[0] << ", " << ray.o[1] << ", " << ray.o[2] << ":  "
	<< ray.d[0] << ", " << ray.d[1] << ", " << ray.d[2] 
	<< " ]"; 
    }

  private:
    Vector o, d;
};

#endif
