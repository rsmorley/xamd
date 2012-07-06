#ifndef Box_h
#define Box_h

#include "Primitive.h"

class Box: public Primitive
{
  public:
    Box(Material* material, const Vector& min, const Vector& max);
    virtual ~Box();


    virtual std::string type() { return "box"; }

    virtual void getBounds(BoundingBox& bbox) const;
    virtual void intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const;

  private:
    Vector min;
    Vector max;

};

#endif
