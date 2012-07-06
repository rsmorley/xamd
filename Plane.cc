#include "Plane.h"
#include "HitRecord.h"
#include "Math.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Vector.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Plane::Plane(Material* material, const Vector& normal, const Vector& point)
  : Primitive(material), n(normal), p(point)
{
}

Plane::~Plane()
{
}

void Plane::getBounds(BoundingBox& bbox) const
{ 
  cerr <<  "Plane::getBounds() called!" << endl;
  exit( 1 );
}

void Plane::intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const
{
  double denom = n.dot(ray.direction());
  if (Abs(denom) > 1.e-6 )
  {
    double t = (n.dot(p - ray.origin()))/denom;
    h.hit(t, this, material, n);
  }
}
