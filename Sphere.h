#ifndef Sphere_h
#define Sphere_h

#include "Primitive.h"

class Sphere: public Primitive
{
  public:
    Sphere(Material* material, const Vector& center, double radius);
    virtual ~Sphere();

    virtual void getBounds(BoundingBox& bbox) const;
    virtual void intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const;

  private:
    Vector center;
    double radius;

};

#endif
