#ifndef Triangle_h
#define Triangle_h

#include "Primitive.h"

class Triangle: public Primitive
{
  public:
    Triangle(Material* material, const Vector& c1, const Vector& c2, const Vector& c3);
    virtual ~Triangle();


    virtual std::string type() { return "triangle"; }

    virtual void getBounds(BoundingBox& bbox) const;
    virtual void intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const;

  private:
    Vector c1;
    Vector c2;
    Vector c3;

};

#endif
