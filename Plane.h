#ifndef Plane_h
#define Plane_h

#include "Primitive.h"

class Plane: public Primitive
{
  public:
    Plane(Material* material, const Vector& normal, const Vector& point);
    virtual ~Plane();

    virtual void getBounds(BoundingBox& bbox) const;
    virtual void intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const;

  private:
    Vector n;
    Vector p;

};

#endif
