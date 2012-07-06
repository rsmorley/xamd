#ifndef Light_h
#define Light_h

#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "Vector.h"

class Light
{
  public:
    Light();
    virtual ~Light();

    virtual void preprocess();

    virtual double getLight(Color& light_color, Vector& light_dir, const RenderContext& context, const Vector& hPos) const = 0;

};

#endif
