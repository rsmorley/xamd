#ifndef Material_h
#define Material_h

#include "Color.h"
#include "HitRecord.h"
#include "Ray.h"
#include "RenderContext.h"

class Material
{
  public:
    Material();
    virtual ~Material();

    virtual void preprocess();
    virtual void shade(Color& pixel, RenderContext& context, const Ray& ray, const HitRecord& h, int depth) const = 0;
};

#endif
