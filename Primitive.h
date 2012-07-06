#ifndef Primitive_h
#define Primitive_h

#include "Object.h"

class Primitive: public Object
{
  public:
    Primitive(Material* material);
    virtual ~Primitive();

    virtual void preprocess();
    virtual void intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const = 0;

  protected:
    Material* material;
};

#endif
