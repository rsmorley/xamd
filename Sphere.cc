#include "Sphere.h"
#include "HitRecord.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Vector.h"
#include <math.h>

Sphere::Sphere(Material* material, const Vector& center, double radius)
  : Primitive(material), center(center), radius(radius)
{
}

Sphere::~Sphere()
{
}

void Sphere::getBounds(BoundingBox& bbox) const
{
    Vector diag(radius, radius, radius);
    bbox.extend(center+diag);
    bbox.extend(center-diag);
}

void Sphere::intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const
{
  Vector O = ray.origin() - center;
  double b = O.dot(ray.direction());
  double c = O.dot(O) - radius * radius;
  double disc = b * b - c;
  if(disc > 0)
  {
    double discSquare = sqrt(disc);
    double r1 = -b - discSquare;
    Vector hPos = ray.origin()+ray.direction()*r1;
    Vector normal = (hPos - center) * (1. / radius);
    if(!h.hit(r1, this, material, normal))
    {
      double r2 = -b + discSquare;
      hPos = ray.origin()+ray.direction()*r2;
      normal = (hPos - center) * (1. / radius);
      h.hit(r2, this, material, normal);
    }
  }
}

